# DevCommeLesPros-2020-Ex1
Modèle de départ pour exercices d'introduction à Visual Studio Code, au débogueur, à la gestion de versions et github.com.

## Instructions de départ

1. Créez un compte sur http://github.com.
1. Créez une clé SSH et ajoutez-la au [ssh-agent](https://fr.wikipedia.org/wiki/Ssh-agent).
    - Suivez ces instructions: https://help.github.com/en/github/authenticating-to-github/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent.
    - Et celles-ci: https://help.github.com/en/github/authenticating-to-github/adding-a-new-ssh-key-to-your-github-account.
1. Créez votre dépôt sur http://github.com en utilisant ce dépôt-ci (https://github.com/thierryseegers/DevCommeLesPros-2020-Ex1) comme modèle.
    - Suivez ces instructions: https://help.github.com/en/github/creating-cloning-and-archiving-repositories/creating-a-repository-from-a-template.
    - Choisissez l'option `Private` à l'étape 5.
1. Ajoutez le professeur comme collaborateur à votre dépôt.
    - Suivez ces instructions: https://help.github.com/en/github/setting-up-and-managing-your-github-user-account/inviting-collaborators-to-a-personal-repository
        - Nom d'utilisateur à ajouter: `thierryseegers`.
1. Clonez votre dépôt vers votre espace de travail local.
    - Suivez ces instructions: https://help.github.com/en/github/creating-cloning-and-archiving-repositories/cloning-a-repository
    - Attention à ne pas cloner https://github.com/thierryseegers/DevCommeLesPros-2020-Ex1 mais bien votre dépôt nouvellement créé.
1. Lancez Visual Studio Code.
    - À l'invite de commandes:
        - `> cd [nom de votre dépôt]`
        - `> code .`
1. Installez l'extension `C/C++` pour Visual Studio Code.
    - Suivez ces instructions: https://code.visualstudio.com/docs/languages/cpp#_install-the-microsoft-cc-extension.
1. Pour travailler sous MacOS, installez aussi Xcode et l'extension `CodeLLDB` pour Visual Studio Code.
    - Installez Xcode via le App Store.
    - Installez "Xcode Command Line Tools". À l'invite de commandes: `> xcode-select --install`
    - https://marketplace.visualstudio.com/items?itemName=vadimcn.vscode-lldb <!-- Mesure temporaire tant que https://github.com/microsoft/vscode-cpptools/issues/3829 n'est pas résolu. -->
1. Compilez une première fois le programme.
    - Menu: `View` > `Command Palette` > `Tasks: Run Build Task`
1. Executez une première fois le programme avec le débogueur.
    - Menu: `View` > `Debug`
    - Choisissez la cible correspondant à votre système d'exploitation.
        - Menu déroulant `DEBUG`: {`test (Linux)`, `test (MacOS)`}
    - Menu: `Debug` > `Start debugging`
1. Vous devriez observer dans l'onglet `DEBUG CONSOLE` le résultat suivant:
    - Sous Linux: 
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

## "J'ai un problème !"

Il est parfaitement acceptable de demander de l'aide sur Internet.
Par contre, sur Internet, les questions d'étudiant se reniflent de loin alors soyez honnête dans la formulation de votre question et demandez bien *de l'aide*, ne demandez pas *la réponse*.

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
