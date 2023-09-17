#ifndef HEALTHPACK_H_
#define HEALTHPACK_H_

#include "singlepowerup.h"

class MovingEntity;

class Healthpack final: public SinglePowerUp {
  int h;  // Amount of health healed
protected:
  void doDraw() const override;
  void turn(std::unique_ptr<MovingEntity>&) override;
public:
  // By default, healthpack heals 1 health and provides 1 score
  Healthpack(int h = 1, int s = 1);
};

#endif
