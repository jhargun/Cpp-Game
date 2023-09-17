#include "entity.h"

Entity::Entity(const Entity &o): points{o.points} {}

// By default, entities are enterable
bool Entity::enterable() const { return true; }

// By default, entities cannot be destroyed
bool Entity::wasDestroyed() const { return false; }

Entity::Entity(int p): points{p} {}

// These are public functions created to follow the NVII idiom.
void Entity::draw() const { doDraw(); }
bool Entity::canEnter() const { return enterable(); }
bool Entity::destroyed() const { return wasDestroyed(); }

int Entity::getPoints() const { return points; }
