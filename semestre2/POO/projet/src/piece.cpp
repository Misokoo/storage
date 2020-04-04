#include <regex>
#include <iostream>
#include <vector>
#include <string>
#include "../include/piece.h"
#include <cstdlib>
using namespace std;

bool diagonal_move(Square o, Square d)
{
  bool result(false);

  if (abs((int)(d.get_coord()[0] - o.get_coord()[0])) == abs((int)(d.get_coord()[1] - o.get_coord()[1])))
    result = true;
  return result;
}

bool diagonal_move_pawn(Square o, Square d, string color)
{
  bool result(false);
  if (abs((int)(d.get_coord()[0] - o.get_coord()[0])) == abs((int)(d.get_coord()[1] - o.get_coord()[1])) && color.compare("Black") == 0 &&
      (int)(d.get_coord()[0] - o.get_coord()[0]) == -1)
    result = true;
  else if (abs((int)(d.get_coord()[0] - o.get_coord()[0])) == abs((int)(d.get_coord()[1] - o.get_coord()[1])) && color.compare("White") == 0 &&
           (int)(d.get_coord()[0] - o.get_coord()[0]) == 1)
    result = true;
  return result;
}

bool straight_move(Square o, Square d)
{
  bool result(false);

  if (abs((int)(d.get_coord()[0] - o.get_coord()[0])) == 0 &&
      abs((int)(d.get_coord()[1] - o.get_coord()[1])))
    result = true;
  else if (abs((int)(d.get_coord()[1] - o.get_coord()[1])) == 0 &&
           abs((int)(d.get_coord()[0] - o.get_coord()[0])))
    result = true;

  return result;
}

string
Piece::get_name() const
{
  return this->name;
}

string
Piece::get_color() const
{
  return this->color;
}

bool Piece::get_is_white() const
{
  return this->is_white;
}

bool Piece::get_already_moved() const
{
  return this->already_moved;
}

bool Piece::get_is_pawn() const
{
  return this->is_pawn;
}

bool Piece::get_is_rock() const
{
  return this->is_rock;
}

bool Piece::get_is_bishop() const
{
  return this->is_bishop;
}

bool Piece::get_is_queen() const
{
  return this->is_queen;
}

bool Piece::get_is_king() const
{
  return this->is_king;
}

Square
Piece::get_pos() const
{
  return this->pos;
}

void Piece::print() const
{
  cout << this->name;
}

void Piece::set_pos(Square &new_pos)
{
  this->pos.set_square(new_pos); // faudrait faire un delete de this->pos avant
}

void Piece::piece_mooved()
{
  this->already_moved = true;
}

//////////////////////////////////////////////
//penser a faire destructeur virtual

bool Pawn::movment_legal(Square orig, Square dest) const
{
  bool reponse(false);
  //Piece *case_dest = cb->piece_on_cb(invert_posx(dest.get_coord()[0]),dest.get_coord()[1]);
  if (this->get_color().compare("White") == 0 &&
      (dest.get_coord()[0] - orig.get_coord()[0]) == 1 &&
      !(dest.get_coord()[1] - orig.get_coord()[1]))
  {
    reponse = true;
  }
  else if (this->get_color().compare("Black") == 0 &&
           (int)(dest.get_coord()[0] - orig.get_coord()[0]) == -1 &&
           !(dest.get_coord()[1] - orig.get_coord()[1]))
  {
    reponse = true;
  }
  else if (this->get_color().compare("White") == 0 &&
           !this->get_already_moved() &&
           (dest.get_coord()[0] - orig.get_coord()[0]) == 2 &&
           !(dest.get_coord()[1] - orig.get_coord()[1]))
  {
    cout << "moove de 2 white" << endl;
    reponse = true;
  }
  else if (this->get_color().compare("Black") == 0 &&
           !this->get_already_moved() &&
           (int)(dest.get_coord()[0] - orig.get_coord()[0]) == -2 &&
           !(dest.get_coord()[1] - orig.get_coord()[1]))
  {
    cout << "moove de 2 black" << endl;
    reponse = true;
  }
  return reponse;
}

//////////////////////////////////////////

bool Rock::movment_legal(Square orig, Square dest) const
{
  cout << "we are mooving a rock" << endl;
  bool result = straight_move(orig, dest);
  if (!result)
    cout << "Rocks only moove in a straight way" << endl;
  return result;
}

///////////////////////////////
bool Bishops::movment_legal(const Square orig, Square dest) const 
{
  cout << "we are mooving a bishop" << endl;
  bool result = diagonal_move(orig, dest);
  if (!result)
    cout << "Bishops only moove in diag" << endl;
  return result;
}

bool Queen::movment_legal(const Square orig, Square dest) const
{
  bool result(false);
  if (diagonal_move(orig, dest) || straight_move(orig, dest))
  {
    cout << "you are mooving the queen" << endl;
    return true;
  }
  cout << "queen doesnt moove that way" << endl;
  return result;
}

bool King::movment_legal(const Square o, Square d) const
{
  bool result(false);
  if (abs((int)(d.get_coord()[0] - o.get_coord()[0])) == 1 ||
      abs((int)(d.get_coord()[1] - o.get_coord()[1])) == 1)
  {
    cout << "you are mooving a KING" << endl;
    return true;
  }

  cout << "Kings dont moove that way" << endl;
  return result;
}

bool Knights::movment_legal(const Square o, Square d) const
{
  bool result(false);
  if ((abs((int)(d.get_coord()[0] - o.get_coord()[0])) +
       abs((int)(d.get_coord()[1] - o.get_coord()[1]))) == 3 &&
      abs((int)(d.get_coord()[0] - o.get_coord()[0])) < 3 &&
      abs((int)(d.get_coord()[1] - o.get_coord()[1])) < 3)
  {
    cout << "you are mooving a Knights" << endl;
    return true;
  }
  cout << "Knights dont moove that way" << endl;
  return result;
}
