#include "figure.h"

rectangle_c::rectangle_c(const vector2_c &size, const vector2_c &peak, const color_c &color) :
  size(size), figure_c(peak, color) {};

vector2_c rectangle_c::GetSize()
{
  return size;
}

void DrawLine(const vector2_c& point, const vector2_c& delta)
{
  glBegin(GL_LINES);
  point.Draw(0, 0);
  point.Draw(delta.GetX(), delta.GetY());
  glEnd();
}

void rectangle_c::DrawFrame()
{
  double leftX = pivotPoint.GetX() - size.GetX() / 2;
  double rightX = pivotPoint.GetX() + size.GetX() / 2;
  double topY = pivotPoint.GetY() + size.GetY() / 2;
  double lowY = pivotPoint.GetY() - size.GetY() / 2;

  glColor3d(0, 0, 0);
  glLineWidth(1);
  DrawLine(vector2_c(leftX, topY), vector2_c(size.GetX(), 0));
  DrawLine(vector2_c(rightX, topY), vector2_c(0, -size.GetY()));
  DrawLine(vector2_c(rightX, lowY), vector2_c(-size.GetX(), 0));
  DrawLine(vector2_c(leftX, lowY), vector2_c(0, size.GetY()));
}

void rectangle_c::Draw()
{
  color.Draw();
  glBegin(GL_POLYGON);

  double x = pivotPoint.GetX();
  double y = pivotPoint.GetY();
  double width = size.GetX();
  double heigth = size.GetY();

  glVertex2f(x - width / 2, y - heigth / 2);
  glVertex2f(x - width / 2, y + heigth / 2);
  glVertex2f(x + width / 2, y + heigth / 2);
  glVertex2f(x + width / 2, y - heigth / 2);

  glEnd();
  DrawFrame();
}
