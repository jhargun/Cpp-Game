#include "livingentity.h"

LivingEntity::LivingEntity(const LivingEntity &o): MovingEntity{o},
  health{o.health} {}

/* If direction or points provided, construct MovingEntity with that direction.
Otherwise, just default construct MovingEntity. */
LivingEntity::LivingEntity(int h): health{h} {}
LivingEntity::LivingEntity(int h, Direction f): MovingEntity{f}, health{h} {}
LivingEntity::LivingEntity(int h, int p): MovingEntity{p}, health{h} {}
LivingEntity::LivingEntity(int h, int p, int d): MovingEntity{d, p}, health{h} {}
LivingEntity::LivingEntity(int h, int p, int d, Direction f):
  MovingEntity{d, p, f}, health{h} {}

// By default, LivingEntity not immune to any status
bool LivingEntity::immune(Status) const { return false; }

// When attacked, LivingEntities lose health
void LivingEntity::onAttack(int damage) { health -= damage; }

// Should never runInto a LivingEntity, so this throws an exception.
void LivingEntity::runInto(MovingEntity *) {
  throw "Error: Can't run into a LivingEntity.";
}

// LivingEntities are destroyed if their health is 0 or less
bool LivingEntity::wasDestroyed() const { return (health <= 0); }

// LivingEntities are not enterable
bool LivingEntity::enterable() const { return false; }

bool LivingEntity::isImmune(Status s) const { return false; } //return immune(s); }
