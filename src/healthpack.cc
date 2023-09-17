#include <iostream>
#include "healthpack.h"
#include "movingentity.h"

Healthpack::Healthpack(int h, int s): SinglePowerUp{s}, h{h} {}

void Healthpack::doDraw() const { std::cout << 'H'; }

void Healthpack::turn(std::unique_ptr<MovingEntity> &m) {
  if(m->isPlayer()) {
    m->attacked(h * -1);  // Do negative damage (heal)
    use();  // Healthpack is used up
  }
}
