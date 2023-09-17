#include <iostream>
#include "movingentity.h"
#include "player.h"

using namespace std;

Player::Player(int h): LivingEntity{h} {}
Player::Player(int h, Direction f): LivingEntity{h, f} {}

bool Player::player() const { return true; }
void Player::doDraw() const { cout << "P"; }

// wasd moves player, ijkl changes direction that character is facing,
// f fires a projectile, and h hits
pair<Action, Direction> Player::nextA(int pX, int pY, char c, Tile *topT,
    MovingEntity *topE, Tile *bottomT, MovingEntity *bottomE, Tile *rightT,
    MovingEntity *rightE, Tile *leftT, MovingEntity *leftE) {
  // cout << "nextA called on " << c << endl;
  switch(c) {
    case 'w': return pair<Action, Direction>{Action::Move, Direction::Up};
    case 'a': return pair<Action, Direction>{Action::Move, Direction::Left};
    case 's': return pair<Action, Direction>{Action::Move, Direction::Down};
    case 'd': return pair<Action, Direction>{Action::Move, Direction::Right};
    case 'i': return pair<Action, Direction>{Action::Face, Direction::Up};
    case 'j': return pair<Action, Direction>{Action::Face, Direction::Left};
    case 'k': return pair<Action, Direction>{Action::Face, Direction::Down};
    case 'l': return pair<Action, Direction>{Action::Face, Direction::Right};
    case 'f': return pair<Action, Direction>{Action::Shoot, getFacing()};
    case 'h': return pair<Action, Direction>{Action::Hit, getFacing()};
    default:
      cout << c << " is not a valid command for the player" << endl;
      return pair<Action, Direction>{Action::DoNothing, getFacing()};
  }
}
