#include <iostream>
#include <string>
#include <vector>

// si vous en avez besoin
#include <map>
#include <set>

#include "noeud.h"

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

  // à implémenter
}

/***********************************************************
Code pour les tests de la Partie 1 et 2
***********************************************************/

/**
Fait le parcours à partir du noeud n avec l'itérateur.
**/
void iterer(Noeud<int> *n) {
  for (Noeud<int>::iterator it = n->begin(); it != n->end(); ++it) {
    cout << (*it) << " ";
  }
  cout << endl;
}
void test_iterator(Noeud<int> &arbre) {
  auto it = arbre.begin();
  std::cout << "Parcours avant:" << std::endl;
  while (it != arbre.end()) {
    std::cout << *it << " ";
    ++it;
  }

  std::cout << "\nParcours inverse:" << std::endl;
  --it; // revenir au dernier élément
  while (true) {
    std::cout << *it << " ";
    if (it == arbre.begin()) break;
    --it;
  }
}
/**
Fait le parcours à partir du noeud n avec l'itérateur, à l'envers.
**/
void iterer_rev(Noeud<int> *n) {
  Noeud<int>::iterator itrev = n->end();
  itrev--;
  while (itrev != n->begin()) {
    cout << (*itrev) << " ";
    itrev--;
  }
  cout << (*itrev); // pour ne pas manquer le begin()
  cout << endl;
}
void testIterationInverse() {
  Noeud<int> *racine = new Noeud<int>(1);
  Noeud<int> *n3 = racine->ajouter_enfant(3);
  Noeud<int> *n2 = racine->ajouter_enfant(2);


  Noeud<int>::iterator it = racine->end();
  --it; // décrémente l'itérateur pour pointer vers le dernier élément
  while (it != racine->begin()) {
    std::cout << *it << std::endl;
    --it; // décrémente l'itérateur pour pointer vers l'élément précédent
  }
  std::cout << *it << std::endl; // affiche le premier élément
}
void teste_iterator(Noeud<int> &arbre) {
  auto it = arbre.begin();
  std::cout << "Parcours avant:" << std::endl;
  while (it != arbre.end()) {
    std::cout << *it << " ";
    ++it;
  }

  std::cout << "\nParcours inverse:" << std::endl;
  --it; // revenir au dernier élément
  while (true) {
    std::cout << *it << " ";
    if (it == arbre.begin()) break;
    --it;
  }
}

int main() {
  //testIterationInverse();
  // ici on construit l'arbre en exemple
  Noeud<int> *racine = new Noeud<int>(13);
  Noeud<int> *n3 = racine->ajouter_enfant(3);
  Noeud<int> *n12 = racine->ajouter_enfant(12);

  n3->ajouter_enfant(1);
  n3->ajouter_enfant(2);

  n12->ajouter_enfant(4);
  n12->ajouter_enfant(5);
  n12->ajouter_enfant(7)->ajouter_enfant(6); // oui ceci fonctionne
  n12->ajouter_enfant(8);
  Noeud<int> *n11 = n12->ajouter_enfant(11);
  n11->ajouter_enfant(9);
  n11->ajouter_enfant(10);

  cout << "Sortie avec afficher_postordre():" << endl;
  racine->afficher_postordre();
  cout << endl;

  cout << "Test 1: iteration simple." << endl;
  iterer(racine);

  cout << "Test 2: iteration inverse." << endl;
  cout << "Root node: " << racine->val() << endl;
  iterer_rev(racine);
 // cout << "Test 2.5: custom" << endl;
 // teste_iterator(*racine );
  cout << "Test 3: iteration d'un sous-arbre." << endl;
  iterer(n12);

  cout << "Test 4: iteration inverse d'un sous-arbre." << endl;
  iterer_rev(n12);

  cout << "Test 5: un peu de va-et-vient." << endl;
  { // les accolades pour limiter la portee de it
    Noeud<int>::iterator it = racine->begin();
    it = ++(++it); // 3
    cout << (*it) << " ";
    it--;
    cout << (*it) << " "; // 2
    ++ ++ ++it;           // 5
    cout << (*it) << " ";
    -- --it; // 3
    cout << (*it) << " ";
    ++ ++ ++ ++it;
    ++--++-- --it; // 6
    cout << (*it) << " ";
    it++;
    it++;
    it++;
    it++;
    it++;
    it++;
    it++;
    it--;
    it--;
    it++;
    it++;
    it++;
    cout << (it == racine->end() ? "fin" : "non-fin") << " ";

    cout << endl;
  }

  // pour tester la suppression pendant une itération
  cout << "Test 6: test avec suppression." << endl;
  Noeud<int> *rcopie = new Noeud<int>(*racine);
  auto it = rcopie->begin();
  while (it != rcopie->end()) {
    cout << *it << " ";

    if (*it == 4) {
      rcopie->get_enfant(1)->supprimer_enfant(1);
      rcopie->get_enfant(1)->supprimer_enfant(1);
    }
    it++;
  }
  delete rcopie;

  delete racine;

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
