#include <stdio.h>
#include <stdlib.h>

// Décrit un noeud d'une liste chaînée de 'float'.
typedef struct node
{
    float data;
    struct node *next;
} node;

// Renvoie la longueur d'une liste chaînée.
int length(node const *list)
{
    // On fait avancer le pointeur 'list' au noeud suivant autant de fois que 
    // nécéssaire pour arriver à la find de la liste. On compte combien de fois 
    // on a fait avancer le pointeur.
    int steps;
    for(steps = 0; list != NULL; list = list->next)
    {}

    return steps;
}

// Renvoie un pointeur vers le 'index'ième noeud dans une liste.
// Si 'index' est plus grand que la longueur de 'list', renvoie 'NULL'. 
node* at(node *list, int index)
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
void set(node *list, int index, float const data)
{
    at(list, index)->data = data;
}

// Insère juste après le 'index'ième noeud un nouveau noeud avec la valeur donnée.
// Renvoie le pointeur 'list'.
// Si 'index' est plus grand que la longueur de 'list', 'list' reste inchangée.
node* insert(node *list, int index, float const data)
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
node* erase(node* list, int index)
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
node* split(node** list, int const index)
{
    node *split_point = at(*list, index);
    node *second_list = split_point->next;
    split_point->next = NULL;

    return second_list;
}

// Libère la mémoire allouée pour tout les noeuds d'une liste.
void clear(node *list)
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

int main()
{
    // Pour chaque test qui échoue, cette variable sera incrémentée de 1.
    // Le but est de la garder à 0.
    int failed = 0;

// Macro qui sert de test. Execute le test, affiche le résultat et incrémente 
// 'failed' si échec.
#define TEST(x) if(x)                       \
                {                           \
                    printf("[SUCCES] : ");  \
                }                           \
                else                        \
                {                           \
                    printf("[ECHEC]  : ");  \
                    failed += 1;            \
                }                           \
                printf("%s\n", #x);

    // Trois listes pour les premiers tests :
    //  1. Une liste vide : {NULL}.
    //  2. Une liste ne contenant qu'un seul noeud : {22.->NULL}.
    //  3. Une liste de cinq noeuds : {10.->20.->30.->40.->50.->NULL}.

    node *const empty = NULL;

    node *const one_node = malloc(sizeof(node));
    one_node->data = 22.;
    one_node->next = NULL;

    node *five_nodes, **init = &five_nodes;
    for(int i = 1; i < 6; ++i)
    {
        (*init) = malloc(sizeof(node));
        (*init)->data = i * 10.;
        (*init)->next = NULL;
        init = &((*init)->next);
    }

    // Tests de la fonction 'length()'.
    {
        TEST((length(empty) == 0));
        TEST((length(one_node) == 1));
        TEST((length(five_nodes) == 5));

        // Tests moins évidents mais tout aussi valides.
        TEST((length(one_node->next) == 0));
        TEST((length(five_nodes->next) == 4));
    }

    // Tests de la fonction 'at()'.
    {
        TEST((at(empty, 0) == NULL));
        TEST((at(empty, 1) == NULL));

        TEST((at(one_node, 0)->data == 22.));
        TEST((at(one_node, 0)->next == NULL));
        TEST((at(one_node, 1) == NULL));
        TEST((at(one_node->next, 0) == NULL));
        TEST((at(one_node->next, 1) == NULL));

        TEST((at(five_nodes, 0)->data == 10.));
        TEST((at(five_nodes, 1)->data == 20.));
        TEST((at(five_nodes, 4)->data == 50.));

        // Tests moins évidents mais tout aussi valides.
        TEST((at(one_node, 100) == NULL));
        TEST((at(five_nodes->next, 0)->data == 20.));
        TEST((at(five_nodes->next->next, 0)->data == 30.));
        TEST((at(five_nodes->next->next, 1)->data == 40.));
        TEST((at(five_nodes->next->next, 2)->data == 50.));
    }

    // Tests de la fonction 'set()'.
    {
        // Ne devrais avoir aucun effet.
        set(empty, 0, 1.);
        TEST((at(empty, 0) == NULL));

        // Modifie la valeur du seul noeud.
        set(one_node, 0, 33.);
        TEST((at(one_node, 0)->data == 22.));
        TEST((at(one_node, 1) == NULL));

        // Double la valeur de tout les noeuds.
        for(int i = 0; i != length(five_nodes); ++i)
        {
            float const data = at(five_nodes, i)->data;
            set(five_nodes, i, data * 2);
        }

        TEST((at(five_nodes, 0)->data == 20.));
        TEST((at(five_nodes, 1)->data == 40.));
        TEST((at(five_nodes, 2)->data == 60.));
        TEST((at(five_nodes, 3)->data == 80.));
        TEST((at(five_nodes, 4)->data == 100.));
    }

    // Libération de la mémoire allouée pour les listes.
    // Pas testé formellement avec le macro mais, à tout le moins, ne devrait 
    // pas planter le programme.
    {
        clear(empty);
        clear(one_node);
        clear(five_nodes);
    }

    // Tests de la fonction 'insert()'.
    {
        // Création d'une toute nouvelle liste, vide.
        node *tested = NULL;
        node *p;
        
        // Insertion dans une liste vide à un index hors-borne.
        p = insert(tested, 3, -1.);
        TEST((p == NULL));

        // Insertion dans une liste vide à l'index 0.
        p = insert(tested, 0, -1.);
        TEST((p->data == -1.));
        TEST((p->next == NULL));

        // Insertion dans une liste non-vide à l'index 0.
        p = insert(p, 0, -2.);
        TEST((p->data == -2.));
        TEST((p->next->data == -1.));
        TEST((p->next->next == NULL));

        // Insertion dans une liste non-vide à l'index 1.
        p = insert(p, 1, -1.5);
        TEST((p->data == -2.));
        TEST((p->next->data == -1.5));
        TEST((p->next->next->data == -1.));
        TEST((p->next->next->next == NULL));
        
        // Insertion dans une list non-vide à la toute fin.
        p = insert(p, length(p), -0.5);
        TEST((at(p, length(p) - 1)->data == -0.5));

        // Insertion dans une liste non-vide à un index hors-borne.
        TEST((insert(p, 99, 1.) == NULL));

        clear(p);
    }

    // Tests de la fonction 'erase()'.
    {
        // 'erase()' sur une liste vide devrait donner 'NULL'.
        TEST((erase(NULL, 0) == NULL));

        // Création d'une nouvelle liste de cinq noeuds pour ce 
        // test : {100.->200.->300.->400.->500.->NULL}.
        node *tested, **init = &tested;
        for(int i = 1; i < 6; ++i)
        {
            (*init) = malloc(sizeof(node));
            (*init)->data = i * 100.;
            (*init)->next = NULL;
            init = &((*init)->next);
        }

        node *p;

        // Supression du premier noeud d'une liste non-vide.
        p = erase(tested, 0);
        TEST((p->data == 200.));

        // Supression du dernier noeud d'une liste non-vide.
        p = erase(p, length(p) - 1);
        TEST(length(p) == 3);
        TEST((p->data == 200.));
        TEST((p->next->data == 300.));
        TEST((p->next->next->data == 400.));
        TEST((p->next->next->next == NULL));

        // Supression deuxième noeud d'une liste non-vide.
        p = erase(p, 1);
        TEST(length(p) == 2);
        TEST((p->data == 200.));
        TEST((p->next->data == 400.));
        TEST((p->next->next->next == NULL));

        // Supression dans une liste non-vide avec un index hors-borne.
        p = erase(p, 99);
        TEST(length(p) == 2);
        TEST((p->data == 200.));
        TEST((p->next->data == 400.));
        TEST((p->next->next->next == NULL));

        clear(p);
    }

    // Tests pour la fonction 'split()'.
    {
        // Division d'une liste vide devrait renvoyer 'NULL'.
        node *empty = NULL;
        TEST((split(&empty, 0) == NULL));

        // Création d'une nouvelle liste de cinq noeuds pour ce 
        // test : {100.->200.->300.->400.->500.->NULL}.
        node *tested, **init = &tested;
        for(int i = 1; i < 6; ++i)
        {
            (*init) = malloc(sizeof(node));
            (*init)->data = i * 100.;
            (*init)->next = NULL;
            init = &((*init)->next);
        }

        // Division d'une liste non-vide au premier noeud.
        node *tail = split(&tested, 1);
        TEST((length(tested) == 1));
        TEST((tested->data == 100.));
        TEST((tested->next == NULL));
        
        TEST((length(tail) == 4));
        TEST((tail->data == 200.));

        clear(tested);

        // Division d'une liste non-vide au dernier noeud.
        node *last = split(&tail, length(tail) - 1);
        TEST((length(tail) == 3));
        TEST((tested->data == 200.));

        TEST((length(last) == 1));
        TEST((last->data == 500.));
        TEST((last->next == NULL));
    }

    return failed;
}
