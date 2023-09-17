#include <iostream>
#include <utility>
#include "movingentity.h"
#include "canenter.h"
#include "rangedenemy.h"

using namespace std;

RangedEnemy::RangedEnemy(int c, int curC, int p, int h): Enemy{p, 0, h},
  cooldown{c}, curCooldown{curC} {}

void RangedEnemy::doDraw() const { cout << "r"; }

pair<Action, Direction> RangedEnemy::nextA(int pX, int pY, char c, Tile *topT,
    MovingEntity *topE, Tile *bottomT, MovingEntity *bottomE, Tile *rightT,
    MovingEntity *rightE, Tile *leftT, MovingEntity *leftE) {
  // If there is a cooldown on firing, reduce it by 1
  if(curCooldown > 0) --curCooldown;

  MovingEntity *desiredE;
  Tile *desiredT;
  Direction desiredD;
  Action desiredA;

  // First, check if on the same column or row as player
  if(pX == 0 || pY == 0) {
    // If on same row/col, choose direction and either face that way or shoot
    if(pX == 0) desiredD = (pY > 0 ? Direction::Up : Direction::Down);
    else desiredD = (pX > 0 ? Direction::Left : Direction::Right);
    // Shoot if facing in correct direction and no cooldown, otherwise turn
    desiredA = (getFacing() == desiredD && curCooldown == 0 ? Action::Shoot : Action::Face);
    // If shooting, set the curCooldown
    if(desiredA == Action::Shoot) curCooldown = cooldown;
    return pair<Action, Direction>{desiredA, desiredD};
  }

  // Try to get to same row first
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
  // If you can move to the desired position, do it
  if(canEnterPair(desiredT, desiredE)) {
    return pair<Action, Direction>{Action::Move, desiredD};
  }

  // If can't get to same row, try to get to the same column next
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
  // If you can move to the desired position, do it
  if(canEnterPair(desiredT, desiredE)) {
    return pair<Action, Direction>{Action::Move, desiredD};
  }

  // If we're stuck, just do nothing.
  return pair<Action, Direction>{Action::DoNothing, Direction::Up};
}
