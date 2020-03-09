#include <iostream>   // en remplacement de <stdio.h>
using namespace std;

void saisie(int* tab, int nb_val)
{
  int valeur;
  for(int i=0; i<nb_val; i++)
  {
    cout << "donner une valeur" << endl;
    cin >> valeur;
    tab[i] = valeur;
    cout << "la valeur d'indice " << i << " vaut " << valeur << endl;
  }
}

void affiche(const int* tab, int length)
{
  cout << "-------------------" << endl;
  cout << " | ";
  for(int i=0; i<length ; i++)
  {
    cout << tab[i] << " | " ;
  }
  cout << endl;
  cout << "-------------------" << endl;
}

double moyenne(const int* tab, int length)
{
  double moy=0;
  for(int i=0; i<length; i++)
  {
    moy = moy + tab[i];
  }
  moy = moy/length;
  return moy;
}

int main()
{
  int val_saisie;
  cout << "donner une taille de tableau" << endl;
  cin >> val_saisie;

  int* montab;
  montab = new int[val_saisie];

  saisie(montab, val_saisie);
  double ma_moy = moyenne(montab, val_saisie);
  affiche(montab, val_saisie);
  cout << "la moyenne est de " << ma_moy << endl;

  delete[] montab;

  return 0;
}
