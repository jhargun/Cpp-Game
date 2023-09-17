#ifndef ENEMY_H_
#define ENEMY_H_

#include "livingentity.h"

class Enemy: public LivingEntity {
public:
  /* By default, enemies provide 1 point when killed, do 1 damage, have 1
  health, and face up. */
  Enemy(int p = 1, int d = 1, int h = 1, Direction f = Direction::Up);
  Enemy(const Enemy&);  // Copy ctor
  virtual ~Enemy() = default;
};

#endif
