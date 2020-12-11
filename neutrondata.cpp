/* mainwindow.h
 * Copyright 2019 Aug
 * Kirill Pshenichnyi
 * This part of InMageS (Inelastic Magnet Scattering)
 * Software for Build analytical data and processing experemental data
 */

#include "neutrondata.h"


NeutronData::NeutronData(unsigned long x, unsigned long y)
{
    Nx = x;
    Ny = y;

    data_matrix = new Data2D(Nx,Ny);
}

void NeutronData::resize(unsigned long int x, unsigned long int y){
    data_matrix->del();
    Nx = x; Ny = y;
    data_matrix->init(x,y);
}

NeutronData::~NeutronData(){
    delete data_matrix;
}

void NeutronData::setWaveLenght(double l){lambda = l;}                  // Angstrom
void NeutronData::setDistanceSD(double Dsd){D = Dsd;}                   // meters
void NeutronData::setSizePixelOfSizeX(double pixel_x){px = pixel_x;}    // in mm
void NeutronData::setSizePixelOfSizeY(double pixel_y){py = pixel_y;}    // in mm
void NeutronData::setDlpxpy(double DistanceSD, double wavelenght, double pixel_x_mm, double pixel_y_mm){
    setDistanceSD(DistanceSD);
    setWaveLenght(wavelenght);
    setSizePixelOfSizeX(pixel_x_mm);
    setSizePixelOfSizeY(pixel_y_mm);

    update_max_wt();
}

/* caclculate wave vector and theta from Nx(count pixels),Ny,px(size of pixel),py and Distance */
void NeutronData::update_max_wt(){
    Lx = Nx*px/1000;         // size of detector [m]
    Ly = Ny*py/1000;

    theta_max_x = atan(Lx/2/D);
    theta_max_y = atan(Ly/2/D);

    update_ki_Ei();
    wave_vector_max_x = ki*theta_max_x;
    wave_vector_max_y = ki*theta_max_y;
}

/* calculate WaveVector and Energy incedent neutron from lambda */
void NeutronData::update_ki_Ei(){
    ki = 2.0*M_PI/lambda/1e-10;
    Ei = WaveVectorToImpulse(ki)*WaveVectorToImpulse(ki)/2.0/cmn();
}

double NeutronData::get_ki_A(){ update_ki_Ei();return ki*1e-10;}
double NeutronData::get_ki_nm(){update_ki_Ei();return ki*1e-9;}
double NeutronData::get_ki(){update_ki_Ei(); return ki;}

double NeutronData::get_maxQx_A(){update_max_wt(); return wave_vector_max_x*1e-10;}
double NeutronData::get_maxQy_A(){update_max_wt(); return wave_vector_max_y*1e-10;}
double NeutronData::get_maxQx_nm(){update_max_wt(); return wave_vector_max_x*1e-9;}
double NeutronData::get_maxQy_nm(){update_max_wt(); return wave_vector_max_y*1e-9;}

double NeutronData::getMaximumThetaX(){update_max_wt(); return theta_max_x;}
double NeutronData::getMaximumThetaY(){update_max_wt(); return theta_max_y;}
double NeutronData::getMaximumThetaXmrad(){return getMaximumThetaX()*1000;}
double NeutronData::getMaximumThetaYmrad(){return getMaximumThetaY()*1000;}

double NeutronData::getEi_Joul(){    update_ki_Ei(); return Ei;}
double NeutronData::getEi_K(){return getEi_Joul()/ckB();}
double NeutronData::getEi_meV(){return getEi_Joul()*1000/ce();}

unsigned long int NeutronData::size_Nx(){
    return Nx;
}

unsigned long int NeutronData::size_Ny(){
    return Ny;
}
