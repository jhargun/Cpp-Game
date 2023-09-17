#include <iostream>
#include "board.h"
using namespace std;

int main() {
  Board b{3, 7, true};
  b.draw();
  char cmd;
  while(cin >> cmd && cmd != 'q') {
    cout << endl;
    b.updateState(cmd);
    // b.draw();
    if(!(b.playerAlive())) {
      cout << "Player died" << endl;
      return 0;
    }
    else if(b.victory()) {
      cout << "You win with score " << b.getScore() << endl;
      return 0;
    }
  }
}
