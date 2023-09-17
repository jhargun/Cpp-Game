#ifndef BLOCKER_H_
#define BLOCKER_H_

#include "tile.h"

class Blocker: public Tile {
protected:
  bool enterable() const override;
public:
  virtual ~Blocker() = 0;  // Pure virtual to make class abstract
};

class OuterBoundary final: public Blocker {
protected:
  void doDraw() const override;
};

class Tree final: public Blocker {
protected:
  void doDraw() const override;
};

class Rock final: public Blocker {
protected:
  void doDraw() const override;
};

#endif
