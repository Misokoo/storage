#include <iostream>
#include "fraction.h"
using namespace std;

Fraction::Fraction() : num(1), den(1) {}
Fraction::Fraction (int _num, int _den): num(_num), den(_den)
{}

int Fraction::pgcd (int a, int b) {
  int r = a % b;

  if (r == 0)
        return b;
  else
        return pgcd (b, r);
}

Fraction const Fraction::additionne (Fraction f1)
{
  Fraction f3(this->num*f1.den + f1.num*this->den,
   this->den * f1.den);
  return f3;
}

Fraction Fraction::multiplie(Fraction f1)
{
  Fraction f2(this->num*f1.num, this->den*f1.den);
  return f2;
}


void Fraction::affiche(ostream &flux)
{
  flux << this->num << "/" << this->den << endl;
  //flux << "Hello" << endl;
}



Fraction Fraction::simplifie(Fraction f)
{
  int div = pgcd(f.num, f.den);
  Fraction ff(f.num/div, f.den/div);
  return ff;
}


Fraction Fraction::operator+(Fraction const &f) const
{
  return Fraction(num*f.den +f.num*den, den*f.den);
}

Fraction Fraction::operator*(Fraction const &f) const {
      return Fraction(num*f.num,den*f.den);
}

// ostream& operator<<(ostream &flux)
// {
//     cout << "affichage avec overloadedoperateur" << endl;
//     this->affiche(cout);
//     return flux;
// }

ostream& operator<<(ostream &flux, Fraction &f)
{
    cout << "affichage avec overloadedoperateur" << endl;
    f.affiche(cout);
    return flux;
}






















// int pgcd (int a, int b) {
//   int r = a % b;
//
//   if (r == 0)
//         return b;
//   else
//         return pgcd (b, r);
// }
// class Fraction
// {
// private:
//   int num;
//   int den;
// public:
//   Fraction() : num(1), den(1) {}
//   Fraction (int _num, int _den): num(_num), den(_den)
//   {}
//
//   const int get_num ()
//   {
//     return this->num;
//   }
//
//   const int get_den()
//   {
//     return this->den;
//   }
//
//   // Fraction additionne(Fraction f1)
//   // {
//   //   Fraction f3(this->num*f1.den + f1.num*this->den,
//   //    this->den * f1.den);
//   //   return f3;
//   // }
//
//   const Fraction additionne(Fraction f1)
//   {
//     Fraction f3(this->get_num()*f1.get_den() + f1.get_num()*this->get_den(),
//      this->get_den() * f1.get_den());
//     return f3;
//   }
//
//   Fraction multiplie(Fraction f1)
//   {
//     Fraction f2(this->num*f1.num, this->den*f1.den);
//     return f2;
//   }
//
//   void affiche()
//   {
//     cout << this->num << "/" << this->den << endl;
//   }
//
//   void setNum(double val)
//   {
//     this->num = val;
//   }
//
//   void setDen(double val)
//   {
//     this->den = val;
//   }
//
//   Fraction simplifie(Fraction f)
//   {
//     int div = pgcd(f.num, f.den);
//     Fraction ff(f.num/div, f.den/div);
//     return ff;
//   }
//
// };
//
// Fraction operator+(Fraction &f1, Fraction &f2)
// {
//   Fraction f3;
//   f3 = f1.additionne(f2);
//   return f3;
// }
//
// Fraction operator*(Fraction &f1, Fraction &f2)
// {
//   Fraction f3;
//   f3 = f1.multiplie(f2);
//   return f3;
// }
//
// ostream &operator<<( ostream &flux, Fraction& f)
// {
//     f.affiche();
//     return flux;
// }
//
// int main()
// {
//
//   Fraction f1(1, 2);
//   Fraction f2(2, 4);
//   Fraction f3(f2);
//   Fraction f4 =f2.multiplie(f3);
//
//   cout << "valeur de f4" << endl;
//   f4.affiche();
//   f3 = f1.additionne(f4);
//
//   cout << "valeur de f3 : (f1+f4)" << endl;
//   f3.affiche();
//
//   Fraction f5 = f4.simplifie(f4);
//
//   cout << "valeur de f5 : " << endl;
//   f5.affiche();
//
//   Fraction f6 = f1 + f4;
//   cout << "1/2 + 4/9 (valeur de f6)" << endl;
//   f6.affiche();
//
//   Fraction f7 = f1 * f4;
//   cout << "1/2 * 4/9 : (valeur de f7)" << endl;
//   f7.affiche();
//
//   cout << "on test le cout de frac avec f7 : " << f7 << endl;
//
//   return 0;
// }
