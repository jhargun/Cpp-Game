#ifndef GOAL_H_
#define GOAL_H_

#include "tile.h"

class Goal final: public Tile {
protected:
  bool goal() const override;
  void doDraw() const override;
};

#endif
