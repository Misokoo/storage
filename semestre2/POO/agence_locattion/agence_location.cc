#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Vehicule
{
protected:
  string marque;
  string modele;
  double prix;

public:
  Vehicule(string _marque, string _modele, double _prix):
  marque(_marque), modele(_modele), prix(_prix){}
  virtual void afficher() const
  {
    cout << "[Vehicule] marque:" << marque <<", modèle:" << modele <<" (prix jour : "
    << prix << " Eur)"<< endl;
  }
};

class Utilitaire : public Vehicule
{
protected:
  double cubage;

public:
  Utilitaire(string _marque, string _modele, double _cubage, double _prix):
  Vehicule(_marque, _modele, _prix), cubage(_cubage)
  {
    cout << "-> Utilitaire "<< this->marque << " "<< this->modele << " créé"<< endl;
  }

  void afficher() const
  {
    cout << "[Utilitaire ] marque:" << marque <<", modèle:" << modele <<" (prix jour : "
    << prix << " Eur)"<< "  " << cubage << " m3" << endl;
  }
};


class Voiture : public Vehicule
{
protected:
  size_t portes;

public:
  Voiture(string _marque, string _modele, double _portes, double _prix):
  Vehicule(_marque, _modele,_prix), portes(_portes)
  {
    cout << "-> Voiture "<< _marque << " "<< _modele << " créé" << endl;
  }

  void afficher() const
  {
    cout << "[Voiture] marque:" << marque <<", modèle:" << modele <<" (prix jour : "
    << prix << " Eur)"<< "  " << portes << "  portes" << endl;
  }
};


class Agence
{
protected:
  string nom;
  vector<Vehicule*> vehicules;

public:
  Agence(string _nom): nom(_nom){}
  ~Agence()
  {
    cout << "-> L'agence "<< this->nom << " ferme ses portes."<< endl;
  }
  void ajouter_flotte(Vehicule& _vehicule)
  {
    this->vehicules.push_back(&_vehicule);
  }

  void afficher_flotte() const
  {
    for(size_t i = 0; i< this->vehicules.size(); i++)
    {
      this->vehicules[i]->afficher();
    }
  }

};


int main() {

    Agence malocation("MaLocation");

    // description des utilitaires et voitures a enregistrer dans l'agence

    vector<Utilitaire> utilitaires;
    // constructeur marque,modele,cubage,prix
    utilitaires.push_back( Utilitaire("Mercedes","Vito" ,9.,50.));
    utilitaires.push_back( Utilitaire("Peugeot","Master",9.,45.));
    utilitaires.push_back( Utilitaire("Renault","Kangoo",4.,35.));

    vector<Voiture> voitures;
    // constructeur marque,modele,portes,prix
    voitures.push_back(    Voiture(   "Peugeot","207",   5, 25.));
    voitures.push_back(    Voiture(   "Renault","Clio",  3, 25.));

    // ajout de ces vehicules à la flotte de l'agence.
    for (size_t i(0);i<utilitaires.size();i++)
        malocation.ajouter_flotte(utilitaires[i]);

    for (size_t i(0);i<voitures.size();i++)
        malocation.ajouter_flotte(voitures[i]);

    // affiche la flotte enregistree pour l'agence malocation
    malocation.afficher_flotte();

    return 0;
}
