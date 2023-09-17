#ifndef MELEEENEMY_H_
#define MELEEENEMY_H_

#include <utility>
#include "enemy.h"

class Tile;
class MovingEntity;

class MeleeEnemy final: public Enemy {
  // Helper fn for nextA
  Action bestAction(Tile *t, MovingEntity *m, Direction d);
protected:
  void doDraw() const override;
  std::pair<Action, Direction> nextA(int pX, int pY, char c, Tile *topT,
    MovingEntity *topE, Tile *bottomT, MovingEntity *bottomE, Tile *rightT,
    MovingEntity *rightE, Tile *leftT, MovingEntity *leftE) override;
public:
  // By default, melee enemy provides 1 point, does 1 damage, has 1 health
  MeleeEnemy(int p = 1, int d = 1, int h = 1);
  MeleeEnemy(const MeleeEnemy&);  // Copy ctor
};

#endif
