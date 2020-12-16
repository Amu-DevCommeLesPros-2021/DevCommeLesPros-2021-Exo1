# DevCommeLesPros-2020-Exo1

Modèle de départ pour exercices d'introduction au débogueur et à la gestion de versions.

<!-- TOC -->

- [DevCommeLesPros-2020-Exo1](#devcommelespros-2020-exo1)
    - [Instructions de départ](#instructions-de-d%C3%A9part)
    - [Objectif](#objectif)
    - [Instructions de travail](#instructions-de-travail)
    - [«J'ai un problème !»](#%C2%ABjai-un-probl%C3%A8me-%C2%BB)
        - [Comment demander de l'aide](#comment-demander-de-laide)
        - [Où demander de l'aide](#o%C3%B9-demander-de-laide)
    - [«Je me suis gouré royalement ! Est-ce que je peux recommencer de zéro ?»](#%C2%ABje-me-suis-gour%C3%A9-royalement--est-ce-que-je-peux-recommencer-de-z%C3%A9ro-%C2%BB)
    - [Évaluation](#%C3%A9valuation)

<!-- /TOC -->

## Instructions de départ

Ces intructions présupposent que vous avez déjà suivi les instructions de l'[exercice précédent](https://github.com/thierryseegers/DevCommeLesPros-2020-Exo0) pour la création de votre compte GitHub et l'installation des programmes et des extensions nécéssaires.

1. Créez votre dépôt sur github.com en utilisant ce dépôt-ci (https://github.com/thierryseegers/DevCommeLesPros-2020-Exo2) comme modèle.
    - Suivez ces instructions: https://docs.github.com/en/free-pro-team@latest/github/creating-cloning-and-archiving-repositories/creating-a-repository-from-a-template.
    - Choisissez l'option `Private` à l'étape 5.
1. Ajoutez le professeur comme collaborateur à votre dépôt.
    - Suivez ces instructions: https://docs.github.com/en/free-pro-team@latest/github/setting-up-and-managing-your-github-user-account/inviting-collaborators-to-a-personal-repository
        - Nom d'utilisateur à ajouter: `thierryseegers`.
1. Clonez votre dépôt vers votre espace de travail local.
    - Suivez ces instructions: https://docs.github.com/en/free-pro-team@latest/github/creating-cloning-and-archiving-repositories/cloning-a-repository
    - Attention à ne pas cloner https://github.com/thierryseegers/DevCommeLesPros-2020-Exo2 mais bien votre dépôt nouvellement créé.
1. Lancez Visual Studio Code.
    - À l'invite de commandes :
        - `$ cd [nom de votre dépôt]`
        - `$ code .`
1. Compilez une première fois le programme.
    - Menu : `View` > `Command Palette` > `Tasks: Run Build Task`
1. Lancez une première fois le programme avec le débogueur.
    - Menu : `Run` > `Start Debugging`
        - Le débogueur lance l'application mais se met en pause dès la première ligne de code dans la fonction `main()`.
1. Affichez les informations de débogage.
    - Menu : `View` > `Open View...` > `Run`
        - Vous observez les valeurs de variables déclarés dans le contexte de la fonction `main()`.
1. Continuez l'exécution du programme jusqu'à sa fin.
    - Menu : `Run` > `Continue`
1. Vous devriez observer dans l'onglet `DEBUG CONSOLE` le résultat suivant :
    - Sous Linux et Windows+WSL :
        - `[Inferior 1 (process [NNNN]) exited with code 027]`.
        - Attention, le débogueur `gdb` affiche le code de retour en octal (base 8). Ici, `027` en octal est `23` en décimal.
    - Sous MacOS:
        - `Process exited with code 23.`

Vous pouvez voir la valeur retournée par le programme dans l'onglet `DEBUG CONSOLE` comme décrit ci-haut.
Vous pouvez aussi voir la valeur retournée par le dernier programme lancé à l'invite de commandes avec `echo $?`.
Dans l'example suivant, le programme `a.out` a retourné la valeur `23`.
```
> ./a.out
> echo $?
23
```

## Objectif

Le programme contient quatre fonctions qui contiennent des erreurs.
Ces fonctions sont testées par un macro qui compare le résultat reçu avec le résultat attendu.
Si les résultats ne correspondent pas, un compteur de résultat final est incrementé de un.
À la fin du programme, ce compteur final est retourné au système d'exploitation.
L'objectif est de réparer toutes les fonctions et que le programme retourne `0`.

Il vous est permis: 
- De modifier les définitions des fonctions `palindrome`, `inverse`, `en_chaine` et `anagramme` à votre gré.

Il ne vous est pas permis:
- De modifier les déclarations des fonctions `palindrome`, `inverse`, `en_chaine` et `anagramme`. (Leurs types de retour et les types de leurs paramètres ne peuvent être modifiés.)
- De modifier la définition de la fonction `main`. Assurez-vous d'aucunement modifier le code qui vient après `int main()` car le script de correction en dépend.

## Instructions de travail

1. Au fur et à mesure de vos modifications au code, intégrez-les au dépôt local avec une description des modifications apportées.
    - `> git add main.c`
    - `> git commit -m "Description des modifications apportées"`
1. Périodiquement, publiez votre dépôt local à votre dépôt sur github.com.
    - `> git push`
1. Répétez ces étapes jusqu'à ce que tout les tests passent.

Avec la commande `> git log --all --decorate --oneline --graph`, l'historique de votre travail devrait au fil du temps ressembler à ceci  (lire du bas vers le haut):

```
* d98fd55 (HEAD -> master) Passe tout les tests de la fonction en_chaine.
* d6c6b98 Passe les test de la fonction en_chaine avec les nombres positifs.
* 26354bc Passe les tests de inverse.
* 53b3e8d Passe les tests de palindrome.
```

## «J'ai un problème !»

Il est parfaitement acceptable de demander de l'aide sur Internet.
Par contre, sur Internet, les questions d'étudiant se reniflent de loin alors soyez honnête dans la formulation de votre question et demandez bien *de l'aide*, ne demandez pas *la réponse*.

### Comment demander de l'aide
1. https://stackoverflow.com/help/how-to-ask
1. https://www.reddit.com/r/C_Programming/comments/9l0vuz/asking_for_help_what_to_do_when_your_program/
1. https://en.wikipedia.org/wiki/Wikipedia:Reference_desk/How_to_ask_a_software_question
1. http://www.catb.org/%7Eesr/faqs/smart-questions.html

### Où demander de l'aide
1. https://devcommelespros.slack.com ([invitation](https://join.slack.com/t/devcommelespros/shared_invite/enQtODg1MjI3NTYwODE4LWI2NTE1YTQ2ODg2MmMyYTliYTJkNDcwYTVhOWQ5N2Y0NDkyZGZhZjAwM2Q2NDRjY2Y2NjI3OTU1YjAzZDcwY2I))
1. https://stackoverflow.com
1. https://reddit.com/r/C_Programming/
1. https://reddit.com/r/codinghelp

## «Je me suis gouré royalement ! Est-ce que je peux recommencer de zéro ?»

Oui.
Pour ce faire, il faut effacer le dépôt et le recréer.
Suivez ces instruction : https://docs.github.com/en/free-pro-team@latest/github/administering-a-repository/deleting-a-repository puis recommencez l'exercice depuis les [Instructions de départ](#instructions-de-d%C3%A9part).
**Assurez-vos de me ré-inviter comme collaborateur à votre nouveau dépôt !**


## Évaluation

Dans le répertoire `correction`, vous trouverez le script que le professeur utilisera pour automatiser une première partie du processus de correction.
Pour une liste de dépôts donnée dans `correction/depots.txt`, le script clone et compile le dépôt, lance le programme et affiche le résultat.
Vous pouvez tester votre propre dépôt comme le fera le professeur:
1. Installez le module pygit2 avec `> pip3 install pygit2` à l'invite de commandes.
1. Ajoutez le nom de votre dépôt à la liste `correction/depots.txt`.
1. Lancez le script à l'invite de commandes:
    - `> cd correction`
    - `> python3 correction.py`

La deuxième partie de la correction est une inspection visuelle de votre code.

Seul le code de votre dépôt sur http://github.com compte !
