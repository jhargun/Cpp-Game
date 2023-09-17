#include <memory>
#include <utility>
#include "livingentitydecorator.h"

using namespace std;

Decorator::Decorator(unique_ptr<LivingEntity> &l):
  LivingEntity{*(l.get())}, l{l.release()} {}

Decorator::Decorator(unique_ptr<LivingEntity> &&l):
  LivingEntity{*(l.get())}, l{l.release()} {}

// By default, do nothing extra on the turn
Action Decorator::doOnTurn(Action a) { return a; }

void Decorator::doAttack(MovingEntity *m) { l->attack(m); }

void Decorator::onAttack(int d) {
  LivingEntity::onAttack(d);
  l->attacked(d);
}

void Decorator::refAc() {
  LivingEntity::refAc();
  l->refreshActions();
}

void Decorator::exAc() {
  LivingEntity::exAc();
  l->exhaustActions();
}

void Decorator::acOcc() {
  LivingEntity::acOcc();
  l->actionOccurred();
}

void Decorator::runInto(MovingEntity *m) {
  LivingEntity::runInto(m);
  l->runIntoBy(m);
}

bool Decorator::player() const { return l->isPlayer(); }

void Decorator::doDraw() const { l->draw(); }

bool Decorator::immune(Status s) const { return l->isImmune(s); }


pair<Action, Direction> Decorator::nextA(int pX, int pY, char c, Tile *topT,
    MovingEntity *topE, Tile *bottomT, MovingEntity *bottomE, Tile *rightT,
    MovingEntity *rightE, Tile *leftT, MovingEntity *leftE) {
  pair<Action, Direction> result = l->nextAction(pX, pY, c, topT, topE,
    bottomT, bottomE, rightT, rightE, leftT, leftE);

  result.first = doOnTurn(result.first);  // Perform any necessary alterations
  return result;
}

Decorator::~Decorator() {}
