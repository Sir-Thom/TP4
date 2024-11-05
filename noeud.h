#ifndef TP4_NOEUD_H
#define TP4_NOEUD_H

#include <vector>
#include <iostream>



template <typename TYPE>
class Noeud{
private:
    TYPE valeur;                            //valeur associée au Noeud
    Noeud* parent;                       //parent du Noeud, possiblement nullptr
    std::vector<Noeud*> enfants;              //liste des enfants du Noeud
    
	//Vous pouvez ajouter des fonctions privées, au besoin - mais PAS de fonctions publiques ni de variable membre

public:

    class iterator;
	friend class Noeud::iterator;				//pour que l'itérateur ait accès à la section privée de Noeud

    Noeud(const TYPE& valeur);                     // constructeur principal prenant la valeur associée au Noeud
    Noeud(const Noeud& source);                 // constructeur par copie
    ~Noeud();                                   // destructeur

    Noeud& operator=(const Noeud& source);      // affectateur (copie de la source)


    TYPE& val();                           		// retourne une référence MODIFIABLE vers la valeur associée au Noeud.
    Noeud* get_enfant(size_t i);				// retourne le i-ème enfant (le premier est indicé à 0)
    size_t get_nb_enfants() const;				// retourne le nombre d'enfants du Noeud
    Noeud* ajouter_enfant(const TYPE& val);		// créé un enfant ajouté à la fin de la liste d'enfants, et le retourne
    
    void supprimer_enfant(size_t i);            //supprime tout le sous-arbre enraciné en le i-ème enfant.  

    iterator begin();                            // retourne un itérateur postordre sur l'arbre
    iterator end();                              // retourne l'itérateur pointant sur la fin (et la fin n'est PAS un élément)

    void afficher_postordre() const;             // fait un parcours postordre RÉCURSIF en affichant les valeurs dans l'ordre.  Pour tester.

    
};


//Déclaration de la classe itérateur.
template <typename TYPE>
class Noeud<TYPE>::iterator{
private:
    
    // À implémenter
    // À vous de choisir une représentation de l'itérateur à l'aide de variables membres
    // Je recommande de maintenir au moins 3 variables: 
    // le noeud qui a initié l'itération, le noeud courant, un bool qui dit si on est à end ou pas.

public:
    
	// À ajouter: constructeurs, destructeur, constructeur par copie (seulement si vous en avez besoin)
	
    iterator& operator++();                       // incrémente l'itérateur.  
    iterator operator++(int i);                  // incrémente l'itérateur.  Le paramètre i est inutile.
    iterator& operator--();                       // décrémente l'itérateur.  
	iterator operator--(int i);                  // décrémente l'itérateur.  Le paramètre i est inutile.
    
    TYPE& operator*();                           // retourne la valeur associée au Noeud pointé par l'itérateur
    bool operator==(const Noeud::iterator& it);  // vérifie si l'itérateur est égal à it
    bool operator!=(const Noeud::iterator& it);  // vérifie si l'itérateur est différent de it
};








/********************************************************
Implémentation de la classe Noeud
********************************************************/


/**
 * Constructeur principal de Noeud.  val est la valeur associée au Noeud
 * À la construction, le parent est nullptr.
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
        delete enfants[i];  //entraîne une chaine de suppression chez les descendants
    }
    //question de réflexion: pourquoi on ne delete pas this?  Comment la racine va-t-elle se supprimer?
}



/**
 * Ajoute un enfant à la fin de la liste d'enfants, et le retourne.
 * val est la valeur associée au nouveau Noeud.
 * Le parent du nouveau Noeud est affecté au Noeud courant.
 */
template <typename TYPE>
Noeud<TYPE>* Noeud<TYPE>::ajouter_enfant(const TYPE& valeur){
    Noeud* n = new Noeud(valeur);
    n->parent = this;
    this->enfants.push_back(n);
    return n;
}




/**
 * Retourne une référence sur la valeur associée au Noeud.  On peut ensuite modifier val.
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
 * Retourne le i-ème enfant (le premier est indicé à 0).
 * C'est du C++, donc on ne fait aucune vérification.
 */
template <typename TYPE>
Noeud<TYPE>* Noeud<TYPE>::get_enfant(size_t i){
    return enfants[i];
}



/**
Supprime tout le sous - arbre enraciné en le i - ème enfant.
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
 * Retourne le début un itérateur postordre sur l'arbre.
 * Le début devrait donc pointer sur le Noeud le plus "à gauche".
 */
template <typename TYPE>
typename Noeud<TYPE>::iterator Noeud<TYPE>::begin(){
    //À implémenter
}

/**
 * Retourne un itérateur représentant la fin de l'arbre.
 * La fin n'est pas la même chose que le dernier élément.
 */
template <typename TYPE>
typename Noeud<TYPE>::iterator Noeud<TYPE>::end(){
    //À implémenter
}









/********************************************************
Implémentation de la classe Noeud::iterator
********************************************************/



/*
À ajouter: implémentation des fonctions de l'itérateur
Puisque iterator est une classe imbriquée, votre compilateur peut avoir du mal à identifier les noms de classe 
Le mieux est d'en spécifier un maximum, par exemple pour le ++:
template <typename TYPE>
typename Noeud<TYPE>::iterator Noeud<TYPE>::iterator::operator++(int i)
*/

#endif //TP4_NOEUD_H
