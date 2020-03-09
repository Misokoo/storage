#include <regex>
#include <iostream>
#include <vector>
#include <string>
#include "../include/game.h"
#include "../include/square.h"
using namespace std;

void Game::print() const
{
  this->cb->print();
  string player_color[] = {"Black", "White"};
  cout << " player " << player_color[this->player_white] << " to play" << endl;
}

bool Game::deplace(Square &origin, Square &dest)
{
  return this->cb->moove_piece(origin, dest);
}

bool Game::white_to_play() const
{
  return this->player_white;
}

void Game::change_player_to_play()
{
  this->player_white = !this->player_white;
}

bool Game::check_hit_regular(Square origin, Square dest)
{
  bool reponse(true);
  string player_color[] = {"Black", "White"};
  if (this->cb->piece_on_cb(invert_posx(origin.get_coord()[0]),origin.get_coord()[1]) == NULL)
  {
    cout << "the case you selected is empty" << endl;
    return false;
  }

  if (this->player_white != this->cb->piece_on_cb(invert_posx(origin.get_coord()[0]),origin.get_coord()[1])->get_is_white())
  {
    return false;
  }
  //cout << dest.to_string();
  if (this->cb->piece_on_cb(invert_posx(dest.get_coord()[0]),dest.get_coord()[1]) != NULL &&
  this->player_white == this->cb->piece_on_cb(invert_posx(dest.get_coord()[0]),dest.get_coord()[1])->get_is_white())
  {
    cout << "you tried to eat one of your own pieces" << endl;
    return false;
  }

  return reponse;
}

bool Game::hit()
{
  bool test = false;
  string my_hit;
  cin >> my_hit;
  if (my_hit == "/quit")
  {
    cout << "you've asked for the end of the game" << endl;
    return true;
  }
  Square origin(my_hit.substr(0, 2));
  Square dest(my_hit.substr(2, 2));
  if (saisie_correcte(my_hit) && check_hit_regular(origin, dest))
  {
    //cout << "on fait le moove de " << my_hit << endl;
    //this->cb->moove_piece(origin, dest);
    if ((test = this->deplace(origin, dest)) == true)
    {
      cout << "coup bien joué, on change de personne" << endl;
      change_player_to_play();
    }

    //cout << my_hit << endl;
  }
  return false;
}
