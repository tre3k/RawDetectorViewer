/* mainwindow.h
 * Copyright 2019 Aug
 * Kirill Pshenichnyi
 * This part of InMageS (Inelastic Magnet Scattering)
 * Software for Build analytical data and processing experemental data
 */

#include "plot1d.h"

Plot1D::Plot1D(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout();
    layout->setMargin(0);
    this->setLayout(layout);

    /* init base plot class */
    plot = new Plot();

    /* bottom layout */
    tool_layout = new QHBoxLayout();
    button_clean = new QPushButton("clean");
    button_clean->hide();
    button_rescale = new QPushButton("rescale");
    tool_layout->addWidget(button_clean);
    tool_layout->addWidget(button_rescale);
    tool_layout->addStretch(0);

    /* top level layout */
    layout->addWidget(plot);
    layout->addLayout(tool_layout);

    connect(button_clean,SIGNAL(clicked()),
            this,SLOT(cleanPlots()));
    connect(button_rescale,SIGNAL(clicked()),
            this,SLOT(rescaleAxis()));
}

Plot1D::~Plot1D(){
    delete plot;
    delete button_clean;
    delete button_rescale;
}

void Plot1D::rescaleAxis(){
    plot->rescaleAxes(true);
    plot->replot();
}

void Plot1D::addPlot(QVector<double> abscissa, QVector<double> ordinate, QString name, QString color){
    QColor col;
    if(color=="rand"){
        col = QColor(rand()%245+10, rand()%245+10, rand()%245+10);
    }else{
        col = QColor(color);
    }

    //qDebug() << bars;
    //if(bars!=nullptr) delete bars;
    if(bars == nullptr) bars = new QCPBars(plot->xAxis,plot->yAxis);
    bars->setData(abscissa,ordinate);
    plot->rescaleAxes(true);
    //if(abscissa.size()!=0) bars->setWidth(0.8*abscissa.at(abscissa.size()-1)/abscissa.size());
    bars->setWidth(0.8);
    QPen pen(col);
    bars->setPen(pen);
    bars->setBrush(col);

    /*
    QPen pen;
    pen.setColor(col);

    plot->addGraph();
    plot->graph()->setName(name);
    plot->graph()->setData(abscissa,ordinate);
    plot->graph()->setPen(pen);

    auto *decorator = new QCPSelectionDecorator();
    decorator->setPen(QPen(QColor(color),2));
    plot->graph()->setSelectionDecorator(decorator);
    */

    /* need modificate */
    /*
    plot->graph()->setLineStyle((QCPGraph::LineStyle)1);
    plot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    plot->replot();
    */
}
