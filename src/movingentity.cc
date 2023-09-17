#include <utility>
#include "movingentity.h"
#include "tile.h"

using namespace std;

MovingEntity::MovingEntity(const MovingEntity &o): Entity{o},
  totalActions{o.totalActions}, remainingActions{o.remainingActions},
  damage{o.damage}, facing{o.facing} {}


MovingEntity::MovingEntity(Direction f, int p): Entity{p}, facing{f} {}

MovingEntity::MovingEntity(unsigned int a, Direction f): totalActions{a},
  remainingActions{a}, facing{f} {}

MovingEntity::MovingEntity(unsigned int tA, unsigned int rA, Direction f):
  totalActions{tA}, remainingActions{rA}, facing{f} {}

MovingEntity::MovingEntity(int d, int p, Direction f): Entity{p}, damage{d}, facing{f} {}

MovingEntity::MovingEntity(int d, unsigned int tA, unsigned int rA, Direction f, int p):
  Entity{p}, totalActions{tA}, remainingActions{rA}, damage{d}, facing{f} {}


void MovingEntity::doAttack(MovingEntity *m) { m->attacked(damage); }

// By default, nothing happens when MovingEntity attacked
void MovingEntity::onAttack(int) { return; }

void MovingEntity::refAc() { return; }
void MovingEntity::exAc() { return; }

// actionOccurred handles decrementing remainingActions, so don't do anything here
void MovingEntity::acOcc() { return; }

// By default, MovingEntity is not a Player
bool MovingEntity::player() const { return false; }

Direction MovingEntity::getFacing() const { return facing; }

bool MovingEntity::hasRemainingActions() const { return (remainingActions != 0); }

void MovingEntity::attacked(int damage) { onAttack(damage); }

void MovingEntity::attack(MovingEntity *e) {
  if(e == nullptr || e->destroyed()) return;
  doAttack(e);
}

void MovingEntity::refreshActions() {
  remainingActions = totalActions;
  refAc();
}

void MovingEntity::exhaustActions() {
  remainingActions = 0;
  exAc();
}

void MovingEntity::actionOccurred() {
  --remainingActions;  // There is one less remaining action after this
  acOcc();  // This performs any extra required tasks
}

pair<Action, Direction> MovingEntity::nextAction(int pX, int pY, char c,
    Tile *topT, MovingEntity *topE, Tile *bottomT, MovingEntity *bottomE,
    Tile *rightT, MovingEntity *rightE, Tile *leftT, MovingEntity *leftE) {
  if(remainingActions == 0) { // If no remaining actions, do nothing
    return pair<Action, Direction>{Action::DoNothing, Direction::Up};
  }
  pair<Action, Direction> p = nextA(pX, pY, c, topT, topE, bottomT, bottomE, rightT, rightE, leftT, leftE);

  // Ensure entity is facing the correct way after this action
  if(p.first == Action::Move || p.first == Action::Face) facing = p.second;

  actionOccurred();
  return p;
}

void MovingEntity::runIntoBy(MovingEntity *m) { runInto(m); }

bool MovingEntity::isPlayer() const { return player(); }
