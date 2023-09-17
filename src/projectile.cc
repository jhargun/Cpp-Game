#include <iostream>
#include "canenter.h"
#include "movingentity.h"
#include "projectile.h"

using namespace std;

/* When projectile constructed, it uses an action. This ensures it's fired the
correct distance when first intialized. */
Projectile::Projectile(Direction f, unsigned int a, int d): MovingEntity{d, a, a-1, f} {}

/* If a Projectile attacks a MovingEntity, the projectile is destroyed
Note that this means projectiles can collide and destroy each other. */
void Projectile::doAttack(MovingEntity *m) {
  MovingEntity::doAttack(m);
  isDestroyed = true;
}

// If a MovingEntity enters a tile containing a Projectile, the Projectile hits them
void Projectile::runInto(MovingEntity *m) { doAttack(m); }

bool Projectile::wasDestroyed() const { return isDestroyed; }

void Projectile::doDraw() const { cout << "A"; }

pair<Action, Direction> Projectile::nextA(int pX, int pY, char c, Tile *topT,
    MovingEntity *topE, Tile *bottomT, MovingEntity *bottomE, Tile *rightT,
    MovingEntity *rightE, Tile *leftT, MovingEntity *leftE) {
  Direction f = getFacing();
  Tile *nextT;
  MovingEntity *nextE;
  switch(f) {
    case Direction::Up:    nextT = topT;     nextE = topE;     break;
    case Direction::Down:  nextT = bottomT;  nextE = bottomE;  break;
    case Direction::Left:  nextT = leftT;    nextE = leftE;    break;
    case Direction::Right: nextT = rightT;   nextE = rightE;   break;
  }
  // If there is a MovingEntity in front of the projectile, attack it
  if(nextE != nullptr) attack(nextE);
  // If the projectile can't enter the next tile, it's destroyed
  else if(!(canEnterPair(nextT, nextE))) isDestroyed = true;
  // Projectile always tries to move forward
  return pair<Action, Direction>{Action::Move, f};
}
