#ifndef S_1_h
#define S_1_h

#include "Arduino.h"

class S_1{
  public:
    double kp;
    double ap;
    double o;
    double u;
    
    double c;
    double xx;
    double d;
    double dv;
    double uv;
    double alpha;
    double beta;
    double gamma;
    double delta;
    double epsilon;
    double alphaMotor;

    S_1();   
    double cTR(double g);
    double cTG(double r);
    void initialize();
    double S1(double x, double y, double z);
};
#endif
