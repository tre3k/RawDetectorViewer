/* mainwindow.h
 * Copyright 2019 14 Aug
 * Kirill Pshenichnyi
 * This part of InMageS (Inelastic Magnet Scattering)
 * Software for Build analitical data and processing experemental data
 */

#include <QString>
#include <QFile>
#include <QTextStream>

#ifndef DATA2D_H
#define DATA2D_H

class Data2D
{
public:
    Data2D(unsigned long int x=0,unsigned long int y=0);
    ~Data2D();

    void init(unsigned long int size_x,unsigned long int size_y);
    unsigned long int size_x(void);
    unsigned long int size_y(void);

    double at(unsigned long int x, unsigned long int y);
    void set(unsigned long int x, unsigned long int y, double value);
    double get(unsigned long int x, unsigned long int y);
    void copy(Data2D *array);
    int errNo(void);
    void del(void);
    void exportTxt(QString filename);

private:
    unsigned long int sx;
    unsigned long int sy;
    double **data;

    int err;
};

#endif // DATA2D_H
