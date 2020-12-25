/* mainwindow.h
 * Copyright 2019 Aug
 * Kirill Pshenichnyi
 * This part of InMageS (Inelastic Magnet Scattering)
 * Software for Build analytical data and processing experemental data
 */

#include "data2d.h"

Data2D::Data2D(unsigned long int x, unsigned long int y)
{
    init(x,y);
}

Data2D::~Data2D(){
    del();
}

void Data2D::del(){
    for(unsigned long int i=0;i<sx;i++) delete [] data[i];
    delete data;
}

void Data2D::init(unsigned long int x,unsigned long int y){
    sx = x;
    sy = y;

    if(x!=0 || y!=0){
        data = new double *[sx];
        for(unsigned long int i=0;i<sx;i++) data[i] = new double [y];

        /* zero all data array */
        for(unsigned long int i=0;i<sx;i++)
            for(unsigned long int j=0;j<sy;j++) data[i][j] = 0.0;
    }
}

unsigned long int Data2D::size_x(){
    return sx;
}

unsigned long int Data2D::size_y(){
    return sy;
}

double Data2D::at(unsigned long x, unsigned long y){
    if(!(x>=sx || y>=sy || x<0 || y<0)) return data[x][y];
    err = -1;
    return 0.0;
}

void Data2D::set(unsigned long x, unsigned long y, double value){
    if((x<sx)||(y<sy)) data[x][y] = value;
    return;
}

double Data2D::get(unsigned long x, unsigned long y){
        if((x<sx)||(y<sy)) return data[x][y];
        return 0.0;
}

void Data2D::copy(Data2D *array){
    del();
    init(array->size_x(),array->size_y());
    for(unsigned long int i=0;i<sx;i++){
        for(unsigned long int j=0;j<sy;j++){
            set(i,j,array->at(i,j));
        }
    }
}

int Data2D::errNo(){
    return err;
}

void Data2D::exportTxt(QString filename){
        QFile f(filename);
        f.open(QIODevice::WriteOnly);
        QTextStream ts(&f);

        ts << "# Data matrix " << QString::number(sx) << "x" << QString::number(sy) << Qt::endl;
        for(unsigned long j=0;j<sy;j++){
                for(unsigned long i=0;i<sx;i++){
                        ts << QString::number(get(i,j)) << " ";
                }
                ts << Qt::endl;
        }
        f.close();
}
