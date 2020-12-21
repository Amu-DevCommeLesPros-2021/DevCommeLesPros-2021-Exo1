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

Ces intructions présupposent que vous avez déjà suivi les instructions de l'[exercice précédent](https://github.com/thierryseegers/DevCommeLesPros-2020-Exo0) pour la création de votre compte GitHub et l'installation des programmes et des extensions nécessaires.

1. Créez votre dépôt sur GitHub en utilisant ce dépôt-ci (https://github.com/thierryseegers/DevCommeLesPros-2020-Exo2) comme modèle.
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
1. Lancez le programme à l'invite de commande.
    - Menu : `Terminal` > `New Terminal`
    - `$ ./a.out`
    - Vous verrez s'afficher des résultats de tests et un sommaire de ces résultats.
    Ces résultats nous indiquent que certains des tests exécutés ont passé, certains ont échoué et que le programme s'est planté en cours de route.
1. Lancez le programme avec le débogueur.
    - Menu : `Run` > `Start Debugging`
        - Le débogueur lance l'application mais se met en pause dès la première ligne de code dans la fonction `main()`.
1. Affichez les informations de débogage.
    - Menu : `View` > `Open View...` > `Run`
        - Vous observez les valeurs de variables déclarés dans le contexte de la fonction `main()`.
1. Continuez l'exécution du programme jusqu'à sa fin.
    - Menu : `Run` > `Continue`
1. Le débogueur s'arrêtera net au moment où le code commet une erreur fatale de manipulation de mémoire et ça ressemblera à ceci :
![Bebogueur segfault](https://user-images.githubusercontent.com/1580647/102505819-bf0a9500-4082-11eb-8bb6-d39b14596d60.png)

Le programme en soi-même renvoie un code d'erreur correspondant au nombre de tests qui ont échoués ou qui n'ont pas été exécutés. Vous pouvez voir cette valeur (techniquement, la valeur du code d'erreur du dernier programme lancée) à l'invite de commande :
```
$ ./a.out
$ echo $?
63
```

## Objectif

Le programme contient du code pour créer et manipuler des [listes simplement chaînées](https://fr.wikipedia.org/wiki/Liste_cha%C3%AEn%C3%A9e#Liste_simplement_cha%C3%AEn%C3%A9e).
Il contient trois fichiers :
- `liste.h` : [fichier d'en-tête](https://en.wikipedia.org/wiki/Include_directive#C/C++) qui déclare les fonctions nécessaires.
- `liste.c` : fichier source qui [définie](https://stackoverflow.com/a/1410632/1300177) ces fonctions.
- `main.c` : contient du code dont la responsabilité est de tester toutes ces fonctions par des tests unitaires et d'afficher un compte rendu des tests.

Les fonctions définies dans le fichier `liste.c` contiennent toutes des erreurs.
L'objectif est de réparer les erreurs en s'aidant du débogueur.
Il s'agit de ne plus «essayer et se croiser les doigts» ou de comprendre ce qui se passe avec des `printf()`.
Le débogueur est là pour accélérer ce processus de compréhension et de réparation du code.
Du code, qui plus est, n'est pas le vôtre.

L'objectif est de réparer toutes les fonctions et que le programme retourne `0`.

Il vous est permis: 
- De modifier l'implémentation des fonctions définies dans le fichier `liste.c`.
Vous pouvez, si vous le désirez, changer le code du tout au tout mais ce ne devrait pas être nécessaire.
Le code existant fonctionne disont dans à peu près 50% des cas.
Seul quelques lignes sont à modifier, ajouter ou éliminer pour atteindre 100%.

Il ne vous est pas permis:
- De modifier les signatures des fonctions déclarées dans `fichier.c`. (Leurs types de retour et les types de leurs paramètres ne peuvent être modifiés.)
- De modifier ni `fichier.h` ni `main.c`.
(Rien ne vous en empêche au moment de travailler mais comprenez que le script d'évaluation utilisera `main.c` comme vous le voyez.)

## Instructions de travail

1. Au fur et à mesure de vos modifications au code, intégrez-les au dépôt local avec une description des modifications apportées.
    - `> git add main.c`
    - `> git commit -m "Description des modifications apportées"`
1. Périodiquement, publiez votre dépôt local à votre dépôt sur GitHub.
    - `> git push`
1. Répétez ces étapes jusqu'à ce que tout les tests passent.

Avec la commande `> git log --all --decorate --oneline --graph`, l'historique de votre travail devrait au fil du temps ressembler à ceci  (lire du bas vers le haut):

```
* d98fd55 (HEAD -> master) Passe tout les tests de insert().
* d6c6b98 Passe les test de insert() mais pas le cas special d'index 0.
* 26354bc Passe les tests de at() et set().
* 53b3e8d Passe les tests de length().
```

## «J'ai un problème !»

Il est parfaitement acceptable de demander de l'aide sur Internet.
Par contre, sur Internet, les questions d'étudiant se reniflent de loin alors soyez honnête dans la formulation de votre question et demandez bien *de l'aide*, ne demandez pas *la réponse*.
Démontrez ce que vous avez essayé et expliquez où vous bloquez.

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

L'évaluation portera sur :
1. Le suivi des instructions de travail.
1. Le nombre de tests réussis.
1. La qualité des modifications apportées.

Attention !
*Seul le code de votre dépôt sur [GitHub](http://github.com) compte !*
