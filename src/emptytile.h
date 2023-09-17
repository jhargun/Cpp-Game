#ifndef EMPTYTILE_H_
#define EMPTYTILE_H_

#include "tile.h"

class EmptyTile final: public Tile {
protected:
  void doDraw() const override;
};

#endif
