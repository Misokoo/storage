#include <iostream>
using namespace std;

class Fraction
{
public:
  Fraction();
  Fraction (int _num, int _den);

  const int get_num ();
  const int get_den();
  const Fraction additionne(Fraction f1);
  Fraction multiplie(Fraction f1);
  void affiche(ostream& flux);
  void setNum(double val);
  void setDen(double val);
  Fraction simplifie(Fraction f);
  // Fraction operator+(Fraction &f1, Fraction &f2);
  // Fraction operator*(Fraction &f1, Fraction &f2);
  // ostream &operator<<( ostream &flux, Fraction& f);


  Fraction operator+(Fraction const &f) const;
  Fraction operator*(Fraction const &f) const;

private:

  int pgcd (int a, int b);
  int num;
  int den;



};
ostream& operator<<(ostream &flux, Fraction &f);
