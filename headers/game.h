#pragma once  
#include "field.h"
#include "platform.h"
#include "ball.h"
#include "bonus.h"
#include "text.h"
#include <list>

using namespace std;

class game_c {
public:
  game_c(const vector2_c &windowSize);
  
  void DrawGame();
  void LaunchBall();
  void MovePlatform(int dx);
  void Run();

private:
  rectangle_c info;
  vector2_c gameSpace;
  field_c field;
  ball_c ball;
  platform_c platform;
  rectangle_c saveBoard;

  int score;

  bool doSaveBoard;
  bool endGame;

  void IsBlocksHit();
  void Hit();
  bool isDestroyableBlockLeft();
  void CheckFail();

  void WinGame();
  void EndGame();

  void PrintScore();
  void PrintLifeCnt();

  void DoBonuses();
  void DeleteActiveBonuses();
};
