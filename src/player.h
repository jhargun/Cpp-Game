#ifndef PLAYER_H_
#define PLAYER_H_

#include "livingentity.h"

class Player final: public LivingEntity {
protected:
  bool player() const override;
  void doDraw() const override;
  std::pair<Action, Direction> nextA(int pX, int pY, char c, Tile *topT,
    MovingEntity *topE, Tile *bottomT, MovingEntity *bottomE, Tile *rightT,
    MovingEntity *rightE, Tile *leftT, MovingEntity *leftE) override;
public:
  Player(int);
  Player(int, Direction);
};

#endif
