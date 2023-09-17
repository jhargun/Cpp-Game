#ifndef MAGICENEMY_H_
#define MAGICENEMY_H_

#include <memory>
#include <utility>
#include <iostream>
#include <utility>
#include <memory>
#include "movingentity.h"
#include "livingentity.h"
#include "getrand.h"

class Tile;
class MovingEntity;

// template<typename T>
// class MagicEnemy final: public LivingEntity {
//   std::unique_ptr<T> e;  // Pointer to enemy that was made magic
//   bool wasDamaged = false;  // True if enemy was damaged last turn
// protected:
//   void onAttack(int) override;
//   void refAc() override;
//   void doDraw() const override;
//   std::pair<Action, Direction> nextA(int pX, int pY, char c, Tile *topT,
//     MovingEntity *topE, Tile *bottomT, MovingEntity *bottomE, Tile *rightT,
//     MovingEntity *rightE, Tile *leftT, MovingEntity *leftE) override;
// public:
//   /* First 4 ctors take an enemy and make it magic by stealing the Enemy* from
//   the provided unique_ptr, while the copy ctor is for cloning */
//   MagicEnemy(std::unique_ptr<T> &);  // Steals pointer from this unique_ptr
//   MagicEnemy(std::unique_ptr<T> &, int h, int p, int d);
//   MagicEnemy(T*, int h, int p, int d);
//   MagicEnemy(std::unique_ptr<T> &&);
//   MagicEnemy(std::unique_ptr<T> &&, int h, int p, int d);
//   MagicEnemy(const MagicEnemy<T> &);  // Copy ctor
//   // MagicEnemy(const std::unique_ptr<MagicEnemy> &);
//   // MagicEnemy(const std::unique_ptr<MovingEntity> &);  // Throws if not a MagicEnemy
// };

// Note: Since I'm using templating, I had to put the implementation
// in this header file.

template<typename T>
class MagicEnemy final: public LivingEntity {
  std::unique_ptr<T> e;  // Pointer to enemy that was made magic
  bool wasDamaged = false;  // True if enemy was damaged last turn
protected:
  void onAttack(int d) override {
    LivingEntity::onAttack(d);
    wasDamaged = true;
  }
  void refAc() override { e->refreshActions(); }
  void exAc() override { e->exhaustActions(); }
  void doDraw() const override { std::cout << "M"; }
  std::pair<Action, Direction> nextA(int pX, int pY, char c, Tile *topT,
      MovingEntity *topE, Tile *bottomT, MovingEntity *bottomE, Tile *rightT,
      MovingEntity *rightE, Tile *leftT, MovingEntity *leftE) override {
        if(wasDamaged) {
          wasDamaged = false;  // Only 1 magic action per damage
          // 1/3 chance of clone, teleport, or a regular action
          int i = getRand(3);
          if(i == 0) return std::pair<Action, Direction>{Action::Clone, Direction::Up};
          else if(i == 1) return std::pair<Action, Direction>{Action::Teleport, Direction::Up};
        }
        return e->nextAction(pX, pY, c, topT, topE, bottomT, bottomE, rightT,
          rightE, leftT, leftE);
    }
public:
  /* First 4 ctors take an enemy and make it magic by stealing the Enemy* from
  the provided unique_ptr, while the copy ctor is for cloning */
  MagicEnemy(std::unique_ptr<T> &o):
    LivingEntity{*o}, e{o.release()} {}  // Steals pointer from this unique_ptr
  MagicEnemy(std::unique_ptr<T> &o, int h, int p, int d):
    LivingEntity{h, p, d}, e{o.release()} {}
  MagicEnemy(T* o, int h, int p, int d):
    LivingEntity{h, p, d}, e{o} {}
  MagicEnemy(std::unique_ptr<T> &&o):
    LivingEntity{*o}, e{o.release()} {}
  MagicEnemy(std::unique_ptr<T> &&o, int h, int p, int d):
    LivingEntity{h, p, d}, e{o.release()} {}
  MagicEnemy(const MagicEnemy<T> &o): LivingEntity{o},
    e{std::make_unique<T>(*(o.e))} {
      this->exhaustActions();  // When copy constructed, entity is exhausted
    }
  // MagicEnemy(const std::unique_ptr<MagicEnemy> &);
  // MagicEnemy(const std::unique_ptr<MovingEntity> &);  // Throws if not a MagicEnemy
};

#endif
