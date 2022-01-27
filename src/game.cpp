#include "game.h"
using namespace std;
#define INFO_PART 1./10

game_c::game_c(const vector2_c &windowSize) : 
  info(vector2_c(windowSize.GetX(), INFO_PART*windowSize.GetY()), vector2_c(windowSize.GetX() / 2, windowSize.GetY()*(1 - INFO_PART / 2)), color_c(1, 1, 1)),
  score(0),
  gameSpace(vector2_c(windowSize.GetX(), windowSize.GetY()*(1 - INFO_PART))),
  field(gameSpace),
  saveBoard(vector2_c(windowSize.GetX(), 2), vector2_c(windowSize.GetX()/2, 1), color_c(1,1,1)),
  platform(windowSize)
{
  ball.SetStartPlace(platform);
  endGame = false;
};

void game_c::LaunchBall()
{
  if (ball.isBallOnPlatform(platform))
  {
    vector2_c normal = platform.GetNormal(ball.GetPivotPoint());
    ball.SetVelocity(vector2_c(0, -5)); //-0.5
    ball.Reflection(normal);
  }
};

void game_c::MovePlatform(int dx)
{ 
  if(platform.MovePlatform(dx))
    if (ball.isBallOnPlatform(platform) && !ball.IsMoving())
      ball.MoveBallWithPlatform(dx);
};

void game_c::IsBlocksHit() 
{
  int i = 0;
  for (auto block : field.GetBlocks())
  {
    if(ball.IsBlockHit(*block))
    {
      if (block->GetType() == DESTROYABLE)
      {
        score++;
        if (block->IsDestroyed())
        {
          if (block->isBonus() == true)
            field.ThrowBonus(*block);
          field.DeleteBlock(i);
        }
      }
    }
    i++;
  }
};

void game_c::DoBonuses() 
{
  int i = 0;
  gameObjects_t obj{&platform, &ball};

  for (auto bonus : field.GetGameBonuses())
  {
    if (bonus->getState() == NOT_DEFINED)
    {
      bonus->moveBonus();
      if (!bonus->isInGameArea())
        field.DeleteBonus(i);
      else if (bonus->isCatched(platform))
        if(!bonus->turnOnBonus(obj))
          field.DeleteBonus(i);
    }
    else
      if(!bonus->processBonus(obj))
        field.DeleteBonus(i);
    i++;
  }
}

void game_c::DeleteActiveBonuses()
{
  gameObjects_t obj{ &platform, &ball };

  for (auto bonus : field.GetGameBonuses())
  {
    if (bonus->getState() == ACTIVE)
      bonus->turnOffBonus(obj);
    field.DeleteBonus(0);
  }
}

void game_c::CheckFail()
{
  if (ball.GetPivotPoint().GetY() - ball.GetRadius() <= 0)
  {
    if (doSaveBoard)
    {
      ball.SetVelocity(ball.GetVelocity() -= 2 * ball.GetVelocity().projY());
      return;
    }
    platform.CutLifes();
    ball.SetStartPlace(platform);
    DeleteActiveBonuses();
  }
}

void game_c::Hit()
{
  ball.CheckWallsHit(gameSpace);
  ball.IsPlatformHit(platform);
  IsBlocksHit();
};

bool game_c::isDestroyableBlockLeft()
{
  for (auto block : field.GetBlocks())
  {
    if (block->GetType() == DESTROYABLE)
      return true;
  }
  return false;
}

void game_c::DrawGame()
{
  info.Draw();
  PrintScore();
  PrintLifeCnt();
  field.DrawField();
  ball.Draw();
  platform.Draw();

  if (doSaveBoard)
    saveBoard.Draw();

  if (platform.GetLifes() == 0)
    EndGame();
  if (!isDestroyableBlockLeft())
  {
    endGame = true;
    WinGame();
  }
}

void game_c::PrintScore() 
{
  text_c textScore(string("Score " + to_string(score)));
  double x = info.GetSize().GetX() / 4;
  double y = info.GetPivotPoint().GetY() - 5;

  glColor3d(0, 0, 0);
  glRasterPos3d(x, y, 0);
  textScore.Print();
};

void game_c::PrintLifeCnt() 
{
  text_c lifes(string("Lifes " + to_string(platform.GetLifes())));

  double x = info.GetSize().GetX()*3 / 4;
  double y = info.GetPivotPoint().GetY() - 5;

  glColor3d(0, 0, 0);
  glRasterPos3d(x, y, 0);
  lifes.Print();
};

void game_c::Run()
{
  if (platform.GetLifes() == 0)
    return;

  if (endGame)
    return;

  ball.MoveBall();
  Hit();
  DoBonuses();
  doSaveBoard = field.isBonusActive(ADD_SAFE_BOARD);
  CheckFail();
}

void game_c::WinGame() 
{
  text_c win(string("YOU WIN"));
  double x = gameSpace.GetX() / 2;
  double y = gameSpace.GetY() / 2;

  glColor3d(0, 0, 0);
  glRasterPos3d(x, y, 0);
  win.Print();
};

void game_c::EndGame() 
{
  text_c gameover(string("GAME OVER"));
  double x = gameSpace.GetX() / 2;
  double y = gameSpace.GetY() / 2;

  glColor3d(0, 0, 0);
  glRasterPos3d(x, y, 0);
  gameover.Print();
};