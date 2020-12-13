/* mainwindow.h
 * Copyright 2019 13 Aug
 * Kirill Pshenichnyi
 * This part of InMageS (Inelastic Magnet Scattering)
 * Software for Build analitical data and processing experemental data
 */

#ifndef PLOT1D_H
#define PLOT1D_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVector>

#include "plot.h"

class Plot1D : public QWidget
{
    Q_OBJECT
public:
    Plot1D(QWidget *parent = nullptr);
    ~Plot1D();

    Plot *getPlot(){return plot;}

private:
    QVBoxLayout *layout;
    QHBoxLayout *tool_layout;
    QCPBars *bars = nullptr;

    Plot *plot;
    QPushButton *button_clean;
    QPushButton *button_rescale;

public slots:
    void cleanPlots(){plot->clearGraphs();plot->replot();}
    void addPlot(QVector<double> abscissa,QVector<double> ordinate,QString name= "", QString color="rand");
    void rescaleAxis();

};

#endif // PLOT1D_H
