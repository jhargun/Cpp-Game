#ifndef TREASURE_H_
#define TREASURE_H_

#include "singlepowerup.h"

class Treasure final: public SinglePowerUp {
  void doDraw() const override;
  void turn(std::unique_ptr<MovingEntity>&) override;
public:
  // By default, treasure gives 5 score
  Treasure(int s = 5);
};

#endif
