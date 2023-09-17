#ifndef MOVINGENTITY_H_
#define MOVINGENTITY_H_

#include <utility>
#include "entity.h"

class Tile;

enum class Direction { Up, Down, Left, Right };
enum class Action { DoNothing, Face, Move, Hit, Shoot, Teleport, Clone };


class MovingEntity : public Entity {
  /* totalActions is the number of actions this MovingEntity can take per turn.
  remainingActions is the number of actions remaining in this turn. */
  const unsigned int totalActions = 1;
  unsigned int remainingActions = 1;
  int damage = 1;  // Damage inflicted if this Entity attacks
  Direction facing = Direction::Up;

protected:
  MovingEntity(const MovingEntity&);  // Copy ctor

  // nextA is called by nextAction to follow NVII idiom
  virtual std::pair<Action, Direction> nextA(int pX, int pY, char c, Tile *topT,
    MovingEntity *topE, Tile *bottomT, MovingEntity *bottomE, Tile *rightT,
    MovingEntity *rightE, Tile *leftT, MovingEntity *leftE) = 0;

  // Called by attack if entity is not nullptr and is not destroyed
  virtual void doAttack(MovingEntity *);

  virtual void onAttack(int);  // Called by attacked to follow NVII idiom
  virtual void refAc();  // Called by refreshActions to follow NVII idiom
  virtual void exAc();  // Called by exhaustActions to follow NVII idiom
  virtual void acOcc();  // Called by actionOccurred to follow NVII idiom
  virtual void runInto(MovingEntity *) = 0;  // Called by runIntoBy to follow NVII idiom
  virtual bool player() const;  // Called by isPlayer to follow NVII idiom

  Direction getFacing() const;  // Returns direction in which this entity is facing

public:
  // By default, moving entities have 0 point value and are facing up when constructed
  MovingEntity(Direction f = Direction::Up, int p = 0);
  MovingEntity(unsigned int a, Direction f = Direction::Up);
  MovingEntity(unsigned int tA, unsigned int rA, Direction f = Direction::Up);
  MovingEntity(int d, int p, Direction f = Direction::Up);
  MovingEntity(int d, unsigned int tA = 1, unsigned int rA = 1, Direction f = Direction::Up, int p = 0);

  bool hasRemainingActions() const;  // Returns true if remainingActions > 0
  void attacked(int);  // Called with damage of attack if attacked
  /* Attacks specified MovingEntity (does nothing if argument is nullptr
  or is already destroyed) */
  void attack(MovingEntity *);
  void refreshActions();  // Sets remainingActions back to totalActions
  void exhaustActions();  // Sets remainingActions to 0
  void actionOccurred();  // Called when the MovingEntity just performed an action

  /* This function enables actions. The MovingEntity is provided with 2 integers
  representing the difference between the entity's and player's x and y
  coordinates, a character representing the player's action, and 4 pairs of
  Tile and MovingEntity, corresponding to the tiles/entities above, below,
  to the right, and to the left of the entity. It returns a pair containing the
  desired next action and direction (but does not perform the action itself).
  Note that it decrements remainingActions and should therefore only be called
  when the action is being run. */
  std::pair<Action, Direction> nextAction(int pX, int pY, char c, Tile *topT,
    MovingEntity *topE, Tile *bottomT, MovingEntity *bottomE, Tile *rightT,
    MovingEntity *rightE, Tile *leftT, MovingEntity *leftE);

  // Called if m enters the same tile as this MovingEntity
  void runIntoBy(MovingEntity *);

  bool isPlayer() const;  // Returns true if this entity is a Player

  virtual ~MovingEntity() = default;
};

#endif
