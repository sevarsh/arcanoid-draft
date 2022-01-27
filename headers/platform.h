#pragma once
#include "figure.h"
#include "vector.h"
#include "block.h"
#include "color.h"

struct platSizeLimits_t {
  double minSize;
  double maxSize;
};

class platform_c: public rectangle_c {
public:
  platform_c(const vector2_c &window);
  platform_c(const vector2_c &size, const vector2_c &peak, const color_c &color);

  bool ChangePlatformSize(double number);
  bool MovePlatform(int dx);

  void CutLifes();
  int GetLifes() const;

  vector2_c GetNormal(const vector2_c &point);
  void Draw();

protected:
  platSizeLimits_t sizeLimits;
  int lifes;
};
