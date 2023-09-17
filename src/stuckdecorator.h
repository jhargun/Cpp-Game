#ifndef STUCKDECORATOR_H_
#define STUCKDECORATOR_H_

#include <utility>
#include <memory>
#include "livingentitydecorator.h"

class StuckDecorator final: public Decorator {
  /* Turns remaining where this still applies. Note that the number of turns
  remaining only decreases if the Entity tries to move. */
  int turns;
protected:
  Action doOnTurn(Action) override;
  bool immune(Status) const override;
public:
  // By default, stuck applies for 2 turns
  StuckDecorator(std::unique_ptr<LivingEntity> &l, int t = 2);
  StuckDecorator(std::unique_ptr<LivingEntity> &&l, int t = 2);
};

#endif

