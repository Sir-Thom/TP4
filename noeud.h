#ifndef TP4_NOEUD_H
#define TP4_NOEUD_H

#include <algorithm>
#include <iostream>
#include <vector>

template <typename TYPE> class Noeud {
private:
  TYPE valeur;                  // valeur associée au Noeud
  Noeud *parent;                // parent du Noeud, possiblement nullptr
  std::vector<Noeud *> enfants; // liste des enfants du Noeud

  // Vous pouvez ajouter des fonctions privées, au besoin - mais PAS de
  // fonctions publiques ni de variable membre

public:
  class iterator;
  friend class Noeud::iterator; // pour que l'itérateur ait accès à la section
                                // privée de Noeud

  Noeud(const TYPE &valeur);  // constructeur principal prenant la valeur
                              // associée au Noeud
  Noeud(const Noeud &source); // constructeur par copie
  ~Noeud();                   // destructeur

  Noeud &operator=(const Noeud &source); // affectateur (copie de la source)

  TYPE &
  val(); // retourne une référence MODIFIABLE vers la valeur associée au Noeud.
  Noeud *
  get_enfant(size_t i); // retourne le i-ème enfant (le premier est indicé à 0)
  size_t get_nb_enfants() const; // retourne le nombre d'enfants du Noeud
  Noeud *ajouter_enfant(const TYPE &val); // créé un enfant ajouté à la fin de
                                          // la liste d'enfants, et le retourne

  void supprimer_enfant(
      size_t i); // supprime tout le sous-arbre enraciné en le i-ème enfant.

  iterator begin(); // retourne un itérateur postordre sur l'arbre
  iterator end();   // retourne l'itérateur pointant sur la fin (et la fin n'est
                    // PAS un élément)

  void afficher_postordre()
      const; // fait un parcours postordre RÉCURSIF en affichant les valeurs
             // dans l'ordre.  Pour tester.
};

// Déclaration de la classe itérateur.
template <typename TYPE> class Noeud<TYPE>::iterator {
private:
  Noeud<TYPE> *current;
  Noeud<TYPE> *root;
  bool is_end;
  // À implémenter
  // À vous de choisir une représentation de l'itérateur à l'aide de variables
  // membres Je recommande de maintenir au moins 3 variables: le noeud qui a
  // initié l'itération, le noeud courant, un bool qui dit si on est à end ou
  // pas.

   Noeud<TYPE> *findLastNode(Noeud<TYPE> *node) {
   if (!node){
    this->is_end = true;
     return nullptr;
   } 
   
    while (!node->enfants.empty()) {
        node = node->enfants.back();  
    }
    return node;
  }
Noeud<TYPE>* findParent(Noeud<TYPE>* root, Noeud<TYPE>* node) {
    if (!root || !node) return nullptr;

    // Recherche dans l'arbre pour trouver le parent
    for (auto& enfant : root->enfants) {
        if (enfant == node) {
            return root;  // Le parent est trouvé
        }
        Noeud<TYPE>* parent = findParent(enfant, node);
        if (parent) return parent;  // Le parent a été trouvé dans l'un des sous-arbres
    }

    return nullptr;  // Aucun parent trouvé
}


Noeud<TYPE>* findPrevNode(Noeud<TYPE>* node) {
  

    if (!node) return nullptr;

    // Si le nœud a des enfants, remonter au dernier enfant exploré
    if (!node->enfants.empty()) {
        return node->enfants[current->enfants.size() - 1];
    }

    // Sinon, remonter au parent
    Noeud<TYPE>* parent = findParent(root, current);
    while (parent && parent->enfants[0] == current) {
        // Remonter jusqu'à ce que le parent n'ait pas encore visité cet enfant
        current = parent;
        parent = findParent(root, current);
    }

    return parent;
}

  
  // Trouve le nœud suivant dans le parcours post-ordre
  Noeud<TYPE> *findNextNode(Noeud<TYPE> *node) {
    if (!node || !node->parent) return nullptr;

    auto &siblings = node->parent->enfants;
    auto it = std::find(siblings.begin(), siblings.end(), node);
    if (it == siblings.end()) return nullptr;

    if (++it != siblings.end()) {
      node = *it;
      while (!node->enfants.empty()) {
        node = node->enfants[0];
      }
      return node;
    }

    return node->parent;
  }

public:
  // À ajouter: constructeurs, destructeur, constructeur par copie (seulement si
iterator(Noeud<TYPE> *start)
    : root(start), current(start), is_end(false) {
    // Descente vers le nœud le plus à gauche (le plus profond)
    if (current) {
        while (!current->enfants.empty()) {
            current = current->enfants[0];  // Aller au premier enfant
        }
    } else {
        is_end = true;  // Si l'arbre est vide, on est à la fin
    }
};

    
    iterator(Noeud<TYPE> * racine, bool est_end);
    iterator &operator++(); // incrémente l'itérateur.
    iterator operator++(
        int i); // incrémente l'itérateur.  Le paramètre i est inutile.
    iterator &operator--(); // décrémente l'itérateur.
    iterator operator--(
        int i); // décrémente l'itérateur.  Le paramètre i est inutile.

    TYPE &
    operator*(); // retourne la valeur associée au Noeud pointé par l'itérateur
    bool operator==(
        const Noeud::iterator &it); // vérifie si l'itérateur est égal à it
    bool operator!=(const Noeud::iterator
                        &it); // vérifie si l'itérateur est différent de it
  };

  /********************************************************
  Implémentation de la classe Noeud
  ********************************************************/

  /**
   * Constructeur principal de Noeud.  val est la valeur associée au Noeud
   * À la construction, le parent est nullptr.
   */
  template <typename TYPE> Noeud<TYPE>::Noeud(const TYPE &valeur) {
    this->valeur = valeur;
    this->parent = nullptr;
  }

  /**
   * Constructeur par copie.  On doit copier toute la structure.
   */
  template <typename TYPE> Noeud<TYPE>::Noeud(const Noeud &source) {
    *this = source;
  }

  /**
  Affectateur =.  this devient une copie de source.
  **/
  template <typename TYPE>
  Noeud<TYPE> &Noeud<TYPE>::operator=(const Noeud &source) {
    if (this == &source)
      return *this;

    this->valeur = source.valeur;
    for (size_t i = 0; i < source.get_nb_enfants(); i++) {
      Noeud *enfant = new Noeud(*(source.enfants[i]));
      enfant->parent = this;
      this->enfants.push_back(enfant);
    }

    return *this;
  }

  /**
   * Destructeur.  Chaque est responsable de supprimer ses enfants.
   */
  template <typename TYPE> Noeud<TYPE>::~Noeud() {
    for (size_t i = 0; i < enfants.size(); i++) {
      delete enfants[i]; // entraîne une chaine de suppression chez les
                         // descendants
    }
    // question de réflexion: pourquoi on ne delete pas this?  Comment la racine
    // va-t-elle se supprimer?
  }

  /**
   * Ajoute un enfant à la fin de la liste d'enfants, et le retourne.
   * val est la valeur associée au nouveau Noeud.
   * Le parent du nouveau Noeud est affecté au Noeud courant.
   */
  template <typename TYPE>
  Noeud<TYPE> *Noeud<TYPE>::ajouter_enfant(const TYPE &valeur) {
    Noeud *n = new Noeud(valeur);
    n->parent = this;
    this->enfants.push_back(n);
    return n;
  }

  /**
   * Retourne une référence sur la valeur associée au Noeud.  On peut ensuite
   * modifier val.
   */
  template <typename TYPE> TYPE &Noeud<TYPE>::val() { return valeur; }

  /**
   * Retourne le nombre d'enfants du Noeud.
   */
  template <typename TYPE> size_t Noeud<TYPE>::get_nb_enfants() const {
    return enfants.size();
  }

  /**
   * Retourne le i-ème enfant (le premier est indicé à 0).
   * C'est du C++, donc on ne fait aucune vérification.
   */
  template <typename TYPE> Noeud<TYPE> *Noeud<TYPE>::get_enfant(size_t i) {
    return enfants[i];
  }

  /**
  Supprime tout le sous - arbre enraciné en le i - ème enfant.
  */
  template <typename TYPE> void Noeud<TYPE>::supprimer_enfant(size_t i) {

    delete enfants[i];
    enfants.erase(enfants.begin() + i);
  }

  template <typename TYPE> void Noeud<TYPE>::afficher_postordre() const {
    for (size_t i = 0; i < enfants.size(); i++) {
      enfants[i]->afficher_postordre();
    }

    std::cout << valeur << " ";
  }

  /**
   * Retourne le début un itérateur postordre sur l'arbre.
   * Le début devrait donc pointer sur le Noeud le plus "à gauche".
   */template <typename TYPE>
typename Noeud<TYPE>::iterator Noeud<TYPE>::begin() {
  // Trouver le premier élément de l'arbre
  if (!enfants.empty()) {
    return iterator(this);
  } else {
    // Si l'arbre est vide, retourner un itérateur en état "fin"
    return iterator(this, true);
  }
}
  

  /**
   * Retourne un itérateur représentant la fin de l'arbre.
   * La fin n'est pas la même chose que le dernier élément.
   */
  template <typename TYPE> typename Noeud<TYPE>::iterator Noeud<TYPE>::end() {
    // À implémenter
    
    return iterator(nullptr, true);
  }

  /********************************************************
  Implémentation de la classe Noeud::iterator
  ********************************************************/

  /*
  À ajouter: implémentation des fonctions de l'itérateur
  Puisque iterator est une classe imbriquée, votre compilateur peut avoir du mal
  à identifier les noms de classe Le mieux est d'en spécifier un maximum, par
  exemple pour le ++: template <typename TYPE> typename Noeud<TYPE>::iterator
  Noeud<TYPE>::iterator::operator++(int i)
  */

  /*Fait passer l’itérateur au prochain noeud à visiter dans le parcours
  postordre. L’état interne de l’itérateur doit être modifié. Vous devez avoir
  l’incrémentation pré-fixe et l’incrémentation post-fixe. Le comportement de
  monnoeud->end()++ n’est pas défini.*/
  template <typename TYPE>
Noeud<TYPE>::iterator::iterator(Noeud<TYPE>* start, bool is_end)
    : root(start), current(nullptr), is_end(is_end) {
    if (is_end) {
        current = findLastNode(root);
    } else {
        current = start;
        while (!current->enfants.empty()) {
            current = current->enfants[0];
        }
    }
}


  template <typename TYPE>
  typename Noeud<TYPE>::iterator &Noeud<TYPE>::iterator::operator++() {
    

        if (is_end)
        return *this;

    if (current == nullptr) {
        is_end = true;
        return *this;
    }

    current = findNextNode(current);

    if (current == nullptr) {
        is_end = true;
    }

    return *this;
  }

  template <typename TYPE>
  typename Noeud<TYPE>::iterator Noeud<TYPE>::iterator::operator++(int i) {
    iterator tmp(*this);
    ++(*this);
    return tmp;
  }
template <typename TYPE>
typename Noeud<TYPE>::iterator& Noeud<TYPE>::iterator::operator--() {
    if (is_end) {
        current = findLastNode(root);
        is_end = false;
    } else {
        current = findPrevNode(current);
        if (current == nullptr) {
            is_end = true;
        }
    }
    return *this;

}





  template <typename TYPE>
  typename Noeud<TYPE>::iterator Noeud<TYPE>::iterator::operator--(int i) {
    iterator tmp(*this);
    --(*this);
    return tmp;
  }

  template <typename TYPE>
  bool Noeud<TYPE>::iterator::operator==(const Noeud<TYPE>::iterator &it) {
    if (is_end && it.is_end)
      return true;
    if (is_end || it.is_end)
      return false;
    return current == it.current && root == it.root;
  }

  template <typename TYPE>
  bool Noeud<TYPE>::iterator::operator!=(const Noeud<TYPE>::iterator &it) {
    return !(*this == it);
  }
template <typename TYPE>
TYPE &Noeud<TYPE>::iterator::operator*() {
  if (is_end) {
    // Ne pas lancer d'exception si l'itérateur est en état "fin"
    return *(TYPE*)nullptr;
  } else if (current == nullptr) {
    throw std::out_of_range("L'itérateur est à la fin, aucune valeur à dereferencer");
  } else {
    return current->valeur;
  }
}

#endif // TP4_NOEUD_H
