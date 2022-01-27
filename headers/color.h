#pragma once
#include "glut.h"

class color_c {
public:
  color_c() : red(0.0), green(0.0), blue(0.0), alpha(0.0) {};
  color_c(double red, double green, double blue) : red(red), green(green), blue(blue), alpha(1) {};
  ~color_c() {};
  
  void SetColor(const double &redValue, const double &greenValue, const double &blueValue);
  void CutIntensity() { alpha*=0.9; };
  void Draw() { glColor4d(red, green, blue, alpha); };

private:
  double red, green, blue;
  double alpha;
};
