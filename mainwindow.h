#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>

#include "plot2d.h"

class MainWindow : public QMainWindow
{
        Q_OBJECT
public:
        explicit MainWindow(QWidget *parent = nullptr);

private:
        Plot2D *plot2d;

        struct s_toolbar{
                QToolBar *tool_bar;
                QPushButton *push_button_update;
                QComboBox *combo_box_resolution;
        } toolbar;
        void buildToolBar();

signals:

};

#endif // MAINWINDOW_H
