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

void MainWindow::buildMenuBar(){
        menubar.menu_bar = new QMenuBar();
        menubar.file = new QMenu("&File");
        menubar.open = new QAction("&Open");
        menubar.quit = new QAction("&Quit");

        menubar.menu_bar->addMenu(menubar.file);
        menubar.file->addAction(menubar.open);
        menubar.file->addSeparator();
        menubar.file->addAction(menubar.quit);

        menubar.edit = new QMenu("&Edit");
        menubar.datalist = new QAction("Show list of data");
        menubar.option = new QAction("&Option");
        menubar.channels = new QAction("&Channels");

        menubar.menu_bar->addMenu(menubar.edit);
        menubar.edit->addAction(menubar.channels);
        menubar.edit->addAction(menubar.datalist);
        menubar.edit->addSeparator();
        menubar.edit->addAction(menubar.option);

        this->setMenuBar(menubar.menu_bar);

        connect(menubar.quit,SIGNAL(triggered(bool)),this,SLOT(close()));
        connect(menubar.open,SIGNAL(triggered(bool)),this,SLOT(openFile()));
        connect(menubar.datalist,SIGNAL(triggered(bool)),datalistdialog.DataListDialog,SLOT(show()));
        connect(menubar.option,SIGNAL(triggered(bool)),optiondialog.OptionDialog,SLOT(show()));
        connect(menubar.channels,SIGNAL(triggered(bool)),channelsdialog.ChannelsDialog,SLOT(show()));
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

        addToolBar(toolbar.tool_bar);
        toolbar.tool_bar->show();

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
        optiondialog.spin_sum_max->setValue(9000);
        optiondialog.spin_sum_min->setValue(10);

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
        qDebug() << _filename;
        if(_filename.size()==0) return;

        unsigned long ix = 0;
        unsigned long iy = 0;

        QString str;
        QString mark;

        QVector<double> y_x1;
        QVector<double> x_x1;
        QVector<double> y_x2;
        QVector<double> x_x2;
        QVector<double> y_y1;
        QVector<double> x_y1;
        QVector<double> y_y2;
        QVector<double> x_y2;

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
        for(auto filename : _filename){
              _rd = new RawData(filename,_opt);
              for(auto rd : _rd->vRawData){
                      switch(rd.code){
                      case 1:
                              mark = "x2";
                              vectorFindOrAdd(&x_x2,&y_x2,rd.value);
                              break;
                      case 3:
                              mark = "y2";
                              vectorFindOrAdd(&x_y2,&y_y2,rd.value);
                              break;
                      case 5:
                              mark = "x1";
                              vectorFindOrAdd(&x_x1,&y_x1,rd.value);
                              break;
                      case 7:
                              mark = "y1";
                              vectorFindOrAdd(&x_y1,&y_y1,rd.value);
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

                      ix = (unsigned long)_resolution*fd.x1/(fd.x1+fd.x2);
                      iy = (unsigned long)_resolution*fd.y1/(fd.y1+fd.y2);
                      //qDebug() << ix << " : " << iy;

                      _nd->data_matrix->set(ix,iy,
                              _nd->data_matrix->get(ix,iy)+1.0
                      );

              }

              channelsdialog.plot_x1->addPlot(x_x1,y_x1,"x1","red");
              channelsdialog.plot_x2->addPlot(x_x2,y_x2,"x2","red");
              channelsdialog.plot_y1->addPlot(x_y1,y_y1,"y1","blue");
              channelsdialog.plot_y2->addPlot(x_y2,y_y2,"y2","blue");


        }

        plot2d->buildNeutronData(_nd);

        str = "all neutrons: "+QString::number(count)+", correct: "+QString::number(count-fail_count)+", "+QString::number(100.0*(count-fail_count)/count)+"%";
        this->statusBar()->showMessage(str);

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

void MainWindow::applyOptions(){
        _opt.max_sum = optiondialog.spin_sum_max->value();
        _opt.min_sum = optiondialog.spin_sum_min->value();
        _opt.lambda = optiondialog.spin_lambda->value();
        _opt.size_of_detector = optiondialog.spin_size->value();
        _opt.source_detector = optiondialog.spin_ds->value();
}
