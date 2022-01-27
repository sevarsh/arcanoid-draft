#pragma once
#include "glut.h"
class vector2_c {
public:
  vector2_c() : x(0.0), y(0.0) {};
  vector2_c(double x, double y) : x(x), y(y) {};
  ~vector2_c() {};

  double GetX() const { return x; };
  double GetY() const { return y; };

  void SetX(const double& value) { x = value; };
  void SetY(const double& value) { y = value; };

  vector2_c& scaleX(const double& val) { x *= val; return *this; }
  vector2_c& scaleY(const double& val) { y *= val; return *this; }

  double Length() const;

  double Dot(const vector2_c& vector) const;
  friend vector2_c operator*(const double& number, const vector2_c vector);
  vector2_c operator-(const vector2_c& vector) const;
  vector2_c operator+(const vector2_c& vector) const;
  vector2_c& operator*=(const double& num);
  vector2_c& operator+=(const vector2_c& vector);
  vector2_c& operator-=(const vector2_c& vector);
  vector2_c& operator-();

  vector2_c(const vector2_c& vec);
  vector2_c& operator=(const vector2_c& vec);
  bool operator==(const vector2_c& vec);

  vector2_c projX()const { return vector2_c(x, 0); };
  vector2_c projY()const { return vector2_c(0, y); };
  double VecToVecProj(const vector2_c& vector) const;
  bool isOppositeProjX(const vector2_c& vec);
  bool isOppositeProjY(const vector2_c& vec);

  void Reflection(const vector2_c& normal);

  void Draw(double dx, double dy) const { glVertex2d(x + dx, y + dy); };

private:
  double x, y;
};