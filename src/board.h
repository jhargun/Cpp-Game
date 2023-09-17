#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include <memory>
#include <utility>

#include "tile.h"
#include "movingentity.h"

class Board {
  bool verbose;  // If true, prints board everytime an entity performs an action
  unsigned int r, c;  // Stores rows and columns in board
  int pX, pY;  // Stores the player's position
  int score;  // Store's the player's score
  // These 2D vectors store the tiles of the board and any entities
  std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
  std::vector<std::vector<std::unique_ptr<MovingEntity>>> entities;

  /* This helper is used to get a reference to the unique_ptr in direction d
  from the provided coordinates in the 2D vector v. Used in handleEntityTurn */
  // std::unique_ptr<MovingEntity>& getInDirection(int x, int y, Direction d);
  template <typename T>
  std::unique_ptr<T>& getInDirection(int x, int y, Direction d, std::vector<std::vector<std::unique_ptr<T>>>&) const;

  // These helpers are used to get the score of an entity and then destroy them
  template <typename T>
  void destroyEntity(std::unique_ptr<T> &p, std::unique_ptr<T> &newP);
  template <typename T>
  void destroyEntity(std::unique_ptr<T> &p, T *newP);
  template <typename T>
  void destroyEntity(std::unique_ptr<T> &p);

  // Updates score as if entity p was destroyed
  template <typename T>
  void updateScore(std::unique_ptr<T> &p);

  // Helper, finds a tile that's enterable and doesn't have a MovingEntity on it
  std::pair<int, int> getRandEmpty() const;

  // Helper, gets reference to unique_ptr to MovingEntity in direction from coords
  std::pair<int, int> handleEntityTurn(int x, int y, char pA);
public:
  // This ctor Board with a specified size filled with EmptyTiles
  Board(unsigned int rows, unsigned int cols, bool v = true, int s = 0);
  void draw() const;
  bool playerAlive() const;  // returns true if player is alive, false otherwise
  bool victory() const;  // Returns true if player on a goal tile, false otherwise
  int getScore() const;  // Gets the current score

  // Takes a character representing player's action and updates the board state
  void updateState(char);
};

#endif
