#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QFileDialog>
#include <QDebug>
#include <QCheckBox>
#include <QPushButton>
#include <QAction>
#include <QDoubleSpinBox>

#include "plot2d.h"
#include "plot1d.h"
#include "rawdata.h"

class MainWindow : public QMainWindow
{
        Q_OBJECT
public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

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

        struct s_optiondialog{
                QDialog *OptionDialog;
                QFormLayout *layout;
                QPushButton *button_ok;
                QPushButton *button_apply;
                QPushButton *button_close;

                QSpinBox *spin_sum_max;
                QSpinBox *spin_sum_min;

                QDoubleSpinBox *spin_ds;
                QDoubleSpinBox *spin_lambda;
                QDoubleSpinBox *spin_size;

        } optiondialog;
        void buildOptionDialog();

        struct s_channelsdialog{
                QDialog *ChannelsDialog;
                QVBoxLayout *layout;
                QTabWidget *tab_widget;
                QVBoxLayout *layout_tab1;
                QVBoxLayout *layout_tab2;
                QWidget *widget_tab1;
                QWidget *widget_tab2;

                Plot1D *plot_x1;
                Plot1D *plot_x2;
                Plot1D *plot_y1;
                Plot1D *plot_y2;

        } channelsdialog;
        void buildChannelsDialog();

        struct s_boxaveragedialog{
                QDialog *boxaveragedialog;

                QVBoxLayout *layout;
                QHBoxLayout *layout_button;
                QFormLayout *layout_form;

                QDoubleSpinBox *spinbox_center_x;
                QDoubleSpinBox *spinbox_center_y;
                QDoubleSpinBox *spinbox_w;
                QDoubleSpinBox *spinbox_h;

                QLabel *label_neutron_sum;

                QPushButton *button_average;
                QPushButton *button_close;
        } boxaveragedialog;
        void buildBoxAverageDialog(void);

        struct s_menubar{
                QMenuBar *menu_bar;
                QMenu *file;
                QAction *open;
                QAction *quit;

                QMenu *edit;
                QAction *box_average;
                QAction *option;
                QAction *datalist;
                QAction *channels;
        } menubar;
        void buildMenuBar(void);

        struct s_toolbar{
                QToolBar *tool_bar;
                QPushButton *push_button_update;
                QComboBox *combo_box_resolution;

                QCheckBox *check_x = nullptr, *check_y = nullptr;
        } toolbar;
        void buildToolBar(void);

        QStringList _filenames;
        int vectorFindOrAdd(QVector<double> *vector,QVector<double> *y,double value);  //retunr index value at vector, or add value to vector and return index


signals:

public slots:
        void openFile(void){
                _filenames = QFileDialog::getOpenFileNames(nullptr,"open *.raw file","","*.raw");
                loadFile();
        }
        void loadFile(void);
        void changeResolution(int index);
        void applyOptions();
        void paintBox(double center_x, double center_y, double h, double w);
        void averageBoxChanged(double value);

};

#endif // MAINWINDOW_H
