#include <regex>
#include <iostream>
#include <vector>
#include <string>
#include "../include/game.h"
using namespace std;






//--------------------------------------------------------------
int main() {

  Game mygame;
  bool stop(false);
  do {
      mygame.print();
      stop = mygame.hit();
  } while (!stop);
  cout << "end of the game" << endl;

}
