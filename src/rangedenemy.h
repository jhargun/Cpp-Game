#ifndef RANGEDENEMY_H_
#define RANGEDENEMY_H_

#include <utility>
#include "enemy.h"

class Tile;
class MovingEntity;

class RangedEnemy final: public Enemy {
  // RangedEnemy has a cooldown when firing to prevent annoying spamming of attacks
  const int cooldown;
  int curCooldown;
protected:
  void doDraw() const override;
  std::pair<Action, Direction> nextA(int pX, int pY, char c, Tile *topT,
    MovingEntity *topE, Tile *bottomT, MovingEntity *bottomE, Tile *rightT,
    MovingEntity *rightE, Tile *leftT, MovingEntity *leftE) override;
public:
  /* By default, ranged enemy has a cooldown of 2 turns, provides 2 points, and
  has 1 health. Note that RangedEnemy cannot melee attack and therefore */
  RangedEnemy(int c = 2, int curC = 0, int p = 2, int h = 1);
};

#endif
