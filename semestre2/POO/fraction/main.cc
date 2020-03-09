#include <iostream>
#include "fraction.h"
using namespace std;


int main()
{

  Fraction f1(1, 2);
  Fraction f2(2, 4);
  Fraction f3(f2);
  Fraction f4 =f2.multiplie(f3);

  cout << "valeur de f4" << endl;
  f4.affiche(cout);
  f3 = f1.additionne(f4);

  cout << "valeur de f3 : (f1+f4)" << endl;
  f3.affiche(cout);

  Fraction f5 = f4.simplifie(f4);

  cout << "valeur de f5 : " << endl;
  f5.affiche(cout);

  Fraction f6 = f1 + f4;
  cout << "1/2 + 4/9 (valeur de f6)" << endl;
  f6.affiche(cout);

  Fraction f7 = f1 * f4;
  cout << "1/2 * 4/9 : (valeur de f7)" << endl;
  f7.affiche(cout);

  //f7 << cout;
  cout << "test2" << endl ;
  cout << f7;

  return 0;
}
