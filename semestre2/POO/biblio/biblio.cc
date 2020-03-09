#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*******************************************
 * Completez le programme a partir d'ici.
 *******************************************/
class Auteur
{
private:
  string name;
  bool prime;

public:
  Auteur(string _name) : name(_name), prime(false){}
  Auteur(string _name, bool _prime) : name(_name), prime(_prime){}

  string getNom() ///*const*/
  {
    return this->name;
  }

  bool get_prix()
  {
    return this->prime;
  }
};

class Oeuvre
{
private:
  string name;
  ///*const*/
  Auteur& auteur;
  string langue;

public:
  Oeuvre(string _name, /*const*/ Auteur& _auteur, string _langue):name(
    _name), auteur(_auteur), langue(_langue){}

  ~Oeuvre()
  {
    cout << "L'oeuvre :\"" << this->name << ", " << this->auteur.getNom()
    << ", en " << this->langue << "\" n'est plus disponible" << endl;
  }

  string getTitre()
  {
    return this->name;
  }

  /*const*/ Auteur& getAuteur()
  {
    return this->auteur;
  }

  string getLangue()
  {
    return this->langue;
  }

  void affiche() /*const*/
  {
    cout << this->name << ", " << this->auteur.getNom()
    << ", en " << this->langue ;
  }

};

class Exemplaire
{
private:
  /*const*/ Oeuvre& oeuvre;

public:

  Exemplaire (Oeuvre& _oeuvre):oeuvre(_oeuvre)
  {
    cout << "Nouvel exemplaire de : " ;
    this->oeuvre.affiche();
    cout << endl;
  }

  // Exemplaire(/*const*/ Exemplaire& e)
  // {
  //   this.oeuvre = e.oeuvre;
  //   cout << "copie d'un exemplaire de "<< this->oeuvre.getTitre() << ", " << this->oeuvre.getAuteur().getNom()
  //   << ", en " << this->oeuvre.getLangue() << endl;
  // }

  ~Exemplaire()
  {
    cout << "Un exemplaire de " ;
    this->oeuvre.affiche();
    cout << " a été jeté !" << endl;
  }

  /*const*/ Oeuvre& getOeuvre()
  {
    return this->oeuvre;
  }

};

class Bibliotheque
{
private:
  string name;
  vector<Exemplaire*> exemplaires;

public:
  //void afficher_auteurs(bool prime=false);
  Bibliotheque(string _name): name(_name)
  {
    cout << "La bibliotheque " << this->name << "est ouverte !" << endl;
  }

  ~Bibliotheque()
  {
    cout << "La bibliotheque " << this->name << " ferme ses portes,"<< endl <<" et detruit ses exemplaires : " << endl;
    for(size_t i = 0; i < this->exemplaires.size(); i++)
    {
      delete this->exemplaires[i];
    }
  }

  string getNom()
  {
    return this->name;
  }

  void stocker(Oeuvre& _oeuvre, int nb)
  {
    // Exemplaire e(_oeuvre);
    for(int i=0; i<nb; i++)
    {
      this->exemplaires.push_back(new Exemplaire(_oeuvre));
    }
  }

  void stocker(Oeuvre&  oeuvre)
  {
    //Exemplaire e(oeuvre);
    this->exemplaires.push_back(new Exemplaire(oeuvre));
  }

  void lister_exemplaires()
  {
    for(unsigned int i=0; i<this->exemplaires.size(); i++)
    {
      cout << "Exemplaire de : \"" << this->exemplaires[i]->getOeuvre().getTitre() << ","
      << this->exemplaires[i]->getOeuvre().getAuteur().getNom()<< ","
      << " en " << this->exemplaires[i]->getOeuvre().getLangue() << "\"" << endl;
    }
  }

  void lister_exemplaires(string langue)
  {
    for(unsigned int i=0; i<this->exemplaires.size(); i++)
    {
      if(langue == this->exemplaires[i]->getOeuvre().getLangue())
      {
        cout << "Exemplaire de : \"" << this->exemplaires[i]->getOeuvre().getTitre() << ","
        << this->exemplaires[i]->getOeuvre().getAuteur().getNom()<< ","
        << " en " << this->exemplaires[i]->getOeuvre().getLangue() << "\"" << endl;
      }
    }
  }

  void afficher_auteurs(bool prime=false)
  {
    if(prime)
    {
      for(unsigned int i=0; i< this->exemplaires.size(); i++)
      {
        if (this->exemplaires[i]->getOeuvre().getAuteur().get_prix())
        {
          cout << this->exemplaires[i]->getOeuvre().getAuteur().getNom() << endl;
        }
      }
    }
  }

  int compter_exemplaires( Oeuvre& oeuvre)
  {
    int cpt=0;
    for(unsigned int i=0; i< this->exemplaires.size(); i++)
    {
      if ((this->exemplaires[i]->getOeuvre().getTitre() == oeuvre.getTitre())
        && (this->exemplaires[i]->getOeuvre().getLangue() == oeuvre.getLangue())
        && (this->exemplaires[i]->getOeuvre().getAuteur().getNom() == oeuvre.getAuteur().getNom())
        && (this->exemplaires[i]->getOeuvre().getAuteur().get_prix() == oeuvre.getAuteur().get_prix())
      )
      {
        cpt++;
      }
    }
    return cpt;
  }

};



// cout << "Un exemplaire de :\"" << this->name << ", " << this->auteur
// << ", en " << this->langue << "\"" << endl;

/*******************************************
 * Ne rien modifier apres cette ligne.
 *******************************************/

int main()
{
  Auteur a1("Victor Hugo"),
         a2("Alexandre Dumas"),
         a3("Raymond Queneau", true);

  Oeuvre o1("Les Misérables"           , a1, "français" ),
         o2("L'Homme qui rit"          , a1, "français" ),
         o3("Le Comte de Monte-Cristo" , a2, "français" ),
         o4("Zazie dans le métro"      , a3, "français" ),
         o5("The Count of Monte-Cristo", a2, "anglais" );

  Bibliotheque biblio("municipale");
  biblio.stocker(o1, 2);
  biblio.stocker(o2);
  biblio.stocker(o3, 3);
  biblio.stocker(o4);
  biblio.stocker(o5);

  cout << "La bibliothèque " << biblio.getNom()
       << " offre les exemplaires suivants :" << endl;
  biblio.lister_exemplaires();

  /*const*/ string langue("anglais");
  cout << " Les exemplaires en "<< langue << " sont :" << endl;
  biblio.lister_exemplaires(langue);

  cout << " Les auteurs à succès sont :" << endl;
  biblio.afficher_auteurs(true);

  cout << " Il y a " << biblio.compter_exemplaires(o3) << " exemplaires de "
       << o3.getTitre() << endl;

  return 0;
}
