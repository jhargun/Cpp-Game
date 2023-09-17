#include <iostream>
#include <utility>
#include "movingentity.h"
#include "canenter.h"
#include "meleeenemy.h"

using namespace std;

MeleeEnemy::MeleeEnemy(int p, int d, int h): Enemy{p, d, h} {}

MeleeEnemy::MeleeEnemy(const MeleeEnemy &o): Enemy{o} {}

void MeleeEnemy::doDraw() const { cout << "m"; }

/* Helper. Takes direction in which MeleeEnemy is planning to move as well as
the tile it's planning to move to and the entity standing on it. If the entity
is a Player, this returns Face (since MeleeEnemy must face Player before
attacking) or Hit (if already facing Player). If this movement is blocked,
this will return DoNothing. Otherwise, it will return Move. */
Action MeleeEnemy::bestAction(Tile *t, MovingEntity *m, Direction d) {
  if(m != nullptr && m->isPlayer()) {
    if(getFacing() == d) return Action::Hit;
    else return Action::Face;
  }
  else if(canEnterPair(t, m)) return Action::Move;
  else return Action::DoNothing;
}


pair<Action, Direction> MeleeEnemy::nextA(int pX, int pY, char c, Tile *topT,
    MovingEntity *topE, Tile *bottomT, MovingEntity *bottomE, Tile *rightT,
    MovingEntity *rightE, Tile *leftT, MovingEntity *leftE) {
  MovingEntity *desiredE;
  Tile *desiredT;
  Direction desiredD;
  Action desiredA;

  // First, check if on the same column as player. If not, try to get there
  if(pX != 0) {
    if(pX > 0) {  // If pX>0, want to move left
      desiredE = leftE;
      desiredT = leftT;
      desiredD = Direction::Left;
    }
    else {  // If pX<0, want to move right
      desiredE = rightE;
      desiredT = rightT;
      desiredD = Direction::Right;
    }
    // Get desired move. If it's DoNothing, move on to next possibility, else try it.
    desiredA = bestAction(desiredT, desiredE, desiredD);
    if(desiredA != Action::DoNothing) {
      return pair<Action, Direction>{desiredA, desiredD};
    }
  }

  // Next, check if on the same column as player. If not, try to get there
  if(pY != 0) {
    if(pY > 0) {  // If pY>0, want to move up
      desiredE = topE;
      desiredT = topT;
      desiredD = Direction::Up;
    }
    else {  // If pY<0, want to move down
      desiredE = bottomE;
      desiredT = bottomT;
      desiredD = Direction::Down;
    }
    // Get desired move. If it's DoNothing, move on to next possibility, else try it.
    desiredA = bestAction(desiredT, desiredE, desiredD);
    if(desiredA != Action::DoNothing) {
      return pair<Action, Direction>{desiredA, desiredD};
    }
  }

  // If we're stuck, just do nothing.
  return pair<Action, Direction>{Action::DoNothing, Direction::Up};
}
