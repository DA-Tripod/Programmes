#ifndef S_3_h
#define S_3_h

#include "Arduino.h"
 class S_3
{  
  public:
    double kp;
    double ap;
    double o;
    double u;
    
    double c;
    double yx;
    double yy;
    double d;
    double dv;
    double uv;
    double alpha;
    double beta;
    double gamma;
    double delta;
    double epsilon;
    double alphaMotor;
    
    S_3();
    double cTR(double g);
    double cTG(double r);
    void initialize();
    double S3(double x, double y, double z);
};
#endif
