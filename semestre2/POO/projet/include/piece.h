#ifndef PIECE_HEADER
#define PIECE_HEADER 1
#include <regex>
#include <iostream>
#include <vector>
#include <string>
#include "../include/square.h"

using namespace std;
bool diagonal_move(Square o, Square d);
bool diagonal_move_pawn(Square o, Square d, string color);

class Piece
{
protected:
  string name;
  string color;
  bool is_white;
  bool already_moved;
  Square pos;
  bool is_pawn;
  bool is_rock;
  bool is_bishop;
  bool is_queen;
  bool is_king;

public:
  virtual bool movment_legal(Square orig, Square dest) const = 0;

  Piece(string _color, string _name, Square _pos, bool _is_pawn) : name(_name), color(_color),
  pos(_pos), is_pawn(_is_pawn)
  {
    cout << "constructeur de : piece " << this->name << " de couleur "<< this->color <<
    " créée en position " << this->pos.to_string() << " " <<
    this->pos.coord_to_string()<< endl;
    this->is_white = false;
    this->already_moved = false;
    this->is_rock = false;
    this->is_bishop = false;
    this->is_rock = false;
    this->is_king = false;
    this->is_pawn = _is_pawn;
    string blanc = "White";
    if (this->color.compare("White")== 0)
      this->is_white = true;
    if( _name.compare(" \u265C ") == 0 || _name.compare(" \u2656 ") == 0)
      this->is_rock = true;

    if( _name.compare(" \u2657 ") == 0 || _name.compare(" \u265D ") == 0)
      this->is_bishop = true;

    if( _name.compare(" \u2655 ") == 0 || _name.compare(" \u265B ") == 0)
      this->is_queen = true;

    if( _name.compare(" \u265A ") == 0 || _name.compare(" \u2654 ") == 0)
      this->is_king = true;
  }

  Piece(string _color, string _name, Square _pos) : name(_name), color(_color),
  pos(_pos)
  {
    cout << "constructeur de : piece " << this->name << " de couleur "<< this->color <<
    " créée en position " << this->pos.to_string() << " " <<
    this->pos.coord_to_string()<< endl;
    this->is_white = false;
    this->already_moved = false;
    string blanc = "White";
    if (this->color.compare("White")== 0)
    {
        this->is_white = true;
    }

  }
  
  string get_name () const;
  string get_color () const;
  Square get_pos () const;
  bool get_is_white () const;
  bool get_already_moved () const;
  bool get_is_pawn() const;
  bool get_is_rock() const;
  bool get_is_bishop() const;
  bool get_is_queen() const;
  bool get_is_king() const;
  void piece_mooved();
  void print () const;
  void set_pos(Square& new_pos);

};


//penser a faire destructeur virtual


class Pawn : public Piece
{
public:
  Pawn(string _color, string _name, Square _pos) : Piece(_color, _name, _pos, true)
  {
    cout << " Constructeur de Pawn: Pawn [" << this->name << "] well created" << endl;
  }
    bool movment_legal(Square orig, Square dest) const;
};




class Rock : public Piece
{
public:
  Rock(string _color, string _name, Square _pos) : Piece(_color, _name, _pos, false)
  {
    cout << "Constructeur de Rock: [" << this->name << "] well created" << endl;
  }

  bool movment_legal(Square orig, Square dest) const;

};


class Bishops : public Piece
{
public:
  Bishops(string _color, string _name, Square _pos) : Piece(_color, _name, _pos, false)
  {
    cout << "Constructeur de Bishops : [" << this->name << "] well created" << endl;
  }

  bool movment_legal(const Square orig, Square dest) const;

};

class Knights : public Piece
{
public:
  Knights(string _color, string _name, Square _pos) : Piece(_color, _name, _pos, false)
  {
    cout << "[" << this->name << "] well created" << endl;
  }

  bool movment_legal(const Square orig, Square dest) const;

};


class Queen : public Piece
{
public:
  Queen(string _color, string _name, Square _pos) : Piece(_color, _name, _pos, false)
  {
    cout << "[" << this->name << "] well created" << endl;
  }

  bool movment_legal(const Square orig, Square dest) const;

};


class King : public Piece
{
public:
  King(string _color, string _name, Square _pos) : Piece(_color, _name, _pos, false)
  {
    cout << "[" << this->name << "] well created" << endl;
  }

  bool movment_legal(const Square orig, Square dest) const;

};
#endif
