# README - Projet Tower Defense

## Introduction

Bienvenue dans le projet de Tower Defense !
Ce jeu de stratégie vous met au défi de défendre une zone contre des vagues incessantes d'ennemis en utilisant des tours stratégiquement placées.
Ce document vous guidera à travers l'architecture du projet, les fonctionnalités et les instructions pour le lancement du jeu.

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
        - `Economy` : Gère les ressources financières du joueur.
        - `Level` : Représente le niveau du jeu avec ses chemins et ses points de spawn.

- **Vue (View)** : Interface utilisateur.
    - **Composants** :
        - `WindowView` : Gère la fenêtre principale du jeu.
        - `MainMenu` : Menu principal du jeu.
        - `GameView` : Interface de jeu en cours.
        - `ScoreBoard` : Affichage des scores.
        - `Settings` : Options de jeu.
        - `EnemyRenderer` : Gère l'affichage des ennemis et de leur barre de vie.

- **Contrôleur (Controller)** : Gère les interactions entre le modèle et la vue.
    - **Classes** :
        - `GameController` : Contrôle le flux du jeu.
        - `MenuController` : Gère les interactions du menu.
        - `SettingsController` : Gère les options de configuration.
        - `EventController` : Gère les événements d'entrée utilisateur.

### Design Patterns Utilisés

- **Singleton** : Utilisé pour le gestionnaire du son et la gestion du score, garantissant qu'il n'y a qu'une seule instance de ces classes.
- **Factory** : Utilisé pour créer dynamiquement des instances de tours et d'ennemis.

## Diagrammes UML

### Diagramme de classes

Le diagramme de classes illustre les relations entre les différentes classes du projet :


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
| + updateScore(int)           |
| + placeTower(Tower)          |
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
| + update(float)              |
+------------------------------+

+------------------------------+
|      Enemy                   |
+------------------------------+
| - id: int                    |
| - health: int                |
| - speed: float               |
| - damage: int                |
| - position: Position         |
| - currentNode: PathNode      |
| - nextNode: PathNode         |
+------------------------------+
| + move(float)                |
| + attack()                   |
| + takeDamage(int)            |
| + isDead(): boolean          |
| + setNextNode(PathNode)      |
+------------------------------+

+------------------------------+
|      Tower                   |
+------------------------------+
| - name: string               |
| - damage: int                |
| - range: float               |
| - upgradeLevel: int          |
| - health: int                |
+------------------------------+
| + attack(Enemy)              |
| + upgrade()                  |
| + takeDamage(int)            |
+------------------------------+

+------------------------------+
|      Economy                 |
+------------------------------+
| - goldAmount: int            |
| - profitMultiplier: int      |
+------------------------------+
| + earnGold(List<Enemy>)      |
| + buyTower(Tower)            |
| + getGoldAmount(): int       |
+------------------------------+

+------------------------------+
|      Level                   |
+------------------------------+
| - levelNumber: int           |
| - nodes: List<PathNode>      |
| - spawnPoint: PathNode       |
| - basePoint: PathNode        |
| - towerSpots: List<Position> |
+------------------------------+
| + addNode(PathNode)          |
| + isValid(): boolean         |
| + getSpawnPoint(): PathNode  |
| + addTowerSpot(Position)     |
+------------------------------+

+------------------------------+
|      PathNode                |
+------------------------------+
| - id: int                    |
| - type: string               |
| - gridPos: GridPosition      |
| - connections: List<PathNode>|
+------------------------------+
| + addConnection(PathNode)    |
| + findNextNode(PathNode)     |
| + getGridPosition():         |
|         GridPosition         |
+------------------------------+

+------------------------------+
|      WaveManager             |
+------------------------------+
| - currentWave: Wave          |
| - waveTimer: float           |
| - isWaveManualStart: boolean |
| - difficulty: string         |
+------------------------------+
| + startNewWave(PathNode)     |
| + update(float)              |
| + renderEnemies()            |
| + setDifficulty(string)      |
+------------------------------+

+------------------------------+
|      UIController            |
+------------------------------+
| - currentState: GameState    |
| - windowView: WindowView     |
| - eventController:           |
|          EventController     |
| - gameData: GameData         |
+------------------------------+
| + startGame()                |
| + pauseGame()                |
| + update(float)              |
| + setVolume(float)           |
| + showMessage(string, float) |
+------------------------------+

+------------------------------+
|      ScoreManager            |
+------------------------------+
| - scoreList: List<scoreEntry>|
+------------------------------+
| + addScore(string, int)      |
| + getHighScores():           |
|        List<scoreEntry>      |
+------------------------------+

+------------------------------+
|      SoundController         |
+------------------------------+
| - soundBuffers: Map<string,  | 
|           SoundBuffer>       |
| - currentMusic: Music        |
| - masterVolume: float        |
| - soundVolume: float         |
| - musicVolume: float         |
| - muted: boolean             |
+------------------------------+
| + loadSound(string, string)  |
| + playSound(string)          |
| + toggleMute()               |
| + setMasterVolume(float)     |
+------------------------------+

+------------------------------+
|      WindowView              |
+------------------------------+
| - window: RenderWindow       |
| - font: Font                 |
| - UIElements: List<Text>     |
| - messageText: Text          |
| - scoreText: Text            |
| - livesText: Text            |
+------------------------------+
| + render()                   |
| + updateVolumeDisplay(float) |
| + handleClick(Vector2f)      |
| + updateScore(int)           |
| + updateLives(int)           |
+------------------------------+

```

## Rôle de chaque fonction dans les classes

### 1. Classe `Game`

- **`+ startGame()`** : Initialise le jeu, configure les paramètres de départ, et commence la première vague d'ennemis.
- **`+ endGame()`** : Termine le jeu, que ce soit par une victoire ou une défaite, et affiche les scores finaux.
- **`+ updateScore()`** : Met à jour le score en fonction des actions du joueur, comme la destruction d'ennemis.

### 2. Classe `Wave`

- **`+ spawnEnemies()`** : Crée et déploie une liste d'ennemis pour la vague actuelle, en fonction de la difficulté.
- **`+ nextWave()`** : Prépare et lance la prochaine vague d'ennemis.

### 3. Classe `Enemy`

- **`+ move()`** : Gère le déplacement des ennemis.
- **`+ attack()`** : Définit le comportement de l'ennemi lorsqu'il attaque.
- **`+ takeDamage(int)`** : Réduit la santé de l'ennemi en fonction des dégâts subis.

### 4. Classe `Tower`

- **`+ attack(Enemy)`** : Permet à la tour d'attaquer un ennemi spécifique.
- **`+ upgrade()`** : Améliore la tour en augmentant ses statistiques.

### 5. Classe `ScoreManager`

- **`+ addScore(int)`** : Ajoute un certain nombre de points au score du joueur.
- **`+ getHighScores()`** : Retourne une liste des meilleurs scores.

### 6. Classe `WindowView`

- **`+ setup()`** : Configure la fenêtre SFML avec tous les paramètres nécessaires.
- **`+ events()`** : Gère les événements de la fenêtre.
- **`+ clear()`** : Efface le contenu de la fenêtre.
- **`+ display()`** : Affiche le contenu rendu.
- **`+ isOpen()`** : Vérifie si la fenêtre est ouverte.
- **`+ close()`** : Ferme proprement la fenêtre.
- **`+ setFrameRate(int)`** : Définit le taux de rafraîchissement.
- **`+ toggleFullscreen()`** : Bascule entre mode fenêtré et plein écran.

### 7. Classe `MainMenu`

- **`+ display()`** : Affiche les options du menu principal.
- **`+ handleInput()`** : Gère les interactions utilisateur pour sélectionner une option dans le menu.
- **`+ update()`** : Met à jour l'affichage du menu.

### 8. Classe `GameView`

- **`+ renderGame()`** : Dessine tous les éléments du jeu.
- **`+ update()`** : Met à jour l'affichage en fonction des actions du joueur.
- **`+ showGameOver()`** : Affiche l'écran de fin de jeu.

### 9. Classe `ScoreBoard`

- **`+ displayScores()`** : Affiche le score actuel et le tableau des meilleurs scores.
- **`+ updateScore(int)`** : Met à jour le score affiché.
- **`+ showHighScores()`** : Affiche une liste des meilleurs scores enregistrés.

### 10. Classe `Settings`

- **`+ displaySettings()`** : Affiche les options de configuration.
- **`+ changeVolume(int)`** : Modifie le niveau du volume sonore.
- **`+ setDifficulty(string)`** : Change le niveau de difficulté du jeu.

### 11. Classe `GameController`

- **`+ startGame()`** : Démarre un nouveau jeu en initialisant le modèle.
- **`+ updateGame()`** : Met à jour l'état du jeu.
- **`+ endGame()`** : Gère la logique de fin de jeu.

### 12. Classe `MenuController`

- **`+ selectOption(int option)`** : Gère la sélection d'une option dans le menu.
- **`+ showCredits()`** : Affiche les crédits du jeu.
- **`+ quitGame()`** : Gère la logique pour quitter le jeu.

### 13. Classe `SettingsController`

- **`+ changeVolume(int volume)`** : Met à jour le volume sonore.
- **`+ setDifficulty(string difficulty)`** : Change la difficulté du jeu.
- **`+ resetSettings()`** : Réinitialise les paramètres aux valeurs par défaut.

## Structure des fichiers


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
## Structure des fichiers

```
_ source
   |
   |__ logic
   |    |___ models
   |    |      |__ Economy.cpp
   |    |      |__ Enemy.cpp
   |    |      |__ Game.cpp
   |    |      |__ ScoreManager.cpp
   |    |      |__ Tower.cpp
   |    |      |__ Wave.cpp
   |    |      |__ towerVariants.cpp
   |    |
   |    |___ controllers
   |           |__ GameController.cpp
   |           |__ WaveManager.cpp
   |           |__ SoundController.cpp
   |           |__ UIController.cpp
   |           |__ EventController.cpp
   |
   |__ graphics
   |    |___ views
   |    |    |__ WindowView.cpp
   |    |    |__ towerView.cpp
   |    |    |__ MapRenderer.cpp
   |    |    |__ EnemyRenderer.cpp
   |    |
   |    |___ assets
   |         |__ images
   |         |__ sounds
   |
   |___ utils
         |__ GridPosition.h
         |__ Level.h
         |__ LevelLoader.h
         |__ PathNode.h
         |__ Position.h
         
_ includes
   |
   |__ logic
   |    |___ models
   |    |      |__ Economy.h
   |    |      |__ Enemy.h
   |    |      |__ Game.h
   |    |      |__ ScoreManager.h
   |    |      |__ Tower.h
   |    |      |__ Wave.h
   |    |      |__ towerVariants.h
   |    |
   |    |___ controllers
   |           |__ GameController.h
   |           |__ WaveManager.h
   |           |__ SoundController.h
   |           |__ UIController.h
   |           |__ EventController.h
   |
   |__ graphics
   |    |___ views
   |         |__ WindowView.h
   |         |__ towerView.h
   |         |__ MapRenderer.h
   |         |__ EnemyRenderer.h
   |
   |___ utils
           |__ GridPosition.h
           |__ Level.h
           |__ LevelLoader.h
           |__ PathNode.h
           |__ Position.h
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