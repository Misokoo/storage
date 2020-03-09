#ifndef GAME_HEADER
#define GAME_HEADER 1
#include <regex>
#include <iostream>
#include <vector>
#include <string>
#include "chessboard.h"
using namespace std;
class Game
{
protected:
    Chessboard* cb;
    bool player_white;
public:
  Game()
  {
      this->cb = new Chessboard();
      this->player_white = true;
  }
  bool white_to_play() const;
  void change_player_to_play();
  void print() const;
  bool hit();
  bool deplace(Square& origin, Square& dest);
  bool check_hit_regular(Square origin, Square dest);
};


#endif
