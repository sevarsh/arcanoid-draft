#pragma once
#include "color.h"
#include "figure.h"

enum block_type_t {
  UNBROKEN,
  DESTROYABLE
};

class block_c: public rectangle_c {
public:
  block_c(const vector2_c &blockSize, const vector2_c &peak);
  virtual ~block_c() {};

  void DrawBlock();

  vector2_c GetCoordinates() const;
  block_type_t GetType() const;
  virtual bool IsDestroyed() { return false; };
  virtual bool isBonus() const = 0;

protected:
  block_type_t type;
}; 

class unbroken_block_c: public block_c {
public:
  unbroken_block_c(const vector2_c &blockSize, const vector2_c &peak);
  ~unbroken_block_c() {}

  bool IsDestroyed() { return false; };
  bool isBonus() const { return false; };
};

class destroyable_block_c : public block_c {
public:
  destroyable_block_c(const vector2_c &blockSize, const vector2_c &peak, bool isBonusBlock);
  ~destroyable_block_c() {}

  bool IsDestroyed();
  bool isBonus() const;

protected:
  int healthLevel;
  bool isBonusBlock;

  void CutHealthLevel();
  void DefineBlockColor();
};