#ifndef TILE_H_
#define TILE_H_

#include <memory>
#include "entity.h"
#include "movingentity.h"

class Tile: public Entity {
protected:
  // Used by doTurn() to follow NVII, assumes ptr isn't nullptr
  virtual void turn(std::unique_ptr<MovingEntity>&);
  virtual bool goal() const;  // Used by isGoal() to follow NVII
public:
  Tile(int p = 0);  // By default, tile has 0 points
  // doTurn makes tile perform actions on the entity standing on it
  void doTurn(std::unique_ptr<MovingEntity>&);
  bool isGoal() const;  // Returns true if this is a goal tile
  virtual ~Tile() = default;
};

#endif
