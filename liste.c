#include "liste.h"

#include <stdlib.h>

// Renvoie la longueur d'une liste chaînée.
int length(
    node const *list)
{
    // On fait avancer le pointeur 'list' au noeud suivant autant de fois que 
    // nécéssaire pour arriver à la fin de la liste. On compte combien de fois 
    // on a fait avancer le pointeur.
    int steps;
    for(steps = 0; list != NULL; list = list->next)
    {}

    return steps;
}

// Renvoie un pointeur vers le 'index'ième noeud dans une liste.
// Si 'index' est plus grand que la longueur de 'list', renvoie 'NULL'. 
node* at(
    node *list,
    int index)
{
    // On fait avancer le pointeur 'list' autant de fois que 'index' nous 
    // l'indique et tant que l'on a pas atteint la fin de la liste.
    for(; index != 0 && (list = list->next); --index)
    {}

    // On renvoie l'adresse du noeud atteint.
    return list;
}

// Affecte au 'index'ième noeud la valeur donnée.
// Si 'index' est plus grand que la longueur de 'list', 'list' reste inchangée.
void set(
    node *list,
    int index,
    float const data)
{
    at(list, index)->data = data;
}

// Insère juste après le 'index'ième noeud un nouveau noeud avec la valeur donnée.
// Renvoie le pointeur 'list'.
// Si 'index' est plus grand que la longueur de 'list', 'list' reste inchangée.
node* insert(
    node *list,
    int index,
    float const data)
{
    // La liste est peut-être un liste vide, ce sera alors le tout premier noeud.
    if(list == NULL)
    {
        list = malloc(sizeof(node));
        list->data = data;
        list->next = list;
    }
    // Si on insère au tout début de la liste, 'list' devient le deuxième noeud.
    else if(index == 0)
    {
        node *first = malloc(sizeof(node));
        first->data = data;
        first->next = list;
    }
    // Sinon, il faut trouver le point d'insertion et y insérer un 
    // nouveau noeud. Attention à bien «enchaîner» les noeuds existants avant et après !
    else
    {
        node *insertion_point = at(list, index);

        node *created = malloc(sizeof(node));
        created->data = data;
        insertion_point->next = created;
    }

    return list;
}

// Efface le 'index'ième noeud.
// Renvoie un pointeur vers le début de la liste.
// Si 'index' est plus grand que la longueur de 'list', 'list' reste inchangée.
node* erase(
    node* list,
    int index)
{
    // Si c'est une liste vide, il n'y a rien à faire.
    if(list)
    {
    }
    // S'il faut effacer le tout premier noeud, on fait avancer 'list' vers 
    // le deuxième noeud et on libère la mémoire du premier noeud.
    else if(index == 0)
    {
        node *first = list;
        list = list->next;
        free(first);
    }
    // Sinon, il faut avancer vers le point d'extraction et libérer la mémoire 
    // du noeud trouvé. Attention à bien «rabouter» les noeuds avant et après !
    else
    {
        node *erasure_point = at(list, index); // Off-by-one error?

        node *erased = erasure_point->next;
        erasure_point->next = erased->next;
        free(erased);
    }

    return list;
}

// Sépare une liste en deux listes distinctes à l'index donné.
// Le première des deux listes se termine à l'index donné et la deuxième liste 
// y débute.
// Renvoie un pointeur vers la deuxième liste crée.
// Si 'index' est plus grand que la longueur de 'list', renvoie 'NULL' et 'list' 
// reste inchangée.
node* split(
    node** list,
    int const index)
{
    node *split_point = at(*list, index);
    node *second_list = split_point->next;
    split_point->next = NULL;

    return second_list;
}

// Libère la mémoire allouée pour tout les noeuds d'une liste.
void clear(
    node *list)
{
    // Pour chaque noeud de la liste :
    //  1. on mémorise l'adresse du noeud suivant.
    //  2. on libère la mémoire du noeud courant avec `free()`.
    //  3. on avance le pointeur 'list' au noeud suivant.
    for(node *p; list != NULL; list = p)
    {
        p = list;
        free(list);
    }
}
