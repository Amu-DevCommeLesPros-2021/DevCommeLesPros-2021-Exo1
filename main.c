#include "liste.h"
#include "test_harness/test_harness.h"

#include <stdlib.h>

// Valeurs pour le harnais de test spécifiques à ce programme.
int const tests_total = 66;
int const test_column_width = 40;

int main()
{
    // Trois listes pour les premiers tests :
    //  1. Une liste vide : {NULL}.
    //  2. Une liste ne contenant qu'un seul noeud : {22.0->NULL}.
    //  3. Une liste de cinq noeuds : {10.0->20.0->30.0->40.0->50.0->NULL}.

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
        TEST(length(empty) == 0);
        TEST(length(one_node) == 1);
        TEST(length(five_nodes) == 5);

        // Tests moins évidents mais tout aussi valides.
        TEST(length(one_node->next) == 0);
        TEST(length(five_nodes->next) == 4);
    }

    // Tests de la fonction 'at()'.
    {
        TEST(at(empty, 0) == NULL);
        TEST(at(empty, 1) == NULL);

        TEST(at(one_node, 0)->data == 22.);
        TEST(at(one_node, 0)->next == NULL);
        TEST(at(one_node, 1) == NULL);
        TEST(at(one_node->next, 0) == NULL);
        TEST(at(one_node->next, 1) == NULL);

        TEST(at(five_nodes, 0)->data == 10.);
        TEST(at(five_nodes, 1)->data == 20.);
        TEST(at(five_nodes, 4)->data == 50.);

        // Tests moins évidents mais tout aussi valides.
        TEST(at(one_node, 100) == NULL);
        TEST(at(five_nodes->next, 0)->data == 20.);
        TEST(at(five_nodes->next->next, 0)->data == 30.);
        TEST(at(five_nodes->next->next, 1)->data == 40.);
        TEST(at(five_nodes->next->next, 2)->data == 50.);
    }

    // Tests de la fonction 'set()'.
    {
        // Ne devrais avoir aucun effet.
        set(empty, 0, 1.);
        TEST(at(empty, 0) == NULL);

        // Modifie la valeur du seul noeud.
        set(one_node, 0, 33.);
        TEST(at(one_node, 0)->data == 33.);
        TEST(at(one_node, 1) == NULL);

        // Double la valeur de tout les noeuds.
        for(int i = 0; i != length(five_nodes); ++i)
        {
            float const data = at(five_nodes, i)->data;
            set(five_nodes, i, data * 2);
        }

        TEST(at(five_nodes, 0)->data == 20.);
        TEST(at(five_nodes, 1)->data == 40.);
        TEST(at(five_nodes, 2)->data == 60.);
        TEST(at(five_nodes, 3)->data == 80.);
        TEST(at(five_nodes, 4)->data == 100.);
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
        TEST(p == NULL);

        // Insertion dans une liste vide à l'index 0.
        p = insert(tested, 0, -1.);
        TEST(p->data == -1.);
        TEST(p->next == NULL);

        // Insertion dans une liste non-vide à l'index 0.
        p = insert(p, 0, -2.);
        TEST(p->data == -2.);
        TEST(p->next->data == -1.);
        TEST(p->next->next == NULL);

        // Insertion dans une liste non-vide à l'index 1.
        p = insert(p, 1, -1.5);
        TEST(p->data == -2.);
        TEST(p->next->data == -1.5);
        TEST(p->next->next->data == -1.);
        TEST(p->next->next->next == NULL);
        
        // Insertion dans une list non-vide à la toute fin.
        p = insert(p, length(p), -0.5);
        TEST(at(p, length(p) - 1)->data == -0.5);

        // Insertion dans une liste non-vide à un index hors-borne.
        p = insert(p, 99, 1.);
        TEST(at(p, length(p) - 1)->data == -0.5);

        clear(p);
    }

    // Tests de la fonction 'erase()'.
    {
        // 'erase()' sur une liste vide devrait donner 'NULL'.
        TEST(erase(NULL, 0) == NULL);

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
        TEST(p->data == 200.);

        // Supression du dernier noeud d'une liste non-vide.
        p = erase(p, length(p) - 1);
        TEST(length(p) == 3);
        TEST(p->data == 200.);
        TEST(p->next->data == 300.);
        TEST(p->next->next->data == 400.);
        TEST(p->next->next->next == NULL);

        // Supression deuxième noeud d'une liste non-vide.
        p = erase(p, 1);
        TEST(length(p) == 2);
        TEST(p->data == 200.);
        TEST(p->next->data == 400.);
        TEST(p->next->next == NULL);

        // Supression dans une liste non-vide avec un index hors-borne.
        p = erase(p, 99);
        TEST(length(p) == 2);
        TEST(p->data == 200.);
        TEST(p->next->data == 400.);
        TEST(p->next->next == NULL);

        clear(p);
    }

    // Tests pour la fonction 'split()'.
    {
        // Division d'une liste vide devrait renvoyer 'NULL'.
        node *empty = NULL;
        TEST(split(&empty, 0) == NULL);

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
        TEST(length(tested) == 1);
        TEST(tested->data == 100.);
        TEST(tested->next == NULL);
        
        TEST(length(tail) == 4);
        TEST(tail->data == 200.);

        clear(tested);

        // Division d'une liste non-vide au dernier noeud.
        node *last = split(&tail, length(tail) - 1);
        TEST(length(tail) == 3);
        TEST(tail->data == 200.);

        TEST(length(last) == 1);
        TEST(last->data == 500.);
        TEST(last->next == NULL);

        clear(tail);
        clear(last);
    }

    return tests_total - tests_successful;
}
