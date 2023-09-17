#ifndef LIVINGENTITY_H_
#define LIVINGENTITY_H_

#include <utility>
#include "movingentity.h"

// These are statuses that can be nullified by powerups
enum class Status { Poison, Stuck };

class LivingEntity: public MovingEntity {
  int health;
protected:
  LivingEntity(const LivingEntity&);  // Copy ctor
  void onAttack(int) override;
  void runInto(MovingEntity *) override;
  bool wasDestroyed() const override;
  bool enterable() const;
  virtual bool immune(Status) const;  // Called by isImmune
public:
  // LivingEntity always has 1 action, so no ctor takes actions as a parameter
  LivingEntity(int h);
  LivingEntity(int h, Direction f);
  LivingEntity(int h, int p);
  LivingEntity(int h, int p, int d);
  LivingEntity(int h, int p, int d, Direction f);

  bool isImmune(Status) const;  // Returns true if this LivingEntity is immune to the status

  virtual ~LivingEntity() = default;
};

#endif
