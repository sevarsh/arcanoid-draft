#pragma once
#include "ball.h"

enum bonus_state_t {
  PASSIVE,
  NOT_DEFINED,
  ACTIVE
};

enum bonus_type_t {
  NAUGHTY_BALL,
  CHANGE_BALL_STICK,
  ADD_SAFE_BOARD,
  ENLARGE_PLATFORM,
  CUT_PLATFORM,
  INCREASE_BALL_SPEED,
  CUT_BALL_SPEED,
};

class bonus_c: public circle_c {

protected:
  bonus_state_t curState;
  bonus_type_t type;
  int time;

public:
  bonus_c();
  bonus_c(color_c color);

  virtual bool turnOnBonus(gameObjects_t obj) = 0;
  virtual void doBonus(gameObjects_t obj) = 0;
  virtual void turnOffBonus(gameObjects_t obj) = 0;

  void moveBonus() { pivotPoint += vector2_c(0, -0.5); };
  bool processBonus(gameObjects_t obj);

  void setBonusState(bonus_state_t state) { curState = state; }
  bool isInGameArea();
  bool isCatched(platform_c &platform);

  bonus_type_t getType() { return type; }
  bonus_state_t getState() { return curState; }
};

class good_bonus_c : public bonus_c {
protected:
  good_bonus_c();

  virtual bool turnOnBonus(gameObjects_t obj) = 0;
  virtual void doBonus(gameObjects_t obj) = 0;
  virtual void turnOffBonus(gameObjects_t obj) = 0;
};

class bad_bonus_c : public bonus_c {
protected:
  bad_bonus_c();

  virtual bool turnOnBonus(gameObjects_t obj) = 0;
  virtual void doBonus(gameObjects_t obj) = 0;
  virtual void turnOffBonus(gameObjects_t obj) = 0;
};

//изменение размеров платформы
class enlarge_platform_c : public good_bonus_c {
public:
  enlarge_platform_c();
  bool turnOnBonus(gameObjects_t obj);
  void doBonus(gameObjects_t obj) {};
  void turnOffBonus(gameObjects_t obj);
};

class cut_platform_c : public bad_bonus_c {
public:
  cut_platform_c();
  bool turnOnBonus(gameObjects_t obj);
  void doBonus(gameObjects_t obj) {};
  void turnOffBonus(gameObjects_t obj);
};

//cкорость шарика
class cut_ball_speed_c : public good_bonus_c {
public:
  cut_ball_speed_c();
  bool turnOnBonus(gameObjects_t obj);
  void doBonus(gameObjects_t obj) {};
  void turnOffBonus(gameObjects_t obj);
};

class increase_ball_speed_c : public bad_bonus_c {
public:
  increase_ball_speed_c();
  bool turnOnBonus(gameObjects_t obj);
  void doBonus(gameObjects_t obj) {};
  void turnOffBonus(gameObjects_t obj);
};

//направление
class naughty_ball_c : public bad_bonus_c {
public:
  naughty_ball_c();
  bool turnOnBonus(gameObjects_t obj);
  void doBonus(gameObjects_t obj);
  void turnOffBonus(gameObjects_t obj) {};
};

//прилипание
class ball_stick_c : public good_bonus_c {
public:
  ball_stick_c();
  bool turnOnBonus(gameObjects_t obj);
  void doBonus(gameObjects_t obj);
  void turnOffBonus(gameObjects_t obj) {};
};

//щит
class safe_board_c : public good_bonus_c {
public:
  safe_board_c();
  bool turnOnBonus(gameObjects_t obj);
  void doBonus(gameObjects_t obj) {};
  void turnOffBonus(gameObjects_t obj) {};
};
