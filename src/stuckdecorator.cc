#include <iostream>
#include "stuckdecorator.h"
#include "movingentity.h"

StuckDecorator::StuckDecorator(std::unique_ptr<LivingEntity> &l, int t):
  Decorator{l}, turns{t} {}

StuckDecorator::StuckDecorator(std::unique_ptr<LivingEntity> &&l, int t):
  Decorator{l}, turns{t} {}

Action StuckDecorator::doOnTurn(Action a) {
  // If entity still stuck, Move gets turned into Face
  if(turns > 0 && a == Action::Move) {
    std::cout << "Stuck for " << turns-- << " more moves!" << std::endl;
    return Action::Face;
  }
  return a;
}

bool StuckDecorator::immune(Status s) const {
  // If currently stuck, immune to getting stuck again.
  if(turns >= 0 && s == Status::Stuck) return false;
  return Decorator::immune(s);
}
