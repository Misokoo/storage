#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ======================================================================
class Article
{
private:
  string name;
  double price;
  bool solde;

public:
  Article(string _name, double _price, bool _solde): name(_name),
  price(_price), solde(_solde){}

  Article(string _name, double _price): name(_name),
  price(_price), solde(false){}

  string get_name()
  {
    return this->name;
  }

  double get_price()
  {
    return this->price;
  }

  bool get_solde()
  {
    return this->solde;
  }

};



class Achat
{
private:
  Article article;
  int amount;

public:
  Achat(Article _article, int _amount): article(_article), amount(_amount)
  {}

  void afficher()
  {
    cout << this->article.get_name() << " :";
    cout << this->article.get_price() << " x " << this->amount
    << " = " << this->price_achat() << " Eur";
    if (this->article.get_solde())
    {
      cout << "   (en solde)";
    }
    cout << endl;
  }

  double price_achat()
  {
    return this->article.get_solde() ? (this->amount * this->article.get_price() )/2 : this->amount * this->article.get_price();
  }
};



class Caddie
{
private:
  vector<Achat> caddie;

public:
  Caddie()
  {}

  void remplir(Article _article, int _amount)
  {
    Achat achat(_article, _amount);
    this->caddie.push_back(achat);
  }

  void remplir(Article& _article)
  {
    Achat achat(_article, 1);
    this->caddie.push_back(achat);
  }

  int get_size()
  {
    return this->caddie.size();
  }


  double get_caddie_price()
  {
    double sum = 0;
    for(unsigned int i=0; i< this->caddie.size(); i++)
    {
      sum += this->caddie[i].price_achat();
    }
    return sum;
  }


  void print_caddie()
  {
    for(unsigned int i=0; i<this->caddie.size(); i++)
    {
      this->caddie[i].afficher();
    }
    cout << "-----" << endl;
    cout << "Total à payer : " << this->get_caddie_price() << " Eur." << endl;
  }

};



class Caisse
{
private:
  const static int id = 1;
  double amount_total;

public:
  Caisse() : amount_total(0)
  {}

  void afficher()
  {
    cout << "total : " << this->amount_total << " Eur";
  }

  void scanner(Caddie caddie)
  {
    caddie.print_caddie();
    this->amount_total += caddie.get_caddie_price();
  }


};

// ======================================================================

int main()
{
  // Les articles vendus dans le supermarché
  Article choufleur ("Chou-fleur extra"      ,  3.50 );
  Article roman     ("Les malheurs de Sophie", 16.50, true );
  Article camembert ("Cremeux 100%MG"        ,  5.80 );
  Article cdrom     ("C++ en trois jours"    , 48.50 );
  Article boisson   ("Chocolats"             ,  2.50, true);
  Article petitspois("Pois surgeles"         ,  4.35 );
  Article poisson   ("Sardines"              ,  6.50 );
  Article biscuits  ("Cookies de grand-mere" ,  3.20 );
  Article poires    ("Poires Williams"       ,  4.80 );
  Article cafe      ("100% Arabica"          ,  6.90, true);
  Article pain      ("Pain d'epautre"        ,  6.90 );

  // Les caddies du supermarché, disons 3 ici
  vector<Caddie> caddies(3);

  // Les caisses du supermarché, disons 2
  vector<Caisse> caisses(2);

  // Les clients font leurs achats :
  // le second argument de la méthode remplir correspond à une quantité

  // remplissage du 1er caddie
  caddies[0].remplir(choufleur, 2);
  caddies[0].remplir(cdrom       );
  caddies[0].remplir(biscuits , 4);
  caddies[0].remplir(boisson  , 6);
  caddies[0].remplir(poisson  , 2);

  // remplissage du 2eme caddie
  caddies[1].remplir(roman        );
  caddies[1].remplir(camembert    );
  caddies[1].remplir(petitspois, 2);
  caddies[1].remplir(poires    , 2);

  // remplissage du 3eme caddie
  caddies[2].remplir(cafe     , 2);
  caddies[2].remplir(pain        );
  caddies[2].remplir(camembert, 2);

  // Les clients passent à la caisse :
  caisses[0].scanner(caddies[0]);
  cout << "=========================================" << endl;
  caisses[0].scanner(caddies[1]);
  cout << "=========================================" << endl;
  caisses[1].scanner(caddies[2]);
  cout << "=========================================" << endl;

  // Affichage du résultat des caisses
  cout << "Résultats du jour :" << endl;
  for (size_t i(0); i < caisses.size(); ++i) {
    cout << "Caisse " << i+1 << " : " ;
    caisses[i].afficher();
    cout << endl;
  }
  return 0;
}
