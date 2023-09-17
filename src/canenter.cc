#include "canenter.h"

#include "tile.h"
#include "movingentity.h"

bool canEnterPair(Tile *t, MovingEntity *e) {
  if(e != nullptr && !(e->canEnter())) return false;
  else return t->canEnter();
}
