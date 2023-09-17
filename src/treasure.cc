#include <iostream>
#include "treasure.h"
#include "movingentity.h"

Treasure::Treasure(int s): SinglePowerUp{s} {}

void Treasure::doDraw() const { std::cout << 'Z'; }

void Treasure::turn(std::unique_ptr<MovingEntity> &m) {
  if(m->isPlayer()) use();
}
