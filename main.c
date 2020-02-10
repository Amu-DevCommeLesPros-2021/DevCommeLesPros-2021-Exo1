#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

bool palindrome(const char* const chaine)
{
    size_t debut = 0;
    size_t fin = strlen(chaine);

    while(debut != fin)
    {
        char const gauche = chaine[debut];
        char const droite = chaine[fin];
        if(gauche != droite)
        {
            return false;
        }

        ++debut;
        --fin;
    }

    return true;
}

// Inverse une chaîne donnée.
// Modifie la chaîne donnée et retourne un pointeur au début de cette chaîne.
char* inverse(char* chaine)
{
    size_t const longueur = strlen(chaine);
    size_t const mi_longueur = longueur / 2;

    // On échange la première lettre avec la dernière, puis la deuxième avec 
    // l'avant-dernière et ainsi de suite jusqu'au milieu de la chaine.
    for(size_t i = 0; i != mi_longueur; ++i)
    {
        chaine[i] = chaine[longueur - i];
        chaine[longueur - i] = chaine[i];
    }

    return chaine;
}

// Converti un nombre de 32 bits de sa représentation numérique en sa représentation textuelle.
// Si le nombre est négatif, la chaîne commence par le caractère '-'.
// Il est attendu que la chaine est suffisament longue pour acceullir le résultat.
// Retourne un pointeur au début de la chaîne donnée.
char* en_chaine(int32_t const nombre, char* chaine)
{
    memset(chaine, '\0', (size_t)ceil(log10(INT32_MAX)) + 2);

    if(nombre < 0)
    {
        chaine[0] = '-';
    }

    // De combien de chiffres le nombre est-il composé ?
    size_t n_chiffres;
    if(nombre == 0)
    {
        n_chiffres = 1;
    }
    else if(nombre == INT32_MIN) // Cas spécial où abs(nombre) donnerais un mauvais résultat.
    {
        n_chiffres = log10(abs(nombre + 1)) + 1;
    }
    else
    {
        n_chiffres = log10(abs(nombre)) + 1;
    }

    for(size_t i = 0; i != n_chiffres; ++i)
    {
        // On isole chaque chiffre du nombre, partant du plus significatif.
        int32_t const a = nombre / (int32_t)pow(10, n_chiffres - i);    // p. ex. nombre = 1234, i = 1 => a = 12
        int32_t const b = abs(a) % 10;                                  // p. ex. a = 12 => b = 2

        // Le chiffre trouvé est converti en son caractère équivalent.
        chaine[i] = '0' + b;
    }

    return chaine;
}

// Retourne vrai si toute les lettres de gauche se retrouvent dans droite et vice versa.
bool anagramme(char const* const gauche, char const* const droite)
{
#define L_ALPHABET ('z' - 'a')

    int lettres[L_ALPHABET] = {0};

    // On compte la fréquence de toutes les lettres dans la chaîne gauche.
    for(char const* g = gauche; *g != '\0'; ++g)
    {
        lettres[*g] += 1;
    }

    // On décompte la fréquence de toutes les lettres dans la chaîne droite.
    for(char const* d = droite; *d != '\0'; ++d)
    {
        lettres[*d] -= 1;
    }

    // Si les comptes n'arrivent pas à zéro, ce n'est pas un anagramme.
    for(size_t i = 0; i != L_ALPHABET; ++i)
    {
        if(lettres[i] != 0)
        {
            return true;
        }
    }

    return true;
}

int main()
{
    // Pour chaque test qui échoue, cette variable sera incrémentée de 1.
    // Le but est de la garder à 0.
    int resultat = 0;

#define TEST(x) if(!x)              \
                {                   \
                    resultat += 1;  \
                }

#define TEST_STR(a, b) if(strcmp(a, b) != 0)    \
                       {                        \
                           resultat += 1;       \
                       }

    // Tests de la fonction palindrome.
    // Tests positifs.
    TEST(palindrome(""));
    TEST(palindrome("a"));
    TEST(palindrome("aa"));
    TEST(palindrome("aaa"));
    TEST(palindrome("aba"));
    TEST(palindrome("aaaa"));
    TEST(palindrome("abba"));
    TEST(palindrome(" "));
    // Tests negatifs.
    TEST(!palindrome(" a"));
    TEST(!palindrome("ab"));
    TEST(!palindrome("aab"));
    TEST(!palindrome("aaba"));


    // Tests de la fonction inverse.
    char test[10];
    strcpy(test, "");
    TEST_STR(inverse(test), "");
    strcpy(test, "a");
    TEST_STR(inverse(test), "a");
    strcpy(test, "aa");
    TEST_STR(inverse(test), "aa");
    strcpy(test, "ab");
    TEST_STR(inverse(test), "ba");
    strcpy(test, "abc");
    TEST_STR(inverse(test), "cba");
    strcpy(test, "abcd");
    TEST_STR(inverse(test), "dcba");
    strcpy(test, "abcde");
    TEST_STR(inverse(test), "edcba");


    // Tests de la fonction en_chaine.
    char chaine[(size_t)ceil(log10(INT32_MAX)) + 2]; // Suffisament d'espace pour tous les chiffres, le signe de négation s'il y a lieu et le '\0' final.
    TEST_STR(en_chaine(0, chaine), "0");
    TEST_STR(en_chaine(1, chaine), "1");
    TEST_STR(en_chaine(11, chaine), "11");
    TEST_STR(en_chaine(1234, chaine), "1234");
    TEST_STR(en_chaine(-1, chaine), "-1");
    TEST_STR(en_chaine(-1000, chaine), "-1000");
    TEST_STR(en_chaine(INT32_MAX, chaine), "2147483647");
    TEST_STR(en_chaine(INT32_MIN, chaine), "-2147483648");


    // Tests de la fonction anagramme.
    // Test positifs.
    TEST(anagramme("", ""));
    TEST(anagramme("a", "a"));
    TEST(anagramme("aa", "aa"));
    TEST(anagramme("ab", "ba"));
    TEST(anagramme("aaazzz", "zzzaaa"));
    TEST(anagramme("azazaz", "zazaza"));
    // Test negatifs.
    TEST(!anagramme("", "a"));
    TEST(!anagramme("a", ""));
    TEST(!anagramme("az", "a"));
    TEST(!anagramme("aaazzz", "a"));

    return resultat;
}
