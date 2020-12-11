/* mainwindow.h
 * Copyright 2019 14 Aug
 * Kirill Pshenichnyi
 * This part of InMageS (Inelastic Magnet Scattering)
 * Software for Build analitical data and processing experemental data
 */


#ifndef NEUTRONDATA_H
#define NEUTRONDATA_H

#include <math.h>
#include "data2d.h"

class NeutronData
{
public:
    NeutronData(unsigned long x=0, unsigned long y=0);
    ~NeutronData();

    /* resize Nx, Ny */
    void resize(unsigned long int x, unsigned long y);

    /* if you set lamda */
    void update_ki_Ei(void);

    /* if you set theta_max_x and Nx */
    //void update_D(void);        // calculate Distance soure to detector

    /* you need set D and L */
    void update_max_wt();       // calculate value of maximum for wave vector and theta

    /* set pixel resolution on x axies in [mm]*/
    void setSizePixelOfSizeX(double pixel_x);
    /* set pixel resolution on y axies in [mm]*/
    void setSizePixelOfSizeY(double pixel_y);
    /* set distance source to detector */
    void setDistanceSD(double Dsd);
    /* set WaveLenght (lambda) */
    void setWaveLenght(double l);
    /* set Magnet Field (Tesla) */
    void setMagnetField(double magnet_field){H=magnet_field;}
    /* set Dlpxpy */
    void setDlpxpy(double DistanceSD=1.0,              // Distance Source-Detector default 1 [m]
                   double wavelenght=1.0,                // WaveLenght default 1 [A]
                   double pixel_x_mm=1.0,          // size of pixel on x default 1 [mm]
                   double pixel_y_mm=1.0           // size of pixel on y default 1 [mm]
            );


    double get_ki_A();                                              // [1/Angstrom]
    double get_ki_nm();                                             // [1/nm]
    double get_ki();                                                // [1/m]

    /* get maximum wavevector */
    double get_maxQx_A();
    double get_maxQx_nm();
    double get_maxQy_A();
    double get_maxQy_nm();

    double getEi_Joul(void);                                        // Joul
    double getEi_meV(void);                                         // meV
    double getEi_K(void);                                           // Kelvin


    double getWaveLenght(void){return lambda;}
    double getDistanceSD(void);

    double getMaximumThetaX(void);                                  // in rad
    double getMaximumThetaY(void);
    double getMaximumThetaXmrad(void);                              // in mrad
    double getMaximumThetaYmrad(void);

    double getMagnetFieldT(void){return H;}                         // in Tesla


    static double cPlank(){return 6.626070040e-34;}                 // Plank constant   [Joul*s]
    static double ce(){return 1.60217662e-19;}                      // electron         [Kulon]
    static double cmn(){return 1.67492749804e-27;}                  // mass neutron     [kg]
    static double ckB(){return 1.3806504e-23;}                      // Bolzman constatn
    static double cgf(){return 2.00231930436153;}                   // g-factor
    static double cub(){return 927.4009682020e-26;}                 // Bor magnetron uB

    static double WaveVectorToImpulse(double value){                // value in [1/m]
        return cPlank()*value/2/M_PI;
    }

    unsigned long int size_Nx(void);
    unsigned long int size_Ny(void);


public:
    Data2D *data_matrix;

private:
    double D;                   // distance soruce to detetctor                      [m]
    double Ly;                  // size of detetcotor (size of pixel * resolution)   [m]
    double Lx;
    double px;                  // size of pixel                                     [mm]
    double py;

    double lambda;              // wave length of neutron                            [Angstrom 1e-10m]

    double H;                   // magnetField


private:
    double ki;                  // incedent wave vector neutron                      [1/m]
    double Ei;                  // incedent energy neutron                           [Joul]

    double theta_max_x;         // maximum theta                                     [mrad]
    double theta_max_y;
    double wave_vector_max_x;   // transmission maximum wavevector                   [1/m]
    double wave_vector_max_y;

    unsigned long Nx, Ny;

};



#endif // NEUTRONDATA_H
