#ifndef LIVINGENTITYDECORATOR_H_
#define LIVINGENTITYDECORATOR_H_

#include <utility>
#include <memory>
#include "livingentity.h"

class Decorator: public LivingEntity {
  std::unique_ptr<LivingEntity> l;
protected:
  // Performs decorator specific actions by altering output of nextA
  virtual Action doOnTurn(Action);

  // Called by attack if entity is not nullptr and is not destroyed
  void doAttack(MovingEntity *) override;
  void onAttack(int) override;  // Called by attacked to follow NVII idiom
  void refAc() override;  // Called by refreshActions to follow NVII idiom
  void exAc() override;  // Called by exhaustActions to follow NVII idiom
  void acOcc() override;  // Called by actionOccurred to follow NVII idiom
  void runInto(MovingEntity *) override;  // Called by runIntoBy to follow NVII idiom
  bool player() const override;  // Called by isPlayer to follow NVII idiom
  void doDraw() const override;
  bool immune(Status) const override;
  std::pair<Action, Direction> nextA(int pX, int pY, char c, Tile *topT,
    MovingEntity *topE, Tile *bottomT, MovingEntity *bottomE, Tile *rightT,
    MovingEntity *rightE, Tile *leftT, MovingEntity *leftE) override;
public:
  // Decorator steals the pointer stored by l
  Decorator(std::unique_ptr<LivingEntity> &l);
  Decorator(std::unique_ptr<LivingEntity> &&l);
  virtual ~Decorator() = 0;  // Made pure virtual to ensure this is abstract
};

#endif
