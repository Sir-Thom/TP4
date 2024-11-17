#ifndef TP4_NOEUD_H
#define TP4_NOEUD_H

#include <vector>
#include <iostream>



template <typename TYPE>
class Noeud{
private:
    TYPE valeur;                            //valeur associÃ©e au Noeud
    Noeud* parent;                       //parent du Noeud, possiblement nullptr
    std::vector<Noeud*> enfants;              //liste des enfants du Noeud

	//Vous pouvez ajouter des fonctions privÃ©es, au besoin - mais PAS de fonctions publiques ni de variable membre

public:

    class iterator;
	friend class Noeud::iterator;				//pour que l'itÃ©rateur ait accÃ¨s Ã  la section privÃ©e de Noeud

    Noeud(const TYPE& valeur);                     // constructeur principal prenant la valeur associÃ©e au Noeud
    Noeud(const Noeud& source);                 // constructeur par copie
    ~Noeud();                                   // destructeur

    Noeud& operator=(const Noeud& source);      // affectateur (copie de la source)


    TYPE& val();                           		// retourne une rÃ©fÃ©rence MODIFIABLE vers la valeur associÃ©e au Noeud.
    Noeud* get_enfant(size_t i);				// retourne le i-Ã¨me enfant (le premier est indicÃ© Ã  0)
    size_t get_nb_enfants() const;				// retourne le nombre d'enfants du Noeud
    Noeud* ajouter_enfant(const TYPE& val);		// crÃ©Ã© un enfant ajoutÃ© Ã  la fin de la liste d'enfants, et le retourne

    void supprimer_enfant(size_t i);            //supprime tout le sous-arbre enracinÃ© en le i-Ã¨me enfant.

    iterator begin();                            // retourne un itÃ©rateur postordre sur l'arbre
    iterator end();                              // retourne l'itÃ©rateur pointant sur la fin (et la fin n'est PAS un Ã©lÃ©ment)

    void afficher_postordre() const;             // fait un parcours postordre RÃ‰CURSIF en affichant les valeurs dans l'ordre.  Pour tester.


};


//DÃ©claration de la classe itÃ©rateur.
template <typename TYPE>
class Noeud<TYPE>::iterator{
private:

    // Ã€ implÃ©menter
    // Ã€ vous de choisir une reprÃ©sentation de l'itÃ©rateur Ã  l'aide de variables membres
    // Je recommande de maintenir au moins 3 variables:
    // le noeud qui a initiÃ© l'itÃ©ration, le noeud courant, un bool qui dit si on est Ã  end ou pas.

public:

	// Ã€ ajouter: constructeurs, destructeur, constructeur par copie (seulement si vous en avez besoin)

    iterator& operator++();                       // incrÃ©mente l'itÃ©rateur.
    iterator operator++(int i);                  // incrÃ©mente l'itÃ©rateur.  Le paramÃ¨tre i est inutile.
    iterator& operator--();                       // dÃ©crÃ©mente l'itÃ©rateur.
	iterator operator--(int i);                  // dÃ©crÃ©mente l'itÃ©rateur.  Le paramÃ¨tre i est inutile.

    TYPE& operator*();                           // retourne la valeur associÃ©e au Noeud pointÃ© par l'itÃ©rateur
    bool operator==(const Noeud::iterator& it);  // vÃ©rifie si l'itÃ©rateur est Ã©gal Ã  it
    bool operator!=(const Noeud::iterator& it);  // vÃ©rifie si l'itÃ©rateur est diffÃ©rent de it
};








/********************************************************
ImplÃ©mentation de la classe Noeud
********************************************************/


/**
 * Constructeur principal de Noeud.  val est la valeur associÃ©e au Noeud
 * Ã€ la construction, le parent est nullptr.
 */
template <typename TYPE>
Noeud<TYPE>::Noeud(const TYPE& valeur){
    this->valeur = valeur;
    this->parent = nullptr;
}

/**
 * Constructeur par copie.  On doit copier toute la structure.
 */
template <typename TYPE>
Noeud<TYPE>::Noeud(const Noeud& source){
    *this = source;
}



/**
Affectateur =.  this devient une copie de source.
**/
template <typename TYPE>
Noeud<TYPE>& Noeud<TYPE>::operator=(const Noeud& source){
	if (this == &source)
		return *this;

	this->valeur = source.valeur;
    for (size_t i = 0; i < source.get_nb_enfants(); i++){
        Noeud* enfant = new Noeud(*(source.enfants[i]));
        enfant->parent = this;
        this->enfants.push_back(enfant);
    }

    return *this;
}



/**
 * Destructeur.  Chaque est responsable de supprimer ses enfants.
 */
template <typename TYPE>
Noeud<TYPE>::~Noeud(){
    for (size_t i = 0; i < enfants.size(); i++){
        delete enfants[i];  //entraÃ®ne une chaine de suppression chez les descendants
    }
    //question de rÃ©flexion: pourquoi on ne delete pas this?  Comment la racine va-t-elle se supprimer?
}



/**
 * Ajoute un enfant Ã  la fin de la liste d'enfants, et le retourne.
 * val est la valeur associÃ©e au nouveau Noeud.
 * Le parent du nouveau Noeud est affectÃ© au Noeud courant.
 */
template <typename TYPE>
Noeud<TYPE>* Noeud<TYPE>::ajouter_enfant(const TYPE& valeur){
    Noeud* n = new Noeud(valeur);
    n->parent = this;
    this->enfants.push_back(n);
    return n;
}




/**
 * Retourne une rÃ©fÃ©rence sur la valeur associÃ©e au Noeud.  On peut ensuite modifier val.
 */
template <typename TYPE>
TYPE& Noeud<TYPE>::val(){
    return valeur;
}






/**
 * Retourne le nombre d'enfants du Noeud.
 */
template <typename TYPE>
size_t Noeud<TYPE>::get_nb_enfants() const {
    return enfants.size();
}

/**
 * Retourne le i-Ã¨me enfant (le premier est indicÃ© Ã  0).
 * C'est du C++, donc on ne fait aucune vÃ©rification.
 */
template <typename TYPE>
Noeud<TYPE>* Noeud<TYPE>::get_enfant(size_t i){
    return enfants[i];
}



/**
Supprime tout le sous - arbre enracinÃ© en le i - Ã¨me enfant.
*/
template <typename TYPE>
void Noeud<TYPE>::supprimer_enfant(size_t i) {

    delete enfants[i];
    enfants.erase(enfants.begin() + i);
}



template <typename TYPE>
void Noeud<TYPE>::afficher_postordre() const {
    for (size_t i = 0; i < enfants.size(); i++){
        enfants[i]->afficher_postordre();
    }

    std::cout << valeur << " ";
}


/**
 * Retourne le dÃ©but un itÃ©rateur postordre sur l'arbre.
 * Le dÃ©but devrait donc pointer sur le Noeud le plus "Ã  gauche".
 */
template <typename TYPE>
typename Noeud<TYPE>::iterator Noeud<TYPE>::begin(){
    //Ã€ implÃ©menter
}

/**
 * Retourne un itÃ©rateur reprÃ©sentant la fin de l'arbre.
 * La fin n'est pas la mÃªme chose que le dernier Ã©lÃ©ment.
 */
template <typename TYPE>
typename Noeud<TYPE>::iterator Noeud<TYPE>::end(){
    //Ã€ implÃ©menter
}









/********************************************************
ImplÃ©mentation de la classe Noeud::iterator
********************************************************/



/*
Ã€ ajouter: implÃ©mentation des fonctions de l'itÃ©rateur
Puisque iterator est une classe imbriquÃ©e, votre compilateur peut avoir du mal Ã  identifier les noms de classe
Le mieux est d'en spÃ©cifier un maximum, par exemple pour le ++:
template <typename TYPE>
typename Noeud<TYPE>::iterator Noeud<TYPE>::iterator::operator++(int i)
*/

#endif //TP4_NOEUD_H