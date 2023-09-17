#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>
#include <utility>
#include "board.h"
#include "tile.h"
#include "emptytile.h"
#include "healthpack.h"
#include "treasure.h"
#include "blocker.h"
#include "goal.h"
#include "movingentity.h"
#include "projectile.h"
#include "meleeenemy.h"
#include "rangedenemy.h"
#include "magicenemy.h"
#include "player.h"
#include "canenter.h"
#include "getrand.h"
#include "stuckdecorator.h"

using namespace std;

/*
Boards are created to have 2 extra rows and columns on the outside containing
OuterBoundary tiles preventing entities from leaving or Passageways
*/
Board::Board(unsigned int rows, unsigned int cols, bool v, int s): verbose{v},
  r{rows}, c{cols}, pX{1}, pY{1}, score{s} {
  if(rows == 0 || cols == 0) {
    throw invalid_argument{"Cannot make a Board with 0 rows or columns"};
  }

  tiles.reserve(rows);
  entities.reserve(rows);

  for(unsigned int i = 0; i <= r+1; ++i) {
    tiles.emplace_back(vector<unique_ptr<Tile>>{});
    tiles[i].reserve(cols);
    entities.emplace_back(vector<unique_ptr<MovingEntity>>{});
    entities[i].reserve(cols);
    for(unsigned int j = 0; j <= c+1; ++j) {
      if(i == 0 || j == 0 || i == r+1 || j == c+1) {
          tiles[i].emplace_back(make_unique<OuterBoundary>());
      }
      else {
        tiles[i].emplace_back(make_unique<EmptyTile>());
      }
      entities[i].emplace_back(nullptr);
    }
  }
  entities[pY][pX] = make_unique<StuckDecorator>(make_unique<Player>(1));
  tiles[2][2] = make_unique<Tree>();
  tiles[2][1] = make_unique<Healthpack>();
  tiles[3][1] = make_unique<Treasure>();
  tiles[3][3] = make_unique<Rock>();
  tiles[3][4] = make_unique<Goal>();
  // entities[3][6] = make_unique<MeleeEnemy>(5);
  entities[3][6] = make_unique<MagicEnemy<MeleeEnemy>>(make_unique<MeleeEnemy>(5, 1, 3));
  // entities[3][6] = make_unique<MagicEnemy<RangedEnemy>>(make_unique<RangedEnemy>(2, 0, 5, 2));
  entities[2][7] = make_unique<RangedEnemy>();
}

void Board::draw() const {
  for(unsigned int i = 0; i < r + 2; ++i) {
    for(unsigned int j = 0; j < c + 2; ++j) {
      if(entities[i][j].get() != nullptr) entities[i][j]->draw();
      else tiles[i][j]->draw();
    }
    cout << endl;
  }
  // cout << "Player (x,y): (" << pX << ", " << pY << ")" << endl << endl;
  cout << endl;
}

template <typename T>
void Board::updateScore(unique_ptr<T> &p) {
  if(p.get() != nullptr) score += p->getPoints();
}

/* Helpers, destroy entity contained by p and adds resulting score to score.
The version with newP resets p with the pointer newP. */
template <typename T>
void Board::destroyEntity(unique_ptr<T> &p, unique_ptr<T> &newP) {
  updateScore<T>(p);
  p.reset(newP.release());
}

template <typename T>
void Board::destroyEntity(unique_ptr<T> &p, T *newP) {
  updateScore<T>(p);
  p.reset(newP);
}

template <typename T>
void Board::destroyEntity(unique_ptr<T> &p) {
  updateScore<T>(p);
  p.reset();
}

// Player not alive if their position is set outside of board or if they are destroyed
bool Board::playerAlive() const {
  if(pX < 0 || pY < 0) return false;
  MovingEntity *p = entities[pY][pX].get();
  return !(p == nullptr || !(p->isPlayer()) || p->destroyed());
}

bool Board::victory() const {
  return (playerAlive() && tiles[pY][pX]->isGoal());
}

// Returns -1 if player is dead, score contained by player otherwise
int Board::getScore() const {
  return score;
  // return (playerAlive() ? entities[pY][pX]->getScore() : -1);
}

// Deletes contents of m if m->destroyed
// void deleteIfDestroyed(unique_ptr<MovingEntity> &m) {
//   if(m.get() != nullptr && m->destroyed()) m.reset();
// }

template <typename T>
unique_ptr<T>& Board::getInDirection(int x, int y, Direction d, vector<vector<unique_ptr<T>>> &v) const {
  switch(d) {
    case Direction::Up:    return v[y-1][x];
    case Direction::Down:  return v[y+1][x];
    case Direction::Left:  return v[y][x-1];
    case Direction::Right: return v[y][x+1];
  }
}

// Helper, takes direction of movement, updates x and y position appropriately
void updatePosition(int &x, int &y, Direction d) {
  switch(d) {
    case Direction::Up:    --y;  break;
    case Direction::Down:  ++y;  break;
    case Direction::Left:  --x;  break;
    case Direction::Right: ++x;  break;
  }
}

pair<int, int> Board::getRandEmpty() const {
  // Tests different random positions until an available one is found
  int newX, newY;
  Tile *inWayT;
  MovingEntity *inWayE;
  while(true) {
    newX = getRand(c) + 1;
    newY = getRand(r) + 1;
    inWayT = tiles[newY][newX].get();
    inWayE = entities[newY][newX].get();
    // Won't return if not enterable or if there's a MovingEntity there already
    if(inWayE == nullptr && canEnterPair(inWayT, inWayE)) break;
  }
  return pair<int, int>{newX, newY};
}

// Helper, handles the turn of the entity currently at (y,x)
pair<int, int> Board::handleEntityTurn(int x, int y, char pA) {
  if(x < 1 || y < 1 || x > pA || y > r) {
    throw invalid_argument{"Cannot handle turn of entity at that position"};
  }
  // If there is no entity at specified position, do nothing
  MovingEntity *e = entities[y][x].get();
  // cout << "Running on: " << x << ", " << y << "\tIs nullptr: " << (e == nullptr) << endl;
  if(e == nullptr || e->destroyed()) return pair<int, int>{-1, -1};
  else if(!(e->hasRemainingActions())) return pair<int, int>{x, y};

  // Draw the board if this entity is going to perform an action and verbose is true
  if(verbose) draw();

  /* Get pointers to the tiles/entities around e. Note: be careful
  not to use these if their corresponding unique_ptr was destroyed. */
  Tile *topT = tiles[y-1][x].get();
  MovingEntity *topE = entities[y-1][x].get();
  Tile *bottomT = tiles[y+1][x].get();
  MovingEntity *bottomE = entities[y+1][x].get();
  Tile *rightT = tiles[y][x+1].get();
  MovingEntity *rightE = entities[y][x+1].get();
  Tile *leftT = tiles[y][x-1].get();
  MovingEntity *leftE = entities[y][x-1].get();

  // Have e decide on its next action
  pair<Action, Direction> a = e->nextAction(x - pX, y - pY, pA, topT, topE, bottomT,
    bottomE, rightT, rightE, leftT, leftE);

  int newX = x;
  int newY = y;

  // These are ptrs to the entity and tile in the way of the action
  MovingEntity *inWayE;
  Tile *inWayT;
  switch(a.second) {
    case Direction::Up:    inWayE = topE;     inWayT = topT;     break;
    case Direction::Down:  inWayE = bottomE;  inWayT = bottomT;  break;
    case Direction::Left:  inWayE = leftE;    inWayT = leftT;    break;
    case Direction::Right: inWayE = rightE;   inWayT = rightT;   break;
  }

  switch(a.first) {
    case Action::Move:
    {
      // If the action was moving, check to make sure it's allowed. If it is,
      // move into the new tile and handle any collisions.
      if(canEnterPair(inWayT, inWayE)) {
        // cout << "Can enter" << endl;
        if(inWayE != nullptr) inWayE->runIntoBy(e);
        updatePosition(newX, newY, a.second);
      }
      // Delete whatever was originally in the new position and move e there
      destroyEntity<MovingEntity>(entities[newY][newX], entities[y][x]);
      break;
    }

    case Action::Hit:
    {
      if(inWayE != nullptr) {
        e->attack(inWayE);
        // Clean up board by deleting attacked MovingEntity if destroyed
        if(inWayE->destroyed()) destroyEntity<MovingEntity>(
          getInDirection<MovingEntity>(x, y, a.second, entities));
      }
      break;

    case Action::Shoot:
      unique_ptr<MovingEntity> proj = make_unique<Projectile>(a.second, 2);
      // If there's a MovingEntity where Projectile is being created, it gets hit
      if(inWayE != nullptr) {
        proj->attack(inWayE);
        if(inWayE->destroyed()) {
          destroyEntity<MovingEntity>(getInDirection<MovingEntity>(x, y, a.second, entities));
          inWayE = nullptr;  // inWayE points to deleted MovingEntity
        }
      }
      if(canEnterPair(inWayT, inWayE) && !(proj->destroyed())) {
        // Put Projectile into appropriate position in vector
        destroyEntity<MovingEntity>(getInDirection<MovingEntity>(x, y, a.second, entities), proj);
        updatePosition(x, y, a.second);
        handleEntityTurn(x, y, pA);
      }
      break;
    }

    case Action::Teleport:
    {
      pair<int, int> newPos = getRandEmpty();
      newX = newPos.first;
      newY = newPos.second;
      // Delete whatever was originally in the new position and move e there
      destroyEntity<MovingEntity>(entities[newY][newX], entities[y][x]);
      entities[newY][newX]->exhaustActions();  // Can't do anything after teleport in a turn
      break;
    }

    case Action::Clone:
    {
      // cout << "Cloning" << endl;
      // Get a new position for the clone
      pair<int, int> newPos = getRandEmpty();

      // First, test if this is a melee magic enemy
      MagicEnemy<MeleeEnemy> *temp1 = dynamic_cast<MagicEnemy<MeleeEnemy> *>(e);
      if(temp1 != nullptr) {
        entities[newPos.second][newPos.first] = make_unique<MagicEnemy<MeleeEnemy>>(*temp1);
        break;
      }

      // If that didn't work, check if this is a ranged magic enemy
      MagicEnemy<RangedEnemy> *temp2 = dynamic_cast<MagicEnemy<RangedEnemy> *>(e);
      if(temp2 != nullptr) {
        entities[newPos.second][newPos.first] = make_unique<MagicEnemy<RangedEnemy>>(*temp2);
        break;
      }

      e->exhaustActions();
      break;
    }
  }

  // If entity was destroyed, reset it
  if(e->destroyed()) {
    destroyEntity<MovingEntity>(entities[newY][newX]);
    // entities[newY][newX].reset();
    return pair<int, int>{-1, -1};
  }
  // If e is not finished with its actions, continue
  else if(e->hasRemainingActions()) return handleEntityTurn(newX, newY, pA);
  else return pair<int, int>{newX, newY};
}


void Board::updateState(char pA) {
  // Player's action always happens first
  // cout << "Player moving" << endl;
  pair<int, int> p = handleEntityTurn(pX, pY, pA);
  pX = p.first;
  pY = p.second;
  if(!playerAlive()) return;  // No need to update state further if player died

  // Then other entiies' actions occur
  for(int i = 1; i <= c; ++i) {
    for(int j = 1; j <= r; ++j) {
      if(i == pX && j == pY) continue;
      handleEntityTurn(i, j, pA);
    }
  }
  if(!playerAlive()) return;  // No need to update state further if player died

  // Then tiles perform their actions
  for(int i = 0; i <= c+1; ++i) {
    for(int j = 0; j <= r+1; ++j) {
      tiles[j][i]->doTurn(entities[j][i]);
    }
  }
  if(!playerAlive()) return;  // No need to update state further if player died
  // Now, check for and delete any destroyed entities or tiles, refresh any living entities
  for(int i = 1; i <= c; ++i) {
    for(int j = 1; j <= r; ++j) {
      MovingEntity *e = entities[j][i].get();
      if(e != nullptr) {
        if(e->destroyed()) destroyEntity<MovingEntity>(entities[j][i]);//entities[j][i].reset();
        else entities[j][i]->refreshActions();
      }
      Tile *t = tiles[j][i].get();
      if(t->destroyed()) {
        // Destroyed tiles are replaced by an empty tile
        unique_ptr<Tile> newTile = make_unique<EmptyTile>();
        destroyEntity<Tile>(tiles[j][i], newTile);
      }
    }
  }

  draw();  // Once everything is done, draw the board
}
