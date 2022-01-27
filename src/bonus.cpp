#include "bonus.h"
#include <iostream>

#define INCREASE_VAL_PLAT 2
#define DECREASE_VAL_PLAT 1./2
#define INCREASE_VAL_BALL 1.6
#define DECREASE_VAL_BALL 0.625

bonus_c::bonus_c() : 
  curState(PASSIVE), time(10000), circle_c(4, vector2_c(0.0, 0.0), color_c(1, 1, 1)) {}

bonus_c::bonus_c(color_c color) : 
  curState(PASSIVE), time(10000), circle_c(4, vector2_c(0.0, 0.0), color_c(color)) {}

good_bonus_c::good_bonus_c() : 
  bonus_c(color_c(0.49, 0.99, 0)) {}

bad_bonus_c::bad_bonus_c() : 
  bonus_c(color_c(0, 0, 0)) {}

enlarge_platform_c::enlarge_platform_c(){
  type = ENLARGE_PLATFORM;
}

cut_platform_c::cut_platform_c() {
  type = CUT_PLATFORM;
}

cut_ball_speed_c::cut_ball_speed_c() {  
  type = CUT_BALL_SPEED; 
}

increase_ball_speed_c::increase_ball_speed_c(){
  type = INCREASE_BALL_SPEED;
}

naughty_ball_c:: naughty_ball_c() {
  type = NAUGHTY_BALL;
}

ball_stick_c::ball_stick_c() : good_bonus_c() {
  type = CHANGE_BALL_STICK;
};

safe_board_c::safe_board_c() : good_bonus_c() {
  type = ADD_SAFE_BOARD;
};

bool bonus_c::isInGameArea()
{
  if (pivotPoint.GetY() - radius <= 0)
    return false;
  return true;
}

bool bonus_c::isCatched(platform_c &platform)
{
  vector2_c platCenter = platform.GetPivotPoint();
  int platLeftBoard = platCenter.GetX() - platform.GetSize().GetX() / 2;
  int platRightBoard = platCenter.GetX() + platform.GetSize().GetX() / 2;
  int bonusLowPoint = pivotPoint.GetY() - radius;
  int bonusCenterX = pivotPoint.GetX();

  if (bonusLowPoint == platCenter.GetY() &&
    platLeftBoard <= bonusCenterX && bonusCenterX <= platRightBoard)
    return true;

  return false;
}

bool bonus_c::processBonus(gameObjects_t obj)
{
  time--;
  if (time == 0)
  {
    turnOffBonus(obj);
    return false;
  }
  doBonus(obj);
  return true;
}

bool cut_platform_c::turnOnBonus(gameObjects_t obj)
{
  if (obj.platform->ChangePlatformSize(DECREASE_VAL_PLAT))
  {
    curState = ACTIVE;
    return true;
  }
  return false;
}

void cut_platform_c::turnOffBonus(gameObjects_t obj)
{
  obj.platform->ChangePlatformSize(INCREASE_VAL_PLAT);
}

bool enlarge_platform_c::turnOnBonus(gameObjects_t obj)
{
  if (obj.platform->ChangePlatformSize(INCREASE_VAL_PLAT))
  {
    curState = ACTIVE;
    return true;
  }
  return false;
}

void enlarge_platform_c::turnOffBonus(gameObjects_t obj)
{
  obj.platform->ChangePlatformSize(DECREASE_VAL_PLAT);
}

bool cut_ball_speed_c::turnOnBonus(gameObjects_t obj)
{
  curState = ACTIVE;
  obj.ball->SetVelocity(obj.ball->GetVelocity() *= DECREASE_VAL_BALL);
  return true;
}

void cut_ball_speed_c::turnOffBonus(gameObjects_t obj)
{
  obj.ball->SetVelocity(obj.ball->GetVelocity() *= INCREASE_VAL_BALL);
}

bool increase_ball_speed_c::turnOnBonus(gameObjects_t obj)
{
  curState = ACTIVE;
  obj.ball->SetVelocity(obj.ball->GetVelocity() *= INCREASE_VAL_BALL);
  return true;
}

void increase_ball_speed_c::turnOffBonus(gameObjects_t obj)
{
  obj.ball->SetVelocity(obj.ball->GetVelocity() *= DECREASE_VAL_BALL);
}

bool naughty_ball_c::turnOnBonus(gameObjects_t obj)
{
  curState = ACTIVE;
  return true;
}

bool ball_stick_c::turnOnBonus(gameObjects_t obj)
{
  curState = ACTIVE;
  return true;
}

bool safe_board_c::turnOnBonus(gameObjects_t obj)
{
  curState = ACTIVE;
  return true;
}

void naughty_ball_c::doBonus(gameObjects_t obj)
{
  if (time % 1000 == 0)
    obj.ball->SetVelocity(-obj.ball->GetVelocity());
}

void ball_stick_c::doBonus(gameObjects_t obj)
{
  if (obj.ball->isBallOnPlatform(*obj.platform))
    obj.ball->SetVelocity(vector2_c(0, 0));
}