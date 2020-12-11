/* mainwindow.h
 * Copyright 2019 Aug
 * Kirill Pshenichnyi
 * This part of InMageS (Inelastic Magnet Scattering)
 * Software for Build analitical data and processing experemental data
 */

#include "plot2d.h"

Plot2D::Plot2D(QWidget *parent) : QWidget(parent)
{
    /* place widgets on layouts */
    plot = new Plot();

    central_layout = new QVBoxLayout();
    central_layout->setMargin(0);
    tool_layout = new QHBoxLayout();

    combo_select_units = new QComboBox();
    buttonRescale = new QPushButton("rescale");
    spinBoxMax = new QDoubleSpinBox();
    spinBoxMin = new QDoubleSpinBox();
    check_hold = new QCheckBox("hold");
    check_log_scale = new QCheckBox("log");

    spinBoxMax->setRange(-999999999.999,999999999.999);
    spinBoxMin->setRange(-999999999.999,999999999.999);
    spinBoxMax->setDecimals(3);
    spinBoxMin->setDecimals(3);

    spinBoxMax->setValue(100.0);
    spinBoxMin->setValue(-100.0);

    spinBoxMax->setMaximumWidth(80);
    spinBoxMin->setMaximumWidth(80);

    combo_select_units->addItem("pixels");
    combo_select_units->addItem("wave vector [1/Å]");
    combo_select_units->addItem("wave vector [1/nm]");
    combo_select_units->addItem("angle θ [mrad]");
    combo_select_units->addItem("reletiv [-1;1]");

    tool_layout->setMargin(0);
    tool_layout->addWidget(new QLabel("Unit:"));
    tool_layout->addWidget(combo_select_units);
    tool_layout->addWidget(buttonRescale);
    tool_layout->addStretch();
    tool_layout->addWidget(new QLabel("max:"));
    tool_layout->addWidget(spinBoxMax,0,Qt::AlignRight);
    tool_layout->addWidget(new QLabel("min:"));
    tool_layout->addWidget(spinBoxMin,0,Qt::AlignRight);
    tool_layout->addWidget(check_hold,0,Qt::AlignRight);
    tool_layout->addWidget(check_log_scale,0,Qt::AlignRight);

    central_layout->addWidget(plot);
    central_layout->addLayout(tool_layout);

    this->setLayout(central_layout);

    /* set 2d plot (colorMap colorScale, etc*/
    colorMap = new QCPColorMap(plot->xAxis,plot->yAxis);
    colorScale = new QCPColorScale(plot);
    colorScale->setType(QCPAxis::atRight);
    plot->plotLayout()->addElement(0,1,colorScale);

    colorMap->setColorScale(colorScale);
    colorMap->setGradient(QCPColorGradient::gpJet);

    QCPMarginGroup *marginGroup = new QCPMarginGroup(plot);
    plot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);


    connect(check_log_scale,SIGNAL(clicked(bool)),
            this,SLOT(logScale(bool)));
    connect(check_hold,SIGNAL(clicked(bool)),
            this,SLOT(hold(bool)));
    connect(combo_select_units,SIGNAL(activated(int)),
            this,SLOT(setAxisUnit(int)));
    connect(buttonRescale,SIGNAL(clicked()),
            this,SLOT(rescaleAxis()));
    connect(colorScale,SIGNAL(dataRangeChanged(QCPRange)),
            this,SLOT(changeDataRange(QCPRange)));

    /* set font for right color scale */
    /*
    QFont fontKameron(
                QFontDatabase::applicationFontFamilies(
                    QFontDatabase::addApplicationFont(":/fonts/kameron.ttf")).at(0),11);
    colorScale->axis()->setTickLabelFont(fontKameron);
    colorScale->axis()->setSelectedTickLabelFont(fontKameron);

    colorScale->axis()->setLabelFont(fontKameron);
    colorScale->axis()->setLabelFont(fontKameron);
    */

}


void Plot2D::buildNeutronData(NeutronData *n_data){
    setNeutronData(n_data);
    buildNeutronData();
    return;
}

void Plot2D::setNeutronData(NeutronData *n_data){
    neutron_data = n_data;
}

int Plot2D::getCurrentUnit(){
    return combo_select_units->currentIndex();
}

void Plot2D::buildNeutronData(){
    if(neutron_data==nullptr) return;
    colorMap->data()->setSize(int(neutron_data->size_Nx()),int(neutron_data->size_Ny()));
    for(int i=0;i<int(neutron_data->size_Nx());i++){
        for(int j=0;j<int(neutron_data->size_Ny());j++){
            colorMap->data()->setCell(i,j,neutron_data->data_matrix->at((unsigned long int) i, (unsigned long int) j));
        }
    }
    setHoldRange();
    setAxisUnit(combo_select_units->currentIndex());
    return;
}

void Plot2D::setAxisUnit(int unit){
    if(neutron_data == nullptr) return;
    switch (unit){
    /* just pixelx Nx, Ny */
    case Units::UNIT_PIXEL:
        colorMap->data()->setRange(QCPRange(0,neutron_data->size_Nx()),
                                   QCPRange(0,neutron_data->size_Ny()));
        plot->xAxis->setLabel("pixels x");
        plot->yAxis->setLabel("pixels y");
        break;

    /* wave vector [1/A] */
    case Units::UNIT_ANGSTROM:
        colorMap->data()->setRange(QCPRange(-neutron_data->get_maxQx_A(),neutron_data->get_maxQx_A()),
                                   QCPRange(-neutron_data->get_maxQy_A(),neutron_data->get_maxQy_A()));
        plot->xAxis->setLabel("wave vector Qx, 1/Å");
        plot->yAxis->setLabel("wave vector Qy, 1/Å");

        break;

    case Units::UNIT_NM:
        colorMap->data()->setRange(QCPRange(-neutron_data->get_maxQx_nm(),neutron_data->get_maxQx_nm()),
                                   QCPRange(-neutron_data->get_maxQy_nm(),neutron_data->get_maxQy_nm()));
        plot->xAxis->setLabel("wave vector Qx, 1/nm");
        plot->yAxis->setLabel("wave vector Qy, 1/nm");
        break;

    case Units::UNIT_THETA:
        colorMap->data()->setRange(QCPRange(-neutron_data->getMaximumThetaXmrad(),neutron_data->getMaximumThetaXmrad()),
                                   QCPRange(-neutron_data->getMaximumThetaYmrad(),neutron_data->getMaximumThetaYmrad()));
        plot->xAxis->setLabel(QString("θx, mrad").toHtmlEscaped());
        plot->yAxis->setLabel("θy, mrad");
        break;

    case Units::UNIT_REL:
        colorMap->data()->setRange(QCPRange(-1.0,1.0),
                                   QCPRange(-1.0,1.0));
        plot->xAxis->setLabel("x, arb. units");
        plot->yAxis->setLabel("y, arb. units");
        break;
    }
    setHoldRange();
}

void Plot2D::logScale(bool state){
    if(state){
        colorMap->setDataScaleType(QCPAxis::stLogarithmic);
    }else{
        colorMap->setDataScaleType(QCPAxis::stLinear);
    }
    setHoldRange();
    return;
}

void Plot2D::hold(bool state){
    if(state){
        connect(spinBoxMax,SIGNAL(valueChanged(double)),
                this,SLOT(setHoldRange()));
        connect(spinBoxMin,SIGNAL(valueChanged(double)),
                this,SLOT(setHoldRange()));
        setHoldRange();
    }else{
        disconnect(spinBoxMax,SIGNAL(valueChanged(double)),
                this,SLOT(setHoldRange()));
        disconnect(spinBoxMin,SIGNAL(valueChanged(double)),
                this,SLOT(setHoldRange()));
    }

}

void Plot2D::setHoldRange(){
    if(check_hold->isChecked()){
        colorMap->setDataRange(QCPRange(spinBoxMin->value(),spinBoxMax->value()));
    }else{
        colorMap->rescaleDataRange(!check_hold->isChecked());
    }
    plot->rescaleAxes();
    plot->replot();
}

void Plot2D::rescaleAxis(){
    if(!check_hold->isChecked()){
        setHoldRange();
    }
    plot->rescaleAxes();
    plot->replot();
}

void Plot2D::changeDataRange(QCPRange range){
    if(!check_hold->isChecked()){
        spinBoxMax->setValue(range.upper);
        spinBoxMin->setValue(range.lower);
    }
}

/* get recoordinate value for x and y axis */
double Plot2D::getRecoordX(double rel_x){
    QCPRange range = plot->xAxis->range();
    switch(combo_select_units->currentIndex()){
    case UNIT_PIXEL:
        return rel_x*(range.upper-range.lower)/2.0+(range.upper-range.lower)/2.0;
        break;
    default:
        return rel_x*(range.upper-range.lower)/2.0;
        break;
    }
}

double Plot2D::getRecoordY(double rel_y){
    QCPRange range = plot->yAxis->range();
    switch(combo_select_units->currentIndex()){
    case UNIT_PIXEL:
        return rel_y*(range.upper-range.lower)/2.0+(range.upper-range.lower)/2.0;
        break;
    default:
        return rel_y*(range.upper-range.lower)/2.0;
        break;
    }
}

void Plot2D::setCurrentUnitIndex(int index){
    combo_select_units->setCurrentIndex(index);
    setAxisUnit(index);
    return;
}
