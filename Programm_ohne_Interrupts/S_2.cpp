#include "S_2.h"

S_2::S_2(){
  kp = 250;
  ap = 80;
  o = 250;
  u = 495;
}

double S_2::cTR(double g)
{
  return g * (PI / 180);
}

double S_2::cTG(double r)
{
  return r * (180 / PI);
}

 void S_2::initialize()
{
  c = 0;
  yx = 0;
  yy = 0;
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

 double S_2::S2(double x, double y, double z)
{
  initialize();
  boolean yynegativ = false;
  dv = x / (sin(cTR(60)));
  d += dv;
  
  yx = (x * (sin(cTR(30)))) / (sin(cTR(60)));
  yy = y - yx;
  
  if (yy < 0) { yy -= 2 * yy; yynegativ = true; }
  
  beta = asin((yy * (sin(cTR(120)))) / u);
  
  if (yynegativ == true) { 
    alpha = cTR(120) - beta; 
  }
  else { 
    alpha = cTR(60) - beta; 
  }
  
  uv = (u * (sin(alpha))) / (sin(cTR(120)));
  
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
