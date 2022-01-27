#include "vector.h"
#include <cmath>

void vector2_c::Reflection(const vector2_c& normal)
{
  vector2_c temp(normal);
  double coefficient = 2 * Dot(normal) / normal.Dot(normal);
  temp *= coefficient;
  *this -= temp;
}

double vector2_c::Dot(const vector2_c& vector) const
{
  return (GetX() * vector.GetX() + GetY() * vector.GetY());
}

double vector2_c::Length() const
{
  return sqrt(x*x + y*y);
}

vector2_c operator*(const double& number, const vector2_c vector)
{
  return vector2_c(vector.GetX()*number, vector.GetY()*number);
}

vector2_c vector2_c::operator-(const vector2_c& vector) const
{
  return vector2_c(x - vector.GetX(), y - vector.GetY());
}

vector2_c vector2_c::operator+(const vector2_c& vector) const
{
  return vector2_c(x + vector.GetX(), y + vector.GetY());
}

vector2_c& vector2_c::operator*=(const double& num)
{
  x *= num;
  y *= num;
  return *this;
}

vector2_c& vector2_c::operator+=(const vector2_c& vector)
{
  x += vector.GetX();
  y += vector.GetY();
  return *this;
}

vector2_c& vector2_c::operator-=(const vector2_c& vector)
{
  x -= vector.GetX();
  y -= vector.GetY();
  return *this;
}

vector2_c& vector2_c::operator-()
{
  x = -x;
  y = -y;
  return *this;
}

double vector2_c::VecToVecProj(const vector2_c& vector) const
{
  return Dot(vector) / vector.Length();
}

vector2_c::vector2_c(const vector2_c& vec)
{
  x = vec.GetX();
  y = vec.GetY();
}

vector2_c& vector2_c::operator=(const vector2_c& vec)
{
  x = vec.GetX();
  y = vec.GetY();
  return *this;
}

bool vector2_c::operator==(const vector2_c& vec)
{
  return ((x == vec.GetX()) && (y == vec.GetY()));
}

bool vector2_c::isOppositeProjX(const vector2_c& vec)
{
  if (x < 0 && vec.GetX() >= 0 || x > 0 && vec.GetX() <= 0)
    return true;
  return false;
}

bool vector2_c::isOppositeProjY(const vector2_c& vec)
{
  if (y < 0 && vec.GetY() >= 0 || y > 0 && vec.GetY() <= 0)
    return true;
  return false;
}