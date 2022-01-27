#include "field.h"
#include <cstdlib>

#define BLOCK_CNT_MIN 40
#define BLOCK_CNT_MAX 50
#define MAX_HEALTH 4

bool isBonus()
{
  bool i = (bool)(rand() % 2);
  return i;
}

int DefineShift(int maxShift)
{
  return (maxShift/2 + rand() % maxShift);
}

int DefineStartShift(int maxShift)
{
  return (0 + rand() % maxShift);
}

bonus_type_t defineBonusType()
{
  return bonus_type_t(0 + rand() % CUT_BALL_SPEED);
}

bonus_c* field_c::SetBonus()
{
  bonus_type_t type = defineBonusType();
  bonus_c* newBonus;
  switch (type)
  {
  case ENLARGE_PLATFORM:
    newBonus = new enlarge_platform_c();
    break;
  case CUT_PLATFORM:
    newBonus = new cut_platform_c();
    break;
  case CUT_BALL_SPEED:
    newBonus = new cut_ball_speed_c();
    break;
  case INCREASE_BALL_SPEED:
    newBonus = new increase_ball_speed_c();
    break;
  case NAUGHTY_BALL:
    newBonus = new naughty_ball_c();
    break;
  case CHANGE_BALL_STICK:
    newBonus = new ball_stick_c();
    break;
  case ADD_SAFE_BOARD:
    newBonus = new safe_board_c();
    break;
  default:
    break;
  }
  return newBonus;
}

block_c* field_c::SetBlock(const vector2_c &blockSize, const vector2_c &peak, const block_type_t &type)
{
  block_c* block;
  switch (type)
  {
    case(UNBROKEN):
      block = new unbroken_block_c(blockSize, peak);
      break;
    case(DESTROYABLE):
    {
      bool bonusExist = isBonus();
      if (bonusExist)
        fieldBonuses.push_back(SetBonus());
      block = new destroyable_block_c(blockSize, peak, bonusExist);
      break;
    }
  }
  return block;
}

field_c::field_c(const vector2_c &winSize)
{
  vector2_c blockSize(winSize.GetX() / 8, winSize.GetY() / 25);
  vector2_c pivotPoint(blockSize.GetX()/2, winSize.GetY() - blockSize.GetY()/2);
  block_type_t type;
  int blockCnt = BLOCK_CNT_MIN + rand() % BLOCK_CNT_MAX;

  for (int i = 0; i < blockCnt; i++)
  {
    if (i % 6 == 0)
    {
      pivotPoint += vector2_c(blockSize.GetX() + DefineShift(blockSize.GetX()), 0);
      type = UNBROKEN;
    }
    else
    {
      pivotPoint += vector2_c(blockSize.GetX(), 0);
      type = DESTROYABLE;
    }

    if (pivotPoint.GetX() + blockSize.GetX() >= winSize.GetX())
    {
      pivotPoint.SetX(blockSize.GetX() / 2 + DefineStartShift(blockSize.GetX()/2));
      pivotPoint -= vector2_c (0, blockSize.GetY());
    }

    block_c* newBlock = SetBlock(blockSize, pivotPoint, type);
    blocks.push_back(newBlock);
  } 
}

void field_c::DeleteBlock(int pos) 
{ 
  delete blocks[pos]; 
  blocks.erase(blocks.begin() + pos); 
}

void field_c::DeleteBonus(int pos)
{
  delete gameBonuses[pos];
  gameBonuses.erase(gameBonuses.begin() + pos);
}

void field_c::ThrowBonus(block_c &block)
{
  bonus_c* bonus = fieldBonuses.back();
  fieldBonuses.pop_back();
  bonus->SetPivotPoint(block.GetPivotPoint());
  bonus->setBonusState(NOT_DEFINED);
  gameBonuses.push_back(bonus);
}

bool field_c::isBonusActive(const bonus_type_t &type)
{
  for (auto bonus : gameBonuses)
    if (bonus->getType() == type && bonus->getState() == ACTIVE)
      return true;
  return false;
}

block_t field_c::GetBlocks() const
{ 
  return blocks; 
}

bonus_t field_c::GetFieldBonuses() const
{
  return fieldBonuses;
}

bonus_t field_c::GetGameBonuses() const
{
  return gameBonuses;
}

void field_c::DrawField()
{
  for (auto block : blocks)
    block->DrawBlock();

  for (auto bonus : gameBonuses)
  if(bonus->getState() == NOT_DEFINED)
    bonus->Draw();
}

field_c::~field_c() 
{ 
  for (auto block : blocks) 
    delete block; 

  for (auto bonus : gameBonuses)
    delete bonus;

  for (auto bonus : fieldBonuses)
    delete bonus;
}