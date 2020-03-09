#ifndef SQUARE_HEADER
#define SQUARE_HEADER 1
#include <regex>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
class Square
{
protected:
  string coord_name;
  size_t coord[2];

public:
  Square(string coord)
  {
    char lettres[] = "abcdefgh";
    int num[] = {1,2,3,4,5,6,7,8};
    char letter = coord.substr(0, 1)[0];
    int nb = atoi(coord.substr(1,1).c_str());
    for(size_t i=0; i< 8; i++)
    {
      if(letter == lettres[i])
      {
        this->coord[1] =  i;
      }
      if(nb == num[i])
      {
        this->coord[0] = i;
      }
    }
    cout << "Constructeur 1  de Square : Square " << coord << " created en position "
    << this->coord_to_string() << endl;
    this->coord_name = coord;
  }


  Square(int _cordx, int _cordy)
  {
    this->coord[0] = _cordx;
    this->coord[1] = _cordy;
    string lettres = "abcdefgh";
    this->coord_name = lettres[_cordy];
    this->coord_name += std::to_string(_cordx +1);
    cout << "Constructeur 2 de Square : Square " << this->coord_name <<
     " created" << this-> coord_to_string() << endl;
  }

  string to_string() const;
  string coord_to_string() const;
  const size_t* get_coord() const;
  void set_square(Square new_square);
  void set_coord(size_t value, size_t idx);
};
  size_t invert_posx(size_t _cordx);
  bool saisie_correcte(string const & cmd);

// bool saisie_correcte_roque(string const & cmd) {
// regex mouvmtpattern("(O|o|0)-(O|o|0)");
//     return regex_match(cmd,mouvmtpattern);
// }




#endif
