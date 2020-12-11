#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
        plot2d = new Plot2D();

        this->setCentralWidget(plot2d);
        buildToolBar();
}

void MainWindow::buildToolBar(){
        toolbar.tool_bar = new QToolBar();
        toolbar.combo_box_resolution = new QComboBox();

        toolbar.combo_box_resolution->addItem("128x128");
        toolbar.combo_box_resolution->addItem("256x256");
        toolbar.combo_box_resolution->addItem("512x512");
        toolbar.combo_box_resolution->addItem("1024x1024");
        toolbar.combo_box_resolution->addItem("2048x2048");
        toolbar.combo_box_resolution->addItem("4096x4096");

        toolbar.tool_bar->addWidget(new QLabel("resolution: "));
        toolbar.tool_bar->addWidget(toolbar.combo_box_resolution);

        addToolBar(toolbar.tool_bar);
        toolbar.tool_bar->show();
}
