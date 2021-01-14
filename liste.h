#pragma once

// Décrit un noeud d'une liste chaînée de 'float'.
typedef struct node
{
    float data;
    struct node *next;
} node;

// Renvoie la longueur d'une liste chaînée.
int length(
    node const *list);

// Renvoie un pointeur vers le 'index'ième noeud dans une liste.
// Si 'index' est plus grand que la longueur de 'list', renvoie 'NULL'. 
node* at(
    node *list,
    int index);

// Affecte au 'index'ième noeud la valeur donnée.
// Si 'index' est plus grand que la longueur de 'list', 'list' reste inchangée.
void set(
    node *list,
    int index,
    float const data);

// Insère juste après le 'index'ième noeud un nouveau noeud avec la valeur donnée.
// Renvoie le pointeur 'list'.
// Si 'index' est plus grand que la longueur de 'list', 'list' reste inchangée.
node* insert(
    node *list,
    int index,
    float const data);

// Efface le 'index'ième noeud.
// Renvoie un pointeur vers le début de la liste.
// Si 'index' est plus grand que la longueur de 'list', 'list' reste inchangée.
node* erase(
    node* list,
    int index);

// Sépare une liste en deux listes distinctes à l'index donné.
// Le première des deux listes se termine à l'index donné et la deuxième liste 
// y débute.
// Renvoie un pointeur vers la deuxième liste crée.
// Si 'index' est plus grand que la longueur de 'list', renvoie 'NULL' et 'list' 
// reste inchangée.
node* split(
    node** list,
    int const index);

// Libère la mémoire allouée pour tout les noeuds d'une liste.
void clear(
    node *list);
