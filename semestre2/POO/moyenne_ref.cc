#include <iostream>   // en remplacement de <stdio.h>
#include <vector>
using namespace std;

void saisie(int nb_val, vector<int> &tab)
{
  int valeur;
  for(int i=0; i<nb_val; i++)
  {
    cout << "donner une valeur" << endl;
    cin >> valeur;
    tab.push_back(valeur);
    cout << "la valeur d'indice " << i << " vaut " << valeur << endl;
  }
}

void affiche(vector<int> &tab)
{
  cout << "-------------------" << endl;
  cout << " | ";
  for(int i=0; i<tab.size() ; i++)
  {
    cout << tab[i] << " | " ;
  }
  cout << endl;
  cout << "-------------------" << endl;
}

double moyenne(vector<int> &tab)
{
  double moy=0;
  for(int i=0; i<tab.size(); i++)
  {
    moy = moy + tab[i];
  }
  moy = moy/tab.size();
  return moy;
}

int main()
{
  int val_saisie;
  cout << "donner une taille de tableau" << endl;
  cin >> val_saisie;

  vector<int> montab;

  saisie(val_saisie, montab);
  double ma_moy = moyenne(montab);
  affiche(montab);
  cout << "la moyenne est de " << ma_moy << endl;

  return 0;
}
