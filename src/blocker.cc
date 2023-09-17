#include <iostream>
#include "blocker.h"

using namespace std;

// Blockers can't be entered
bool Blocker::enterable() const { return false; }

Blocker::~Blocker() {}

void OuterBoundary::doDraw() const { cout << 'X'; }
void Tree::doDraw() const { cout << 'T'; }
void Rock::doDraw() const { cout << 'R'; }
