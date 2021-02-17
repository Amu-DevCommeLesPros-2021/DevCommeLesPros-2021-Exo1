# DevCommeLesPros-2021-Exo1

Modèle de départ pour exercices d'introduction au débogueur et à la gestion de versions.

<!-- TOC depthfrom:2 -->

- [Préparation](#pr%C3%A9paration)
- [Objectif](#objectif)
- [Instructions de travail](#instructions-de-travail)
    - [Ce qui est permis](#ce-qui-est-permis)
    - [Ce qui ne l'est pas](#ce-qui-ne-lest-pas)
- [Évaluation](#%C3%A9valuation)
- [Questions-Réponses](#questions-r%C3%A9ponses)
    - [«Puis-je utiliser l'en-tête <X.h> dans mon code ?»](#%C2%ABpuis-je-utiliser-len-t%C3%AAte-xh-dans-mon-code-%C2%BB)
    - [«J'ai un problème !»](#%C2%ABjai-un-probl%C3%A8me-%C2%BB)
        - [Comment demander de l'aide](#comment-demander-de-laide)
        - [Où demander de l'aide](#o%C3%B9-demander-de-laide)
    - [«Je me suis gouré royalement ! Est-ce que je peux recommencer de zéro ?»](#%C2%ABje-me-suis-gour%C3%A9-royalement--est-ce-que-je-peux-recommencer-de-z%C3%A9ro-%C2%BB)
    - [«Pourquoi pas de goto ou de boucles infinies ?»](#%C2%ABpourquoi-pas-de-goto-ou-de-boucles-infinies-%C2%BB)
    - [«Je n'ai rien fait encore et git me dit que tous les fichiers ont été modifiés.»](#%C2%ABje-nai-rien-fait-encore-et-git-me-dit-que-tous-les-fichiers-ont-%C3%A9t%C3%A9-modifi%C3%A9s%C2%BB)

<!-- /TOC -->

## Préparation

Ces intructions présupposent que vous avez déjà suivi les instructions de l'[exercice précédent](https://github.com/Amu-DevCommeLesPros-2021/DevCommeLesPros-2021-Exo0) pour la création de votre compte GitHub et l'installation des programmes et des extensions nécessaires.

1. Créez votre dépôt sur GitHub en utilisant [ce dépôt-ci](https://github.com/Amu-DevCommeLesPros-2021/DevCommeLesPros-2021-Exo1) comme modèle.
    - Suivez [ces instructions](https://docs.github.com/en/free-pro-team@latest/github/creating-cloning-and-archiving-repositories/creating-a-repository-from-a-template).
    - Choisissez l'option `Private` à l'étape 5.
1. Ajoutez le professeur comme collaborateur à votre dépôt.
    - Suivez [ces instructions](https://docs.github.com/en/free-pro-team@latest/github/setting-up-and-managing-your-github-user-account/inviting-collaborators-to-a-personal-repository).
    - Nom d'utilisateur à ajouter : `thierryseegers`.
1. Clonez votre dépôt vers votre espace de travail local.
    - Suivez [ces instructions](https://docs.github.com/en/free-pro-team@latest/github/creating-cloning-and-archiving-repositories/cloning-a-repository).
    - Attention à ne pas cloner https://github.com/Amu-DevCommeLesPros-2021/DevCommeLesPros-2021-Exo1 mais bien votre dépôt nouvellement créé.
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
        - Vous observez les valeurs des variables déclarées dans le contexte de la fonction `main()`.
1. Continuez l'exécution du programme jusqu'à sa fin.
    - Menu : `Run` > `Continue`
1. Le débogueur s'arrêtera net au moment où le code commet une erreur fatale de manipulation de mémoire et ça ressemblera à ceci :
![Débogueur segfault](https://user-images.githubusercontent.com/1580647/102505819-bf0a9500-4082-11eb-8bb6-d39b14596d60.png)

S'il est lancé directement à l'invite de commande (`$ ./a.out`), le programme :
- affiche le résultat de chaque test exécutés : `[SUCCES]`, `[ECHEC]` ou `[FATAL(N)]` (à `[FATAL(N)]`, le programme est stoppé).
- affiche en fin d'exécution le nombre de tests total, de tests exécutés et de tests réussis.
- retourne comme valeur à l'invite de commande la différence entre le nombre de tests total et de tests réussis (p. ex. 66 - 3 -> `63`).
Vous pouvez voir cette valeur (techniquement, la valeur du code d'erreur du dernier programme lancé) à l'invite de commande :
```
$ ./a.out
.
.
.
$ echo $?
63
```

## Objectif

Le programme contient du code pour créer et manipuler des [listes simplement chaînées](https://fr.wikipedia.org/wiki/Liste_cha%C3%AEn%C3%A9e#Liste_simplement_cha%C3%AEn%C3%A9e).
Il contient trois fichiers :
- `liste.h` : [fichier d'en-tête](https://en.wikipedia.org/wiki/Include_directive#C/C++) qui déclare les fonctions nécessaires.
- `liste.c` : fichier source qui [définit](https://stackoverflow.com/a/1410632/1300177) ces fonctions.
- `main.c` : contient du code dont la responsabilité est de tester toutes ces fonctions par des [tests unitaires](https://fr.wikipedia.org/wiki/Test_unitaire) et d'afficher un compte rendu des tests.

Les fonctions définies dans le fichier `liste.c` contiennent toutes des erreurs.
L'objectif est de réparer les erreurs en s'aidant du débogueur.
Il s'agit de ne plus «essayer et se croiser les doigts» ou de comprendre ce qui se passe avec des `printf()`.
Le débogueur est là pour accélérer ce processus de compréhension et de réparation du code.
Vous trouverez [ici](https://code.visualstudio.com/docs/editor/debugging) des instructions complètes pour le débogage avec Code.
L'exemple est donné avec un programme en Javascript mais il s'applique pareillement avec un programme en C ou C++.

L'objectif est donc de réparer toutes les fonctions et que :
- le programme affiche que tous les tests ont passé avec succès.
- le programme retourne `0` à l'invite de commandes.

## Instructions de travail

1. Au fur et à mesure de vos modifications au code, intégrez-les au dépôt local avec une description des modifications apportées.
    - `$ git add liste.c`
    - `$ git commit -m "Description des modifications apportées"`
1. Périodiquement, publiez votre dépôt local à votre dépôt sur GitHub.
    - `$ git push`
1. Répétez ces étapes jusqu'à ce que tous les tests passent.

Avec la commande `$ git log --all --decorate --oneline --graph`, l'historique de votre travail devrait au fil du temps ressembler à ceci  (lire du bas vers le haut) :

```
* d98fd55 (HEAD -> master) Passe tous les tests de insert().
* d6c6b98 Passe les test de insert() mais pas le cas special d'index 0.
* 26354bc Passe les tests de at() et set().
* 53b3e8d Passe les tests de length().
```

### Ce qui est permis

- De modifier l'implémentation des fonctions définies dans le fichier `liste.c`.
Vous pouvez, si vous le désirez, changer le code du tout au tout mais ce ne devrait pas être nécessaire.
Le code existant fonctionne disont dans à peu près 50% des cas.
Seul quelques lignes sont à modifier, ajouter ou éliminer pour atteindre 100%.

### Ce qui ne l'est pas

- De modifier les signatures des fonctions déclarées dans `liste.c`.
(Leurs types de retour et les types de leurs paramètres ne peuvent être modifiés.)
- De modifier ni `liste.h` ni `main.c`.
(Rien ne vous en empêche au moment de travailler mais comprenez que le script d'évaluation utilisera les fichiers `liste.h` et `main.c` d'origine.)
- D'utiliser `goto` et d'avoir des «boucles infinies» du style `while(1)`. Pourquoi ? La réponse est [ici](#pourquoi-pas-de-goto-ou-de-boucles-infinies-).

## Évaluation

L'évaluation portera sur :
1. Le suivi des instructions de travail.
1. Le nombre de tests réussis.
1. La qualité des modifications apportées.

Attention !
*Seul le code de votre dépôt sur [GitHub](https://github.com) compte !*

## Questions-Réponses

### «Puis-je utiliser l'en-tête `<X.h>` dans mon code ?»

Oui.
Vous avez droit à toutes les en-têtes C standard pour cet exercice et tous les exercices suivants.
Explorez particulièrement `<ctype.h>` et `<string.h>`.

### «J'ai un problème !»

Il est parfaitement acceptable de demander de l'aide sur Internet.
Par contre, sur Internet, les questions d'étudiant se reniflent de loin alors soyez honnête dans la formulation de votre question et demandez bien *de l'aide*, ne demandez pas *la réponse*.
Démontrez ce que vous avez essayé et expliquez où vous bloquez.

#### Comment demander de l'aide
1. https://stackoverflow.com/help/how-to-ask
1. https://www.reddit.com/r/C_Programming/comments/9l0vuz/asking_for_help_what_to_do_when_your_program/
1. https://en.wikipedia.org/wiki/Wikipedia:Reference_desk/How_to_ask_a_software_question
1. http://www.catb.org/%7Eesr/faqs/smart-questions.html

#### Où demander de l'aide
1. https://devcommelespros.slack.com ([invitation](https://join.slack.com/t/devcommelespros/shared_invite/enQtODg1MjI3NTYwODE4LWI2NTE1YTQ2ODg2MmMyYTliYTJkNDcwYTVhOWQ5N2Y0NDkyZGZhZjAwM2Q2NDRjY2Y2NjI3OTU1YjAzZDcwY2I))
1. https://stackoverflow.com
1. https://reddit.com/r/C_Programming/
1. https://reddit.com/r/codinghelp

### «Je me suis gouré royalement ! Est-ce que je peux recommencer de zéro ?»

Oui.
Pour ce faire, il faut effacer le dépôt et en créer un nouveau.
Suivez [ces instructions](https://docs.github.com/en/free-pro-team@latest/github/administering-a-repository/deleting-a-repository) puis recommencez l'exercice depuis l'étape de  [préparation](#pr%C3%A9paration).
**Assurez-vous de me ré-inviter comme collaborateur à votre nouveau dépôt et ce même s'il porte exactement le même nom !**

### «Pourquoi pas de `goto` ou de boucles infinies ?»

Pour vous forcer à visualiser les tenants et aboutissants de vos boucles *avant de toucher au clavier*. Si vous avez de la difficulté à reformuler votre code sans, je suis là pour vous aider.

J'aurais bien envie de vous interdire aussi l'usage de `break` et de `continue` mais cette opinion, bien que défendable, est relativement exceptionnelle dans le monde du C alors je vais me retenir :smiley:. Sachez cependant qu'il est possible de réussir à la perfection tous les exercices que je vous donne sans une seule utilisation de `break` et `continue`. Je vous laisse avec cette astuce :

```
for(int i = 0; i != n; ++i)
{
    // ...

    if(X)
    {
        break;
    }
}
```

Devient :
```
for(int i = 0; !X && i != n; ++i)
{
    // ...
}
```

### «Je n'ai rien fait encore et `git` me dit que tous les fichiers ont été modifiés.»

Réponse rapide : si vous travaillez sous Windows avec WSL, il est préférable d'utiliser `git` à l'invite de commande de WSL et non pas dans le contexte de Windows.
Du fait, installez `git` sous WSL avec la commande `$ sudo apt-get install git` et n'utilisez `git` que dans le contexte de WSL (ou de l'onglet `Terminal` de Visual Studio Code, étant soi-même un terminal de WSL).

Réponse complète : pour des raisons historiques, sous Windows les «[fins de ligne](https://fr.wikipedia.org/wiki/Fin_de_ligne)» sont encodées par les deux caractères `\CR\LF` (retour de chariot suive de saut de ligne).
Sous Linux, les fins de ligne ne sont encodées que par le caractère `\LF`.
Quand vous installez et utilisez `git` pour Windows ([GitBash](https://git-scm.com/download/win) par exemple), ccelui-ci est configuré par défaut pour convertir les fin de lignes en version «Windows».
Comme vous allez ensuite visionner et modifier ces fichiers sous WSL qui est Linux, les fichiers apparaîtront comme modifiés.

Outre utiliser `git` exclusivement sous WSL, il vous est aussi possible de changer cette configuration avec `$ git config core.autocrlf input`.
Voici un avant/après de ce ça donnera :

![git-crlf-input-good](https://user-images.githubusercontent.com/1580647/108228834-8436e300-713f-11eb-9764-c8d553df6098.PNG)

Cette modification à la configuration de `git` n'est que locale, pour reconfigurer `git` une fois pour toute de façon globale faite `$ git config --global core.autocrlf input` à l'invite de commande.
