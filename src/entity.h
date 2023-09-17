#ifndef ENTITY_H_
#define ENTITY_H_

class Entity {
  int points;
protected:
  Entity(const Entity&);  // Copy ctor
  virtual void doDraw() const = 0;  // Used by draw() to follow NVII
  virtual bool enterable() const;  // Used by canEnter() to follow NVII
  virtual bool wasDestroyed() const;  // Called by destroyed() to follow NVII idiom
public:
  Entity(int p = 0);  // Ctor takes point value of entity if destroyed, 0 by default
  void draw() const;  // Draws the entity
  // Returns true if another entity can enter the same space as this entity
  bool canEnter() const;
  /* Returns true if this entity was destroyed. This can meet it hit something
  for Projectiles, it ran out of health for LivingEntities, or it applied its
  single use powerup for PowerupTiles. */
  bool destroyed() const;
  int getPoints() const;  // Returns point value if destroyed
  virtual ~Entity() = default;
};

#endif
