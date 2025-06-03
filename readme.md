# README - Projet Tower Defense

## Introduction

Bienvenue dans le projet de Tower Defense ! 
Ce jeu de stratégie vous met au défi de défendre une zone contre des vagues incessantes d'ennemis en utilisant des tours stratégiquement placées. 
Ce document vous guidera à travers l'architecture du projet, les fonctionnalités, et les instructions pour le lancement du jeu.

## Architecture du Projet

### Modèle MVC

Le projet est structuré selon le modèle architectural MVC (Modèle-Vue-Contrôleur) :

- **Modèle (Model)** : Gère la logique, les données et les règles du jeu.
    - **Classes** :
        - `Tower` : Représente les tours de défense.
        - `Enemy` : Représente les ennemis qui attaquent.
        - `Wave` : Gère les vagues d'ennemis.
        - `Game` : Logique principale du jeu.
        - `ScoreManager` : Gère le score et les tableaux des scores.

- **Vue (View)** : Interface utilisateur.
    - **Composants** :
        - `MainMenu` : Menu principal du jeu.
        - `GameView` : Interface de jeu en cours.
        - `ScoreBoard` : Affichage des scores.
        - `Settings` : Options de jeu.

- **Contrôleur (Controller)** : Gère les interactions entre le modèle et la vue.
    - **Classes** :
        - `GameController` : Contrôle le flux du jeu.
        - `MenuController` : Gère les interactions du menu.
        - `SettingsController` : Gère les options de configuration.

### Design Patterns Utilisés

- **Singleton** : Pour le gestionnaire du son et la gestion du score, garantissant qu'il n'y a qu'une seule instance de ces classes.
- **Factory** : Pour créer dynamiquement des instances de tours et d'ennemis.

## Diagrammes UML

### **Diagramme de classes** :

Le diagramme de classes illustre les relations entre les différentes classes du projet.

```
            MODEL
+------------------------------+
|      Game                    |
+------------------------------+
| - waves: List<Wave>          |
| - scoreManager: ScoreManager |
| - currentWave: int           |
| - isGameOver: boolean        |
+------------------------------+
| + startGame()                |
| + endGame()                  |
| + updateScore()              |
+------------------------------+

+------------------------------+
|      Wave                    |
+------------------------------+
| - enemies: List<Enemy>       |
| - waveNumber: int            |
| - difficulty: string         |
+------------------------------+
| + spawnEnemies()             |
| + nextWave()                 |
+------------------------------+

+------------------------------+
|      Enemy                   |
+------------------------------+
| - health: int                |
| - speed: float               |
| - damage: int                |
+------------------------------+
| + attack()                   |
| + takeDamage(int)            |
+------------------------------+

+------------------------------+
|      Tower                   |
+------------------------------+
| - damage: int                |
| - range: float               |
| - upgradeLevel: int          |
+------------------------------+
| + attack(Enemy)              |
| + upgrade()                  |
+------------------------------+

+------------------------------+
|   ScoreManager               |
+------------------------------+
| - score: int                 |
| - highScores: List<int>      |
+------------------------------+
| + addScore(int)              |
| + getHighScores()            |
+------------------------------+

        VUE
+------------------------------+
|        MainMenu              |
+------------------------------+
| - options: List<string>      |
| - selectedOption: int        |
+------------------------------+
| + display()                  |
| + handleInput()              |
| + update()                   |
+------------------------------+

+------------------------------+
|        GameView              |
+------------------------------+
| - gameMap: Map               |
| - towers: List<Tower>        |
| - enemies: List<Enemy>       |
| - playerHealth: int          |
+------------------------------+
| + renderGame()               |
| + update()                   |
| + showGameOver()             |
+------------------------------+

+------------------------------+
|        ScoreBoard            |
+------------------------------+
| - currentScore: int          |
| - highScores: List<int>      |
+------------------------------+
| + displayScores()            |
| + updateScore(int)           |
| + showHighScores()           |
+------------------------------+

+------------------------------+
|        Settings              |
+------------------------------+
| - volume: int                |
| - difficulty: string         |
+------------------------------+
| + displaySettings()          |
| + changeVolume(int)          |
| + setDifficulty(string)      |
+------------------------------+

        CONTROLLEUR

+------------------------------+
|       GameController         |
+------------------------------+
| - game: Game                 |
| - gameView: GameView         |
+------------------------------+
| + startGame()                |
| + updateGame()               |
| + endGame()                  |
+------------------------------+

+------------------------------+
|      MenuController          |
+------------------------------+
| - mainMenu: MainMenu         |
+------------------------------+
| + selectOption(int option)   |
| + showCredits()              |
| + quitGame()                 |
+------------------------------+

+------------------------------+
|     SettingsController       |
+------------------------------+
| - settings: Settings         |
+------------------------------+
| + changeVolume(int volume)   |
| + setDifficulty(string)      |
| + resetSettings()            |
+------------------------------+

```
Rôle de chaque fonction dans les classes du diagramme de classes

#### 1. Classe `Game`

- **`+ startGame()`** : Cette méthode initialise le jeu, configure les paramètres de départ, et commence la première vague d'ennemis. 
                        Elle est responsable de l'organisation générale du flux de jeu.

- **`+ endGame()`** : Cette méthode termine le jeu, que ce soit par une victoire ou une défaite.
                      Elle peut afficher les scores finaux et éventuellement retourner au menu principal.

- **`+ updateScore()`** : Cette méthode met à jour le score en fonction des actions du joueur, comme la destruction d'ennemis. 
                          Elle interagit avec le `ScoreManager` pour garantir que le score est correct et à jour.

#### 2. Classe `Wave`

- **`+ spawnEnemies()`** : Cette méthode est responsable de la création et du déploiement d'une liste d'ennemis pour la vague actuelle. 
                            Elle utilise des paramètres comme le nombre d'ennemis et leur type, en fonction de la difficulté de la vague.

- **`+ nextWave()`** : Cette méthode prépare et lance la prochaine vague d'ennemis. 
                      Elle peut inclure des logiques pour augmenter la difficulté ou le nombre d'ennemis à mesure que le jeu progresse.

#### 3. Classe `Enemy`

- **`+ attack()`** : Cette méthode définit le comportement de l'ennemi lorsqu'il attaque, par exemple, infligeant des dégâts à la zone protégée ou aux tours. 
                    Elle peut également inclure des animations ou des effets sonores.

- **`+ takeDamage(int)`** : Cette méthode réduit la santé de l'ennemi en fonction des dégâts subis. 
                            Elle vérifie également si la santé de l'ennemi atteint zéro pour le détruire et éventuellement notifier le `Game` pour le score.

#### 4. Classe `Tower`

- **`+ attack(Enemy)`** : Cette méthode permet à la tour d'attaquer un ennemi spécifique, infligeant des dégâts en fonction de ses caractéristiques. 
                            Elle peut également gérer les animations d'attaque ou les effets spéciaux.

- **`+ upgrade()`** : Cette méthode améliore la tour en augmentant ses statistiques (dégâts, portée, etc.). 
                      Elle peut affecter l'apparence de la tour.

#### 5. Classe `ScoreManager`

- **`+ addScore(int)`** : Cette méthode ajoute un certain nombre de points au score du joueur. 
                            Elle peut être appelée après la destruction d'un ennemi ou à la fin d'une vague victorieuse.

- **`+ getHighScores()`** : Cette méthode retourne une liste des meilleurs scores, permettant au joueur de voir ses performances par rapport à d'autres joueurs. 
                              Elle peut également trier et stocker les scores pour une utilisation future.

#### 6. Classe `MainMenu`

- **`display()`** : Affiche les options du menu principal comme "Démarrer le Jeu", "Options", "Crédits" et "Quitter".

- **`handleInput()`** : Gère les interactions utilisateur, comme les clics ou les pressions de touches, pour sélectionner une option dans le menu.

- **`update()`** : Met à jour l'affichage du menu si nécessaire, par exemple, en surlignant une option sélectionnée.

#### 7. Classe `GameView`

- **`renderGame()`** : Dessine tous les éléments du jeu, y compris les tours, les ennemis, et les barres de vie.

- **`update()`** : Met à jour l'affichage en fonction des actions du joueur et des événements en cours, comme les attaques des tours et les mouvements des ennemis.

- **`showGameOver()`** : Affiche l'écran de fin de jeu lorsque le joueur perd ou termine toutes les vagues.

#### 8. Classe `ScoreBoard`

- **`displayScores()`** : Affiche le score actuel et le tableau des meilleurs scores.

- **`updateScore(int)`** : Met à jour le score affiché en fonction des changements dans le jeu.

- **`showHighScores()`** : Affiche une liste des meilleurs scores enregistrés.

#### 9. Classe `Settings`

- **`displaySettings()`** : Affiche les options de configuration disponibles.

- **`changeVolume(int)`** : Modifie le niveau du volume sonore en fonction des réglages choisis par l'utilisateur.

- **`setDifficulty(string)`** : Change le niveau de difficulté du jeu en fonction de la sélection de l'utilisateur.

#### 10. Classe `GameController`

- **`startGame()`** : Démarre un nouveau jeu en initialisant le modèle et en affichant la vue du jeu.

- **`updateGame()`** : Met à jour l'état du jeu, gére les vagues d'ennemis et les attaques des tours.

- **`endGame()`** : Gère la logique de fin de jeu et passe à l'affichage des résultats.

#### 11. Classe `MenuController`

- **`selectOption(int option)`** : Gère la sélection d'une option dans le menu, en appelant les fonctions appropriées pour démarrer le jeu, accéder aux paramètres, etc.

- **`showCredits()`** : Affiche les crédits du jeu lorsque l'utilisateur choisit cette option. (Liste des contributeurs, autres credits... comme l'utilisation de design tiers)

- **`quitGame()`** : Gère la logique pour quitter le jeu de manière appropriée.

#### 12. Classe `SettingsController`

- **`changeVolume(int volume)`** : Appelle la méthode de la vue pour mettre à jour le volume sonore et le modèle pour sauvegarder le nouveau paramètre.

- **`setDifficulty(string difficulty)`** : Change la difficulté du jeu en mettant à jour le modèle et en informant la vue.

- **`resetSettings()`** : Réinitialise les paramètres aux valeurs par défaut.


### **Diagramme utilisateur** : 
Montre les interactions de l'utilisateur avec le système.

```
+--------------------+
|     Utilisateur    |
+--------------------+
| - nom: string      |
| - score: int       |
+--------------------+
| + startGame()      |
| + accessOptions()  |
| + viewScores()     |
| + quitGame()       |
+--------------------+

```

## Fonctionnalités du Jeu

- **Vagues d'ennemis** : Gestion dynamique des vagues d'ennemis avec un timer.
- **Victoire/Défaite** : Conditions de victoire et de défaite basées sur l'arrivée des ennemis dans la zone protégée.
- **Gestion du score** : Calcul du score basé sur les ennemis éliminés et les vagues complétées, affiché dans un tableau des scores.
- **Gestion du son** : Options pour activer/désactiver la musique et les effets sonores.
- **Graphisme travaillé** : Interface attrayante avec des animations pour les tours et les ennemis.
- **Barres de vie des ennemis** : Barres de vie visibles pour chaque ennemi.
- **Évolutions des tours** : Système d'amélioration des tours.
- **Timer et compteur de vagues** : Affichage du temps restant pour la vague actuelle et le nombre de vagues restantes.

## Conclusion

Ce projet de Tower Defense est une excellente occasion de mettre en pratique des concepts de conception logicielle. 
Grâce à l'utilisation du MVC et de design patterns, nous visons à créer un jeu structuré et évolutif. 

## Instructions de Lancement

1. Clonez le dépôt.
2. Installez les dépendances requises.
3. Exécutez le fichier principal pour démarrer le jeu.