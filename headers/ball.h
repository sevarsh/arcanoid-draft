#pragma once
#include "vector.h"
#include "color.h"
#include "figure.h"

#include "platform.h"
#include "block.h"

class ball_c : public circle_c {
public:
  ball_c();

  void SetVelocity(const vector2_c &shift) { velocity = shift; };
  bool IsMoving();
  void Reflection(const vector2_c &normal);
  vector2_c GetVelocity() const { return velocity; };

  bool IsBlockHit(block_c &block);
  void IsPlatformHit(platform_c &platform);
  void CheckWallsHit(const vector2_c &gamespace);

  void SetStartPlace(platform_c &platform);
  void MoveBallWithPlatform(int dx);
  void MoveBall();
  bool isBallOnPlatform(platform_c &platform);

  void Draw();
private:
  vector2_c velocity;
  void ChangeVelocity(const vector2_c &vec) { velocity += vec; };
};

struct gameObjects_t {
  platform_c* platform;
  ball_c* ball;
};
