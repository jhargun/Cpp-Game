#include "enemy.h"

Enemy::Enemy(int p, int d, int h, Direction f): LivingEntity{h, p, d, f} {}

Enemy::Enemy(const Enemy &o): LivingEntity{o} {}
