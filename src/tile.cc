#include <memory>
#include "movingentity.h"
#include "tile.h"

using namespace std;

Tile::Tile(int p): Entity{p} {}

// By default, tiles don't do anything to entities standing on them
void Tile::turn(unique_ptr<MovingEntity> &p) { return; }

// By default, tiles aren't goal tiles
bool Tile::goal() const { return false; }

void Tile::doTurn(unique_ptr<MovingEntity> &p) {
  // If there is no entity on this tile, do nothing
  if(p.get() == nullptr) return;
  this->turn(p);
}

bool Tile::isGoal() const { return goal(); }
