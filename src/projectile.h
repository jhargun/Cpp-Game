#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "movingentity.h"

class Projectile final: public MovingEntity {
  bool isDestroyed = false;
protected:
  void doAttack(MovingEntity *) override;
  void runInto(MovingEntity *) override;
  bool wasDestroyed() const override;
  void doDraw() const override;
  std::pair<Action, Direction> nextA(int pX, int pY, char c, Tile *topT,
    MovingEntity *topE, Tile *bottomT, MovingEntity *bottomE, Tile *rightT,
    MovingEntity *rightE, Tile *leftT, MovingEntity *leftE) override;
public:
  /* Projectil ctor has 3 parameters: which direction it's facing, how many
  actions it has per turn, and how much damage it does. */
  Projectile(Direction f, unsigned int a = 1, int d = 1);
};

#endif
