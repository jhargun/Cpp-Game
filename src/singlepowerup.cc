#include "singlepowerup.h"

SinglePowerUp::SinglePowerUp(int p): Tile{p} {}

void SinglePowerUp::use() { isUsed = true; }

bool SinglePowerUp::wasDestroyed() const { return isUsed; }
