#include "block.h"
#include <iostream>
#define MIN_HEALTH 1
#define MAX_HEALTH 4

int DefineHealth()
{
  int i = (MIN_HEALTH + rand() % MAX_HEALTH);
  return i;
}

block_c::block_c(const vector2_c &blockSize, const vector2_c &peak) : 
  rectangle_c(blockSize, peak, color_c())
{}

unbroken_block_c::unbroken_block_c(const vector2_c &blockSize, const vector2_c &peak)
  : block_c(blockSize, peak)
{
  SetColor(color_c(0, 0, 0));
  type = UNBROKEN;
};

destroyable_block_c::destroyable_block_c(const vector2_c &blockSize, const vector2_c &peak, bool isBonusBlock)
  : block_c(blockSize, peak), isBonusBlock(isBonusBlock)
{
  healthLevel = DefineHealth();
  DefineBlockColor();
  type = DESTROYABLE;
};

block_type_t block_c::GetType() const
{
  return type;
}

bool destroyable_block_c::isBonus() const
{
  return isBonusBlock;
}

void destroyable_block_c::CutHealthLevel()
{
  healthLevel--;
}

void destroyable_block_c::DefineBlockColor()
{
  switch (healthLevel)
  {
  case (1):
    color = color_c(0.64, 0.80, 0.35);
    break;
  case (2):
    color = color_c(0.41, 0.55, 0.13);
    break;
  case (3):
    color = color_c(0, 0.55, 0.27);
    break;
  case (4):
    color = color_c(0, 0.55, 0);
    break;
  default:
    color = color_c(0, 0.55, 0);
  }
}

bool destroyable_block_c::IsDestroyed()
{
  CutHealthLevel();
  if (healthLevel != 0)
  {
    DefineBlockColor();
    return false;
  }
  else
    return true;
}

vector2_c block_c::GetCoordinates() const
{
  return GetPivotPoint();
}

void block_c::DrawBlock()
{
  Draw();
}