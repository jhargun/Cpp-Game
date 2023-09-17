#ifndef CANENTER_H_
#define CANENTER_H_

// This function was needed in a few places in my code so I moved it here

class Tile;
class MovingEntity;

// Helper, returns true if it is possible to enter the tile t with entity e on it
bool canEnterPair(Tile *t, MovingEntity *e);

#endif
