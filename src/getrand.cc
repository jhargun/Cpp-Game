#include <random>
#include <ctime>
#include "getrand.h"

int getRand(int max) {
  // Seed generator with current time, then return int
  std::srand(std::time(nullptr));
  return std::rand() % max;
}
