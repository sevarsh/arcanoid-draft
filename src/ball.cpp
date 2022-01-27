#include "ball.h"
#include <cmath>

ball_c:: ball_c(): circle_c(9, vector2_c(0.0, 0.0), color_c(1, 0, 0)), velocity(vector2_c(0, 0.5))
{};

bool ball_c::IsMoving()
{
  if (velocity == vector2_c())
    return false;
  return true;
}

void ball_c::Draw()
{
  circle_c::Draw();
}

void ball_c::Reflection(const vector2_c &normal)
{
  velocity.Reflection(normal);
}

void ball_c::SetStartPlace(platform_c &platform)
{
  velocity = vector2_c(0, 0);
  vector2_c platCenter = platform.GetPivotPoint();
  double platWidth = platform.GetSize().GetY();
  SetPivotPoint(vector2_c(platCenter.GetX(), platCenter.GetY() + platWidth/2 + radius));
}

void ball_c::MoveBallWithPlatform(int dx)
{
  pivotPoint = vector2_c(pivotPoint.GetX() + dx, pivotPoint.GetY());
}

void ball_c::MoveBall()
{
  pivotPoint += velocity; 
}

bool ball_c::IsBlockHit(block_c &block)
{
  int blockCenterY = block.GetPivotPoint().GetY();
  vector2_c ballSpeedY = GetVelocity().projY();
  vector2_c ballSpeedX = GetVelocity().projX();
  vector2_c dist = pivotPoint - block.GetPivotPoint();

  if ((abs(dist.GetY()) <= radius + block.GetSize().GetY() / 2) 
      && (abs(dist.GetX()) <= block.GetSize().GetX() / 2))
  {
    if (dist.isOppositeProjY(ballSpeedY))
    {
      ChangeVelocity(-2 * ballSpeedY);
      return true;
    }
  }

  if ((abs(dist.GetX()) <= radius + block.GetSize().GetX() / 2)
    && (abs(dist.GetY()) <= block.GetSize().GetY() / 2))
  {
    ChangeVelocity(-2 * ballSpeedX);
    return true;
  }
  return false;
}

bool ball_c::isBallOnPlatform(platform_c &platform)
{
  vector2_c dist = pivotPoint - platform.GetPivotPoint();

  if ((abs(dist.GetY()) <= radius + platform.GetSize().GetY() / 2)
    && (abs(dist.GetX()) <= platform.GetSize().GetX() / 2))
    return true;

  return false;
}

void ball_c::IsPlatformHit(platform_c &platform)
{
  if (isBallOnPlatform(platform) && velocity.GetY() <= 0)
    Reflection(platform.GetNormal(pivotPoint));
}

void ball_c::CheckWallsHit(const vector2_c &gamespace)
{
  if (pivotPoint.GetX() - radius <= 0 || pivotPoint.GetX() + radius >= gamespace.GetX())
    velocity -= 2 * velocity.projX();
  if (pivotPoint.GetY() + radius >= gamespace.GetY())
    velocity -= 2 * velocity.projY();
}  