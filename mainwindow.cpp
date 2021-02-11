#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
        this->setMinimumSize(400,400);
        this->setGeometry(0,0,600,600);
        this->setWindowTitle("Raw Detector Viewer");

        plot2d = new Plot2D();

        this->setCentralWidget(plot2d);
        buildDataListDialog();
        buildOptionDialog();
        buildChannelsDialog();
        buildBoxAverageDialog();

        buildMenuBar();
        buildToolBar();
        this->statusBar()->show();

        applyOptions();
}

MainWindow::~MainWindow(){
        optiondialog.OptionDialog->close();
        datalistdialog.DataListDialog->close();
}

void MainWindow::buildChannelsDialog(){
        channelsdialog.ChannelsDialog = new QDialog();
        channelsdialog.ChannelsDialog->setWindowTitle("channels");
        channelsdialog.tab_widget = new QTabWidget();
        channelsdialog.layout = new QVBoxLayout();

        channelsdialog.ChannelsDialog->setLayout(channelsdialog.layout);
        channelsdialog.layout->addWidget(channelsdialog.tab_widget);

        channelsdialog.widget_tab1 = new QWidget();
        channelsdialog.layout_tab1 = new QVBoxLayout();
        channelsdialog.widget_tab1->setLayout(channelsdialog.layout_tab1);

        channelsdialog.widget_tab2 = new QWidget();
        channelsdialog.layout_tab2 = new QVBoxLayout();
        channelsdialog.widget_tab2->setLayout(channelsdialog.layout_tab2);

        channelsdialog.tab_widget->addTab(channelsdialog.widget_tab1,"channels");
        channelsdialog.tab_widget->addTab(channelsdialog.widget_tab2,"different");

        channelsdialog.plot_x1 = new Plot1D();
        channelsdialog.plot_x2 = new Plot1D();
        channelsdialog.plot_y1 = new Plot1D();
        channelsdialog.plot_y2 = new Plot1D();

        channelsdialog.layout_tab1->addWidget(channelsdialog.plot_x1);
        channelsdialog.layout_tab1->addWidget(channelsdialog.plot_x2);
        channelsdialog.layout_tab1->addWidget(channelsdialog.plot_y1);
        channelsdialog.layout_tab1->addWidget(channelsdialog.plot_y2);
        channelsdialog.layout_tab1->setMargin(0);

        channelsdialog.plot_x1->getPlot()->yAxis->setLabel("x1");
        channelsdialog.plot_x2->getPlot()->yAxis->setLabel("x2");
        channelsdialog.plot_y1->getPlot()->yAxis->setLabel("y1");
        channelsdialog.plot_y2->getPlot()->yAxis->setLabel("y2");
}

void MainWindow::buildDataListDialog(){
        datalistdialog.DataListDialog = new QDialog();
        datalistdialog.layout_central = new QVBoxLayout();
        datalistdialog.layout_central->setMargin(1);
        datalistdialog.DataListDialog->setLayout(datalistdialog.layout_central);
        datalistdialog.DataListDialog->setWindowTitle("Data List");

        datalistdialog.tab_widget = new QTabWidget();
        datalistdialog.widget_tab1 = new QWidget();
        datalistdialog.widget_tab2 = new QWidget();
        datalistdialog.layout_central->addWidget(datalistdialog.tab_widget);
        datalistdialog.tab_widget->addTab(datalistdialog.widget_tab1,"values");
        datalistdialog.tab_widget->addTab(datalistdialog.widget_tab2,"memory");

        datalistdialog.layout_tab1 = new QVBoxLayout();
        datalistdialog.layout_tab2 = new QVBoxLayout();
        datalistdialog.widget_tab1->setLayout(datalistdialog.layout_tab1);
        datalistdialog.widget_tab2->setLayout(datalistdialog.layout_tab2);
        datalistdialog.layout_tab1->setMargin(1);
        datalistdialog.layout_tab2->setMargin(1);

        datalistdialog.list_values = new QListWidget();
        datalistdialog.list_raw = new QListWidget();

        datalistdialog.layout_tab1->addWidget(datalistdialog.list_values);
        datalistdialog.layout_tab2->addWidget(datalistdialog.list_raw);

        datalistdialog.push_button_ok = new QPushButton("ok");
        datalistdialog.layout_push_button = new QHBoxLayout();
        datalistdialog.layout_push_button->addStretch(1);
        datalistdialog.layout_push_button->addWidget(datalistdialog.push_button_ok);

        datalistdialog.layout_central->addLayout(datalistdialog.layout_push_button);

        connect(datalistdialog.push_button_ok,SIGNAL(clicked(bool)),datalistdialog.DataListDialog,SLOT(close()));

        datalistdialog.DataListDialog->setMinimumSize(130,400);
}

void MainWindow::buildBoxAverageDialog(){
        boxaveragedialog.boxaveragedialog = new QDialog();
        boxaveragedialog.boxaveragedialog->setWindowTitle("BoxAverage");
        boxaveragedialog.layout = new QVBoxLayout();
        boxaveragedialog.layout_button = new QHBoxLayout();
        boxaveragedialog.layout_form = new QFormLayout();

        boxaveragedialog.button_close = new QPushButton("close");
        boxaveragedialog.button_average = new QPushButton("average");

        boxaveragedialog.spinbox_center_x = new QDoubleSpinBox();
        boxaveragedialog.spinbox_center_y = new QDoubleSpinBox();
        boxaveragedialog.spinbox_h = new QDoubleSpinBox();
        boxaveragedialog.spinbox_w = new QDoubleSpinBox();

        boxaveragedialog.label_neutron_sum = new QLabel("<b>0</b>");

        boxaveragedialog.spinbox_center_x->setRange(-99999.99,99999.99);
        boxaveragedialog.spinbox_center_y->setRange(-99999.99,99999.99);
        boxaveragedialog.spinbox_h->setRange(-99999.99,99999.99);
        boxaveragedialog.spinbox_w->setRange(-99999.99,99999.99);

        boxaveragedialog.spinbox_center_x->setSuffix(" pix");
        boxaveragedialog.spinbox_center_y->setSuffix(" pix");
        boxaveragedialog.spinbox_h->setSuffix(" pix");
        boxaveragedialog.spinbox_w->setSuffix(" pix");

        boxaveragedialog.layout->addLayout(boxaveragedialog.layout_form);
        boxaveragedialog.layout->addLayout(boxaveragedialog.layout_button);

        boxaveragedialog.boxaveragedialog->setLayout(boxaveragedialog.layout);

        boxaveragedialog.layout_form->addRow("Center x: ",boxaveragedialog.spinbox_center_x);
        boxaveragedialog.layout_form->addRow("Center y: ",boxaveragedialog.spinbox_center_y);
        boxaveragedialog.layout_form->addRow("Hight: ",boxaveragedialog.spinbox_h);
        boxaveragedialog.layout_form->addRow("Width: ",boxaveragedialog.spinbox_w);
        boxaveragedialog.layout_form->addRow("Neutrons: ",boxaveragedialog.label_neutron_sum);

        boxaveragedialog.layout_button->addStretch();
        //boxaveragedialog.layout_button->addWidget(boxaveragedialog.button_average);
        boxaveragedialog.layout_button->addWidget(boxaveragedialog.button_close);

        connect(boxaveragedialog.button_close,SIGNAL(clicked()),boxaveragedialog.boxaveragedialog,SLOT(close()));
        connect(boxaveragedialog.spinbox_center_x,SIGNAL(valueChanged(double)),this,SLOT(averageBoxChanged(double)));
        connect(boxaveragedialog.spinbox_center_y,SIGNAL(valueChanged(double)),this,SLOT(averageBoxChanged(double)));
        connect(boxaveragedialog.spinbox_w,SIGNAL(valueChanged(double)),this,SLOT(averageBoxChanged(double)));
        connect(boxaveragedialog.spinbox_h,SIGNAL(valueChanged(double)),this,SLOT(averageBoxChanged(double)));
        connect(this,SIGNAL(fileLoaded()),this,SLOT(averageBoxChanged(double)));

}

void MainWindow::buildMenuBar(){
        menubar.menu_bar = new QMenuBar();
        menubar.file = new QMenu("&File");
        menubar.open = new QAction("&Open");
        menubar.menu_export = new QMenu("&Export");
        menubar.export_txt = new QAction("txt");
        menubar.quit = new QAction("&Quit");

        menubar.menu_bar->addMenu(menubar.file);
        menubar.file->addAction(menubar.open);
        menubar.file->addMenu(menubar.menu_export);
        menubar.menu_export->addAction(menubar.export_txt);
        menubar.file->addSeparator();
        menubar.file->addAction(menubar.quit);

        menubar.edit = new QMenu("&Edit");
        menubar.box_average = new QAction("Box average");
        menubar.datalist = new QAction("Show list of data");
        menubar.option = new QAction("&Option");
        menubar.channels = new QAction("&Channels");

        menubar.menu_bar->addMenu(menubar.edit);
        menubar.edit->addAction(menubar.box_average);
        menubar.edit->addSeparator();
        menubar.edit->addAction(menubar.channels);
        menubar.edit->addAction(menubar.datalist);
        menubar.edit->addSeparator();
        menubar.edit->addAction(menubar.option);

        this->setMenuBar(menubar.menu_bar);

        connect(menubar.quit,SIGNAL(triggered(bool)),this,SLOT(close()));
        connect(menubar.open,SIGNAL(triggered(bool)),this,SLOT(openFile()));
        connect(menubar.export_txt,SIGNAL(triggered(bool)),this,SLOT(exportTxt()));
        connect(menubar.datalist,SIGNAL(triggered(bool)),datalistdialog.DataListDialog,SLOT(show()));
        connect(menubar.option,SIGNAL(triggered(bool)),optiondialog.OptionDialog,SLOT(show()));
        connect(menubar.channels,SIGNAL(triggered(bool)),channelsdialog.ChannelsDialog,SLOT(show()));
        connect(menubar.box_average,SIGNAL(triggered(bool)),boxaveragedialog.boxaveragedialog,SLOT(show()));
}

void MainWindow::buildToolBar(){
        toolbar.tool_bar = new QToolBar();
        toolbar.combo_box_resolution = new QComboBox();
        toolbar.push_button_update = new QPushButton("update");

        toolbar.combo_box_resolution->addItem("128x128");
        toolbar.combo_box_resolution->addItem("256x256");
        toolbar.combo_box_resolution->addItem("512x512");
        toolbar.combo_box_resolution->addItem("1024x1024");
        toolbar.combo_box_resolution->addItem("2048x2048");
        toolbar.combo_box_resolution->addItem("4096x4096");

        toolbar.combo_box_resolution->setCurrentIndex(1);

        toolbar.tool_bar->addWidget(toolbar.push_button_update);
        toolbar.tool_bar->addWidget(new QLabel(" resolution: "));
        toolbar.tool_bar->addWidget(toolbar.combo_box_resolution);

        toolbar.check_x = new QCheckBox("mirror x");
        toolbar.check_y = new QCheckBox("mirror y");

        toolbar.tool_bar->addWidget(toolbar.check_x);
        toolbar.tool_bar->addWidget(toolbar.check_y);

        addToolBar(toolbar.tool_bar);
        toolbar.tool_bar->show();

        connect(toolbar.check_x,SIGNAL(stateChanged(int)),this,SLOT(loadFile()));
        connect(toolbar.check_y,SIGNAL(stateChanged(int)),this,SLOT(loadFile()));
        connect(toolbar.push_button_update,SIGNAL(clicked(bool)),this,SLOT(loadFile()));
        connect(toolbar.combo_box_resolution,SIGNAL(currentIndexChanged(int)),this,SLOT(changeResolution(int)));
}

void MainWindow::buildOptionDialog(){
        optiondialog.OptionDialog = new QDialog();
        optiondialog.OptionDialog->setWindowTitle("Options");
        optiondialog.layout = new QFormLayout();
        optiondialog.OptionDialog->setLayout(optiondialog.layout);

        optiondialog.button_ok = new QPushButton("ok");
        optiondialog.button_apply = new QPushButton("apply");
        optiondialog.button_close = new QPushButton("close");

        QHBoxLayout *button_layout = new QHBoxLayout();
        button_layout->addStretch(1);
        button_layout->addWidget(optiondialog.button_apply);
        button_layout->addWidget(optiondialog.button_ok);
        button_layout->addWidget(optiondialog.button_close);

        optiondialog.spin_sum_max = new QSpinBox();
        optiondialog.spin_sum_min = new QSpinBox();
        optiondialog.spin_sum_max->setRange(0,30000);
        optiondialog.spin_sum_min->setRange(0,30000);
        optiondialog.spin_sum_max->setValue(5000);  //default values
        optiondialog.spin_sum_min->setValue(3500);

        optiondialog.spin_lambda = new QDoubleSpinBox();
        optiondialog.spin_lambda->setSuffix(" Å");
        optiondialog.spin_lambda->setValue(5.0);
        optiondialog.spin_ds = new QDoubleSpinBox();
        optiondialog.spin_ds->setSuffix(" m");
        optiondialog.spin_ds->setValue(1.0);
        optiondialog.spin_size = new QDoubleSpinBox();
        optiondialog.spin_size->setSuffix(" mm");
        optiondialog.spin_size->setRange(0,99999);
        optiondialog.spin_size->setValue(200.0);

        optiondialog.layout->addRow("Maximum sum: ", optiondialog.spin_sum_max);
        optiondialog.layout->addRow("Minimum sum: ", optiondialog.spin_sum_min);
        optiondialog.layout->addRow("Wavelenght: ", optiondialog.spin_lambda);
        optiondialog.layout->addRow("Source detector: ", optiondialog.spin_ds);
        optiondialog.layout->addRow("Size of detector: ", optiondialog.spin_size);

        optiondialog.layout->addRow("",button_layout);

        connect(optiondialog.button_close,SIGNAL(clicked(bool)),optiondialog.OptionDialog,SLOT(close()));
        connect(optiondialog.button_ok,SIGNAL(clicked(bool)),this,SLOT(applyOptions()));
        connect(optiondialog.button_ok,SIGNAL(clicked(bool)),optiondialog.OptionDialog,SLOT(close()));
        connect(optiondialog.button_apply,SIGNAL(clicked(bool)),this,SLOT(applyOptions()));
}

int MainWindow::vectorFindOrAdd(QVector<double> *vector,QVector<double> *y, double value){
        int index = 0;
        if(vector->size()==0){
                vector->append(value);
                y->clear();
                y->append(1);
                return 0;
        }
        for(auto v : *vector){
                if(v==value){
                        (*y)[index] += 1;
                        return index;
                }
                index ++;
        }
        vector->append(value);
        y->append(1);
        return vector->size()-1;
}

void MainWindow::loadFile(){
        if(_filenames.size()==0) return;

        unsigned long ix = 0;
        unsigned long iy = 0;

        QString str;
        QString mark;

        channelsdialog.y_x1.clear();
        channelsdialog.x_x1.clear();
        channelsdialog.y_x2.clear();
        channelsdialog.x_x2.clear();
        channelsdialog.y_y1.clear();
        channelsdialog.x_y1.clear();
        channelsdialog.y_y2.clear();
        channelsdialog.x_y2.clear();

        unsigned long int count = 0;
        unsigned long int fail_count = 0;

        datalistdialog.list_raw->clear();
        datalistdialog.list_values->clear();


        if(_nd!=nullptr) delete _nd;
        _nd = new NeutronData(_resolution,_resolution);
        _nd->setDlpxpy(_opt.source_detector,
                       _opt.lambda,
                       _opt.size_of_detector/_resolution,
                       _opt.size_of_detector/_resolution
        );

        if(_rd!=nullptr) delete _rd;
        for(auto filename : _filenames){
              _rd = new RawData(filename,_opt);
              for(auto rd : _rd->vRawData){
                      switch(rd.code){
                      case 1:
                              mark = "x2";
                              vectorFindOrAdd(&channelsdialog.x_x2,&channelsdialog.y_x2,rd.value);
                              break;
                      case 3:
                              mark = "y2";
                              vectorFindOrAdd(&channelsdialog.x_y2,&channelsdialog.y_y2,rd.value);
                              break;
                      case 5:
                              mark = "x1";
                              vectorFindOrAdd(&channelsdialog.x_x1,&channelsdialog.y_x1,rd.value);
                              break;
                      case 7:
                              mark = "y1";
                              vectorFindOrAdd(&channelsdialog.x_y1,&channelsdialog.y_y1,rd.value);
                              break;
                      default:
                              mark = "?";
                      }

                      str = "( 0x"+QString::number(rd.raw,16)+ " ) " +
                                 QString::number(rd.code)+" ["+mark+"] = " +
                                 QString::number(rd.value);
                      datalistdialog.list_raw->addItem(str);
              }


              for(auto fd : _rd->vFourData){
                      count ++;
                      if(!fd.correct){
                              mark = "NOT CORRECT!";
                              fail_count++;
                      }else{
                              mark = "";
                      }
                      str = "x1 = "+QString::number(fd.x1)+
                      ", x2 = "+QString::number(fd.x2)+
                      ", y1 = "+QString::number(fd.y1)+
                      ", y2 = "+QString::number(fd.y2)+
                      ", sum x = "+QString::number(fd.x1+fd.x2)+
                      ", sum y = "+QString::number(fd.y1+fd.y2)+
                      "\t"+mark;
                      datalistdialog.list_values->addItem(str);
                      if(!fd.correct) continue;

                      if(toolbar.check_x->isChecked()){
                              ix = (unsigned long)_resolution*fd.x1/(fd.x1+fd.x2);
                      }else{
                              ix = (unsigned long)_resolution*fd.x2/(fd.x1+fd.x2);
                      }
                      if(toolbar.check_y->isChecked()){
                              iy = (unsigned long)_resolution*fd.y2/(fd.y1+fd.y2);
                      }else{
                              iy = (unsigned long)_resolution*fd.y1/(fd.y1+fd.y2);
                      }

                      _nd->data_matrix->set(ix,iy,
                              _nd->data_matrix->get(ix,iy)+1.0
                      );

              }

              channelsdialog.plot_x1->addPlot(channelsdialog.x_x1,channelsdialog.y_x1,"x1","red");
              channelsdialog.plot_x2->addPlot(channelsdialog.x_x2,channelsdialog.y_x2,"x2","red");
              channelsdialog.plot_y1->addPlot(channelsdialog.x_y1,channelsdialog.y_y1,"y1","blue");
              channelsdialog.plot_y2->addPlot(channelsdialog.x_y2,channelsdialog.y_y2,"y2","blue");
        }

        plot2d->buildNeutronData(_nd);

        str = "all neutrons: "+QString::number(count)+", correct: "+QString::number(count-fail_count)+", "+QString::number(100.0*(count-fail_count)/count)+"%";
        this->statusBar()->showMessage(str);
        emit fileLoaded();
}

void MainWindow::changeResolution(int index){
        switch(index){
        case 0:
                _resolution = 128;
                break;
        case 1:
                _resolution = 256;
                break;
        case 2:
                _resolution = 512;
                break;
        case 3:
                _resolution = 1024;
                break;
        case 4:
                _resolution = 2048;
                break;
        case 5:
                _resolution = 4096;
                break;
        }
        loadFile();
}

double MainWindow::amountNeutronsInPixels(int x,int y,int h,int w){
        double amount = 0;
        //_nd->data_matrix->at

        for(int i=x-w/2; i<x+w/2; i++){
                for(int j=y-h/2; j<y+h/2; j++){
                        amount += _nd->data_matrix->at(i,j);
                }
        }

        return amount;
}

void MainWindow::applyOptions(){
        _opt.max_sum = optiondialog.spin_sum_max->value();
        _opt.min_sum = optiondialog.spin_sum_min->value();
        _opt.lambda = optiondialog.spin_lambda->value();
        _opt.size_of_detector = optiondialog.spin_size->value();
        _opt.source_detector = optiondialog.spin_ds->value();
}

void MainWindow::paintBox(double center_x, double center_y, double h, double w){
        plot2d->getPlot()->clearItems();
        if(boxaveragedialog.boxaveragedialog->isHidden()) return;
        QPen pen;
        pen.setStyle(Qt::DashLine);
        pen.setWidth(1);
        pen.setColor("black");

        QCPItemRect *box = new QCPItemRect(plot2d->getPlot());
        box->setPen(pen);
        box->topLeft->setCoords(center_x-w/2,center_y-h/2);
        box->bottomRight->setCoords(center_x+w/2,center_y+h/2);
        plot2d->getPlot()->replot();
}

void MainWindow::averageBoxChanged(double value){
        paintBox(boxaveragedialog.spinbox_center_x->value(),
                 boxaveragedialog.spinbox_center_y->value(),
                 boxaveragedialog.spinbox_h->value(),
                 boxaveragedialog.spinbox_w->value());
        boxaveragedialog.label_neutron_sum->setText("<b>"+
                                                    QString::number(amountNeutronsInPixels(
                                                                            boxaveragedialog.spinbox_center_x->value(),
                                                                            boxaveragedialog.spinbox_center_y->value(),
                                                                            boxaveragedialog.spinbox_h->value(),
                                                                            boxaveragedialog.spinbox_w->value()))+
                                                    "</b>");
}

void MainWindow::exportTxt(){
        QString filename = QFileDialog::getSaveFileName(nullptr,"export to txt files","","*.*");
        _nd->data_matrix->exportTxt(filename+"_data_matrix.txt");

        QFile fx1(filename+"_x1.txt");
        QFile fx2(filename+"_x2.txt");
        QFile fy1(filename+"_y1.txt");
        QFile fy2(filename+"_y2.txt");

        fx1.open(QIODevice::WriteOnly);
        fx2.open(QIODevice::WriteOnly);
        fy1.open(QIODevice::WriteOnly);
        fy2.open(QIODevice::WriteOnly);

        QTextStream tsx1(&fx1);
        QTextStream tsx2(&fx2);
        QTextStream tsy1(&fy1);
        QTextStream tsy2(&fy2);

        tsx1 << "# (channel count) x1: " << endl;
        for(int i=0;i<channelsdialog.x_x1.size();i++) tsx1 << QString::number(channelsdialog.x_x1.at(i)) << " " << QString::number(channelsdialog.y_x1.at(i)) << endl;
        tsx2 << "# (channel count) x2: " << endl;
        for(int i=0;i<channelsdialog.x_x2.size();i++) tsx2 << QString::number(channelsdialog.x_x2.at(i)) << " " << QString::number(channelsdialog.y_x2.at(i)) << endl;
        tsy1 << "# (channel count) y1: " << endl;
        for(int i=0;i<channelsdialog.x_y1.size();i++) tsy1 << QString::number(channelsdialog.x_y1.at(i)) << " " << QString::number(channelsdialog.y_y1.at(i)) << endl;
        tsy2 << "# (channel count) y2: " << endl;
        for(int i=0;i<channelsdialog.x_y2.size();i++) tsy2 << QString::number(channelsdialog.x_y2.at(i)) << " " << QString::number(channelsdialog.y_y2.at(i)) << endl;

        fx1.close(); fx2.close(); fy1.close(); fy2.close();
}

/* EOF */
