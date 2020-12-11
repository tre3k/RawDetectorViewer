#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QFileDialog>
#include <QDebug>

#include "plot2d.h"
#include "rawdata.h"

class MainWindow : public QMainWindow
{
        Q_OBJECT
public:
        explicit MainWindow(QWidget *parent = nullptr);

private:
        Plot2D *plot2d;
        int _resolution = 256;
        NeutronData *_nd = nullptr;
        RawData *_rd = nullptr;
        RawData::s_options _opt;

        struct s_datalistdialog{
                QDialog *DataListDialog;
                QVBoxLayout *layout_central;
                QTabWidget *tab_widget;
                QWidget *widget_tab1;
                QWidget *widget_tab2;
                QVBoxLayout *layout_tab1;
                QVBoxLayout *layout_tab2;
                QListWidget *list_values;
                QListWidget *list_raw;
                QHBoxLayout *layout_push_button;
                QPushButton *push_button_ok;
        } datalistdialog;
        void buildDataListDialog();

        struct s_menubar{
                QMenuBar *menu_bar;
                QMenu *file;
                QAction *open;
                QAction *quit;

                QMenu *edit;
                QAction *option;
                QAction *datalist;
        } menubar;
        void buildMenuBar(void);

        struct s_toolbar{
                QToolBar *tool_bar;
                QPushButton *push_button_update;
                QComboBox *combo_box_resolution;
        } toolbar;
        void buildToolBar(void);

        QString _filename;

signals:

public slots:
        void openFile(void){
                _filename = QFileDialog::getOpenFileName(nullptr,"open *.raw file","","*.raw");
                loadFile();
        }
        void loadFile(void);
        void changeResolution(int index);

};

#endif // MAINWINDOW_H
