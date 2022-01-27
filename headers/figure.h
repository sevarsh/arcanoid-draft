#pragma once
#include "vector.h"
#include "glut.h"
#include "color.h"

class figure_c {
public:
  figure_c() : pivotPoint(vector2_c()), color(color_c()) {};
  figure_c(const vector2_c &peak, const color_c &color) : pivotPoint(peak), color(color) {};
  virtual ~figure_c() {};

  void SetColor(const color_c &newColor);
  void SetPivotPoint(const vector2_c &point);

  vector2_c GetPivotPoint() const;
  virtual void Draw() = 0;

protected:
  vector2_c pivotPoint;
  color_c color;
};

class circle_c: public figure_c {
public:
  circle_c() : radius(0.0), figure_c() {};
  circle_c(double radius, const vector2_c &center, const color_c &color);
  ~circle_c() {};

  double GetRadius() const;
  void Draw();

protected:
  double radius;
private:
  void DoSegments();
};

class rectangle_c: public figure_c {

public:
  rectangle_c() : size{}, figure_c() {};
  rectangle_c(const vector2_c &size, const vector2_c &peak, const color_c &color);
  ~rectangle_c() {};

  vector2_c GetSize();

  void Draw();

protected:
  vector2_c size;

private:
  void DrawFrame();
};