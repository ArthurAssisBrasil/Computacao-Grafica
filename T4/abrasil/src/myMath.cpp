/***
    algumas funcoes matematicas
***/
#include "myMath.h"
#include <math.h>

double distanciaPts(double x1, double y1, double z1, double x2, double y2, double z2){
    return sqrt(pow((x2-x1),2) + pow((y2-y1),2) + pow((z2-z1),2));
}

double grauParaRad(double ang){
    return ang*M_PI/180.0;
}

double radParaGrau(double ang){
    return ang*180.0/M_PI;
}

double angVetores(double x1, double y1, double z1, double x2, double y2, double z2){
    return radParaGrau( acos( (x1*x2 + y1*y2 + z1*z2) / (sqrt(pow(x1, 2) + pow(y1, 2) + pow(z1, 2)) * sqrt(pow(x2, 2) + pow(y2, 2) + pow(z2, 2)) ) ));
}
