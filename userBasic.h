
#ifndef HEADER_USER_DEFINED_USERBASIC
#define HEADER_USER_DEFINED_USERBASIC


#include "userHeader.h"


/*********Check the idle time**********/
double checkWindowsTime(void); // check the windows time in [ms]
void idleTime(double deltTime, double currentTime, double timeBuff[]);

/***********Data Storage**************/
void writeTextFile(char name[], int k, double TOTALNUM, double data1[], double data2[], double data3[]);
void readTextFile(char name[], double TOTALNUM, double data1[], double data2[], double data3[]);


void bandPassFilter(double Vmre[], double dataNum, double Vmref[]);
double zeroCrossing_orig(double Vmre, double* past, double* present, double time, double zctime[], int* iter);
double zeroCrossing(double Vmre[], int dataNum, double time, int iter);
char motorRotation(double freq, int* pastStep, int* presentStep, int* direction);

double mre_freq(double _x_re[], double _x_im[], double _X_re[], double _X_im[], double fft_mag[]);
void fft(double _x_re[], double _x_im[], double _X_re[], double _X_im[]);

#endif