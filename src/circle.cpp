#include "figure.h"
#include <cmath>

#define SEGMENTS 40

circle_c::circle_c(double radius, const vector2_c &center, const color_c &color) :
  radius(radius), figure_c(center, color) {};

double circle_c::GetRadius() const
{
  return radius;
}

void circle_c::DoSegments()
{
  float dx, dy, angle;
  int amountSegments = SEGMENTS;

  for (int i = 0; i < amountSegments; i++)
  {
    angle = 2.0 * 3.1415926 * float(i) / float(amountSegments);
    dx = radius * cosf(angle);
    dy = radius * sinf(angle);
    pivotPoint.Draw(dx, dy);
  }
}

void circle_c::Draw()
{
  color.Draw();
  glBegin(GL_TRIANGLE_FAN);
  DoSegments();
  glEnd();
  glColor3d(0, 0, 0);
  glBegin(GL_LINE_LOOP);
  DoSegments();
  glEnd();
}