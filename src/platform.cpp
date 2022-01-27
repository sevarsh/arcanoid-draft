#include "platform.h"
#include <cmath>
#define WIDTH 100
#define HEIGHT 5

platform_c::platform_c(const vector2_c &window) :
  rectangle_c(vector2_c(WIDTH, HEIGHT), vector2_c(window.GetX()/ 2, HEIGHT*1.2), color_c(0.66, 0.53, 0.31)), 
  sizeLimits({ 10, window.GetX() }), lifes(5)
{};

platform_c:: platform_c(const vector2_c &size, const vector2_c &peak, const color_c &color) :
  rectangle_c(size, peak, color), sizeLimits({ 10, 400 }), lifes(5)
{};

void platform_c::CutLifes()
{ 
  lifes--; 
}

int platform_c::GetLifes() const
{ 
  return lifes; 
}

bool platform_c::ChangePlatformSize(double number)
{
  int distLBoard = pivotPoint.GetX() - size.GetX()*number / 2;
  int distRBoard = pivotPoint.GetX() + size.GetX()*number / 2;

  if (size.GetX()*number > sizeLimits.minSize && size.GetX()*number < sizeLimits.maxSize)
  {
    if (distLBoard <= 0)
      pivotPoint += vector2_c(abs(distLBoard), 0);
    else if (distRBoard >= sizeLimits.maxSize)
      pivotPoint -= vector2_c((distRBoard - sizeLimits.maxSize), 0);

    size.scaleX(number);
    return true;
  }
  return false;
}

vector2_c platform_c::GetNormal(const vector2_c &point)
{
  if (point.GetX() < pivotPoint.GetX() - size.GetX()/2)
    return vector2_c(-0.5, 0.5);
  if (point.GetX() > pivotPoint.GetX() + size.GetX()/2)
    return vector2_c(0.5, 0.5);

  double x = point.GetX() - pivotPoint.GetX() + size.GetX()/2;
  int width = size.GetX() / 2;
  double delta = abs(x - width) / (abs(x - width) + 2 * width);

 if (x >= width)
    return vector2_c(delta, 1 - delta);
  else
    return vector2_c(-delta, 1 - delta); 
};

bool platform_c::MovePlatform(int dx)
{
  double x = GetPivotPoint().GetX();
  if (x + size.GetX()/2 + dx > sizeLimits.maxSize)
    return false;
  else if (x - size.GetX() / 2 + dx < 0)
    return false;
  else
    pivotPoint.SetX(x + dx);
  return true;
}

void platform_c::Draw()
{
  rectangle_c::Draw();
}

//if (ballCenter.GetY() <= pivotPoint.GetY() + size.GetY() / 2. &&
  //  ballCenter.GetY() >= pivotPoint.GetY() - size.GetY() / 2. &&
  //  abs((ballCenter - pivotPoint).GetX()) <= ball.GetRadius() + size.GetX() / 2)
  //  return true;
  //return false;