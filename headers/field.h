#pragma once
#include "block.h"
#include "bonus.h"
#include <vector>

using namespace std;
using block_t = vector<block_c*>; 
using bonus_t = vector<bonus_c*>;

class field_c {
public:
  field_c(const vector2_c &vec);
  field_c() {};
  ~field_c();
  
  block_t GetBlocks() const;
  bonus_t GetFieldBonuses() const;
  bonus_t GetGameBonuses() const;

  bool isBonusActive(const bonus_type_t &type);
  void ThrowBonus(block_c &block);
  
  bonus_c* SetBonus();
  block_c* SetBlock(const vector2_c &blockSize, const vector2_c &peak, const block_type_t &type);

  void DeleteBonus(int pos);
  void DeleteBlock(int pos);

  void DrawField();
  
private:
  block_t blocks;
  bonus_t fieldBonuses;
  bonus_t gameBonuses;
};
