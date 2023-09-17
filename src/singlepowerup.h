#ifndef SINGLE_POWERUP_H_
#define SINGLE_POWERUP_H_

#include "tile.h"

class MovingEntity;

class SinglePowerUp: public Tile {
  bool isUsed = false;
protected:
  void use();  // Sets isUsed = true
  bool wasDestroyed() const override;
public:
  SinglePowerUp(int p);  // All single powerups have some number of points
  virtual ~SinglePowerUp() = default;
};



#endif
