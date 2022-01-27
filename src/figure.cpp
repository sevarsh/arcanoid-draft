#include "figure.h"

void figure_c::SetColor(const color_c &newColor) 
{ 
  color = newColor; 
}

void figure_c::SetPivotPoint(const vector2_c &point) 
{ 
  pivotPoint = point; 
}

vector2_c figure_c::GetPivotPoint() const
{ 
  return pivotPoint; 
}
