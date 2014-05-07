#include "S_1.h"

S_1::S_1()
{
  kp = 250;
  ap = 80;
  o = 250;
  u = 495;
}

double S_1::cTR(double g)
{
  return g * (PI / 180);
}
   
double S_1::cTG(double r)
{
  return r * (180 / PI);
}
   
void S_1::initialize()
{
      c = 0;
      xx = 0;
      d = 170;
      dv = 0;
      uv = 0;
      alpha = 0;
      beta = 0;
      gamma = 0;
      delta = 0;
      epsilon = 0;
      alphaMotor = 0;
} 
   
double S_1::S1(double x, double y, double z)
{
  initialize();
  dv = y;
  d -= dv;
  xx = x;
  
  uv = sqrt((pow(u, 2)) - (pow(xx, 2)));
  
  c = sqrt((pow(d, 2)) + (pow(z, 2)));
  
  if (d < 0) { 
    d -= 2 * d; gamma = asin(d / c) + cTR(90); 
  }
  else { 
    gamma = asin(z / c); 
  }
  
  delta = acos((pow(o, 2) + pow(c, 2) - pow(uv, 2)) / (2 * o * c));
  
  alphaMotor = gamma + delta;
  return cTG(alphaMotor);
}
