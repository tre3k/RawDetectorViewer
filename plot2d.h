/* mainwindow.h
 * Copyright 2019 Aug
 * Kirill Pshenichnyi
 * This part of InMageS (Inelastic Magnet Scattering)
 * Software for Build analitical data and processing experemental data
 */


#ifndef PLOT2D_H
#define PLOT2D_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QComboBox>

#include "plot.h"
#include "neutrondata.h"

enum Units{
    UNIT_PIXEL,
    UNIT_ANGSTROM,
    UNIT_NM,
    UNIT_THETA,
    UNIT_REL
};

class Plot2D : public QWidget
{
    Q_OBJECT
public:
    explicit Plot2D(QWidget *parent = nullptr);

    void buildNeutronData(NeutronData *n_data);
    void buildNeutronData(void);
    void setNeutronData(NeutronData *n_data);
    int getCurrentUnit(void);
    Plot *getPlot(void){return plot;}

    double getRecoordX(double rel_x);
    double getRecoordY(double rel_y);
    int getCurrentUnits(void){return combo_select_units->currentIndex();}

protected:
    Plot *plot;

    QVBoxLayout *central_layout;
    QHBoxLayout *tool_layout;

    QDoubleSpinBox *spinBoxMax;
    QDoubleSpinBox *spinBoxMin;
    QCheckBox *check_hold;
    QCheckBox *check_log_scale;
    QComboBox *combo_select_units;
    QPushButton *buttonRescale;

    QCPColorMap *colorMap;
    QCPColorScale *colorScale;

    NeutronData *neutron_data = nullptr;


signals:
    void UnitsChanged(int);

public slots:
    void logScale(bool state);
    void hold(bool state);
    void setHoldRange();
    void setAxisUnit(int);
    void rescaleAxis();
    void changeDataRange(QCPRange);
    void setCurrentUnitIndex(int index);
};

#endif // PLOT2D_H
