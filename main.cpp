#include <iostream>
#include <string>
#include <vector>

// si vous en avez besoin
#include <map>
#include <set>

//#include "noeud.h"

using namespace std;

/***********************************************************
Code pour la partie 2
***********************************************************/

// Représente un individu de la population.
struct Personne {
  int id;
  string province;
  string ville;

  Personne() : Personne(0, "", "") {}

  Personne(int id, string province, string ville) {
    this->id = id;
    this->province = province;
    this->ville = ville;
  }
};

void afficher_populations(vector<Personne> &personnes) {


  map<pair<string, string>, int> population_par_ville;
  set<int> ids_uniques;

  for (const auto &personne : personnes) {
    if (!ids_uniques.insert(personne.id).second) {
      cout << "ERREUR : il y a un identifiant répété." << endl;
      return;
    }
    pair<string, string> cle = {personne.province, personne.ville};
    population_par_ville[cle]++;
  }

  for (const auto &[cle, population] : population_par_ville) {
    cout << cle.first << ", " << cle.second << " : " << population << endl;
  }
}

/***********************************************************
Code pour les tests de la Partie 1 et 2
***********************************************************/

/**
Fait le parcours à partir du noeud n avec l'itérateur.
**/


/**
Fait le parcours à partir du noeud n avec l'itérateur, à l'envers.
**/



int main() {


  /**********************************
  Tests partie 2
  ***********************************/
  vector<Personne> v;

  v.push_back(Personne(1, "Quebec", "Sherbrooke"));
  v.push_back(Personne(2, "Ontario", "Windsor"));
  v.push_back(Personne(3, "Quebec", "Sherbrooke"));
  v.push_back(Personne(4, "Quebec", "Windsor"));
  v.push_back(Personne(5, "Alberta", "Calgary"));
  v.push_back(Personne(6, "Ontario", "Windsor"));
  v.push_back(Personne(7, "Quebec", "Sherbrooke"));

  cout << endl << endl << "Tests partie 2" << endl;

  afficher_populations(v);

  cout << endl << "Tests duplicat" << endl;
  v.push_back(Personne(3, "Saskatchewan", "Saskatoon"));

  afficher_populations(v);

  return 0;
}
