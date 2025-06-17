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
# Diagramme de classes

```mermaid
classDiagram
    %% Application Layer
    class GameApplication {
        -window: sf::RenderWindow
        -windowView: unique_ptr~WindowView~
        -uiController: shared_ptr~UIController~
        -eventController: shared_ptr~EventController~
        -applicationRunning: bool
        +GameApplication()
        +run()
    }

    %% Controllers Layer
    class UIController {
        -currentState: GameState
        -windowView: WindowView*
        -eventController: shared_ptr~EventController~
        -gameController: shared_ptr~GameController~
        -waveManager: shared_ptr~WaveManager~
        -economy: unique_ptr~Economy~
        -gameData: GameData
        +setState(GameState)
        +startGame()
        +pauseGame()
        +update(float)
        +handleClick(sf::Vector2f)
    }

    class GameController {
        -game: unique_ptr~Game~
        -scoreManager: unique_ptr~ScoreManager~
        -currentPlayer: string
        -currentScore: int
        -windowView: WindowView*
        -eventController: shared_ptr~EventController~
        -gameRunning: bool
        +startGame()
        +update(float)
        +loginPlayer(string)
        +addPlayerScore(int)
    }

    class EventController {
        -mousePosition: sf::Vector2f
        -isDraggingVolume: bool
        -buttons: unordered_map~string, ButtonInfo~
        -keyCallback: KeyCallback
        -mouseClickCallback: MouseClickCallback
        +handleEvent(sf::Event, sf::RenderWindow)
        +registerKeyCallback(KeyCallback)
        +registerMouseClickCallback(MouseClickCallback)
    }

    class SoundController {
        -soundBuffers: map~string, sf::SoundBuffer~
        -sounds: map~string, unique_ptr~sf::Sound~~
        -currentMusic: unique_ptr~sf::Music~
        -masterVolume: float
        -soundVolume: float
        -musicVolume: float
        -muted: bool
        +getInstance(): SoundController&
        +playSound(string)
        +setMasterVolume(float)
        +mute()
        +unmute()
    }

    class WaveManager {
        -currentWave: shared_ptr~Wave~
        -currentLevel: shared_ptr~Level~
        -waveTimer: float
        -isWaveManualStart: bool
        -currentDifficulty: string
        -enemyRenderer: EnemyRenderer
        +setLevel(shared_ptr~Level~)
        +startNewWave(shared_ptr~PathNode~)
        +update(float)
        +isWaveComplete(): bool
        +renderEnemies(sf::RenderWindow)
    }

    %% Models Layer
    class Game {
        -running: bool
        -paused: bool
        -gameOver: bool
        -gameTime: float
        -baseHealth: int
        -currentScore: int
        -waveManager: unique_ptr~WaveManager~
        -economy: unique_ptr~Economy~
        -currentLevel: shared_ptr~Level~
        -towers: vector~shared_ptr~Tower~~
        +start()
        +pause()
        +update(float)
        +placeTower(string, Position): bool
        +getEnemies(): vector~shared_ptr~Enemy~~
    }

    class Enemy {
        -id: int
        -health: int
        -maxHealth: int
        -speed: float
        -damage: int
        -position: Position
        -currentNode: shared_ptr~PathNode~
        -nextNode: shared_ptr~PathNode~
        -progress: float
        -type: EnemyType
        +reward: int
        +Enemy(int, int, float, int, shared_ptr~PathNode~, EnemyType)
        +move(float)
        +takeDamage(int)
        +isDead(): bool
        +hasReachedEnd(): bool
    }

    class Tower {
        -instance: Tower
        -baseHealth: int
        +name: string
        +health: int
        +atk: int
        +level: int
        +atkMultiplier: double
        +visible: bool
        +spritePath: string
        +price: int
        +getInstance(): Tower&
        +attack(Enemy*)
        +upgrade()
        +takeDamage(int)
        +createTower(string): Tower*
    }

    class Wave {
        -enemies: vector~shared_ptr~Enemy~~
        -waveNumber: int
        -difficulty: string
        -spawnNode: shared_ptr~PathNode~
        -isComplete: bool
        -enemiesToSpawn: int
        -spawnTimer: float
        -spawnInterval: float
        +Wave(int, string, shared_ptr~PathNode~)
        +spawnEnemies(float)
        +update(float)
        +isWaveComplete(): bool
        +areAllEnemiesDead(): bool
    }

    class Economy {
        +goldAmount: int
        +profitMultiplier: int
        +earnGold(vector~Enemy*~)
        +getGoldAmount(): int
        +buyTower(Tower*): bool
    }

    class ScoreManager {
        +scoreList: vector~scoreEntry~
        +addScore(string, int)
        +getHighScores(): vector~scoreEntry~
    }

    %% Views Layer
    class WindowView {
        -window: sf::RenderWindow&
        -mapRenderer: unique_ptr~MapRenderer~
        -currentLevel: shared_ptr~Level~
        -view: sf::View
        -font: sf::Font
        -gameField: sf::RectangleShape
        -sidePanel: sf::RectangleShape
        -currentScore: int
        -playerMoney: int
        -baseLives: int
        +WindowView(sf::RenderWindow&)
        +render(sf::RenderWindow&)
        +updateScore(int)
        +updateMoney(int)
        +handleClick(sf::Vector2f)
        +setLevel(shared_ptr~Level~)
    }

    class MapRenderer {
        -window: sf::RenderWindow&
        -enemyRenderer: unique_ptr~EnemyRenderer~
        -currentLevel: shared_ptr~Level~
        -currentWave: shared_ptr~Wave~
        -baseTexture: sf::Texture
        -baseSprite: sf::Sprite
        +CELL_SIZE: float
        +GAME_FIELD_X: float
        +GAME_FIELD_Y: float
        +MapRenderer(sf::RenderWindow&)
        +setLevel(shared_ptr~Level~)
        +render()
        -renderGrid()
        -renderEnemies()
    }

    class EnemyRenderer {
        -enemySprites: sf::Sprite[3]
        -font: sf::Font
        -textures: sf::Texture[3]
        +EnemyRenderer()
        +loadSprites()
        +renderEnemy(shared_ptr~Enemy~, sf::RenderWindow&)
        +renderHealthBar(shared_ptr~Enemy~, sf::RenderWindow&)
    }

    class towerView {
        +displayTower(Tower*)
    }

    %% Utility Classes
    class Level {
        -levelNumber: int
        -nodes: vector~shared_ptr~PathNode~~
        -spawnPoint: shared_ptr~PathNode~
        -basePoint: shared_ptr~PathNode~
        -towerSpots: vector~Position~
        +Level(int)
        +addNode(shared_ptr~PathNode~)
        +addTowerSpot(Position)
        +isValidTowerPosition(Position): bool
        +isValid(): bool
    }

    class PathNode {
        -id: int
        -type: string
        -gridPos: GridPosition
        -connections: vector~shared_ptr~PathNode~~
        +PathNode(int, string, GridPosition)
        +addConnection(shared_ptr~PathNode~)
        +findNextNode(shared_ptr~PathNode~): shared_ptr~PathNode~
        +getPixelPosition(): Position
    }

    class LevelLoader {
        +loadLevel(int): shared_ptr~Level~
        -configureLevelOne(shared_ptr~Level~)
        -configureLevelTwo(shared_ptr~Level~)
    }

    %% Utility Structures
    class Position {
        +x: float
        +y: float
        +Position(float, float)
        +operator+(Position): Position
        +distance(Position): float
    }

    class GridPosition {
        +row: int
        +col: int
        +CELL_SIZE: int
        +GridPosition(int, int)
        +toPixelPosition(): Position
        +fromPixelPosition(Position): GridPosition
    }

    class scoreEntry {
        +name: string
        +score: int
    }

    %% Tower Variants
    class Puncher {
        +Puncher()
        +attack(Enemy*)
        +upgrade()
    }

    class Freezer {
        +Freezer()
        +attack(Enemy*)
        +upgrade()
    }

    class Bomber {
        +Bomber()
        +attack(Enemy*)
        +upgrade()
    }

    class Base {
        +Base()
        +takeDamage(int)
    }

    %% Enums
    class EnemyType {
        <<enumeration>>
        PRIVATE
        CORPORAL
        SERGEANT
    }

    class GameState {
        <<enumeration>>
        MENU
        PLAYING
        PAUSED
        GAME_OVER
    }

    %% Relationships
    GameApplication --> UIController
    GameApplication --> EventController
    GameApplication --> WindowView

    UIController --> GameController
    UIController --> WaveManager
    UIController --> Economy
    UIController --> WindowView
    UIController --> EventController

    GameController --> Game
    GameController --> ScoreManager
    GameController --> WindowView
    GameController --> EventController

    Game --> WaveManager
    Game --> Economy
    Game --> Level
    Game --> Tower
    Game --> Enemy

    WaveManager --> Wave
    WaveManager --> Level
    WaveManager --> EnemyRenderer

    Wave --> Enemy
    Wave --> PathNode

    WindowView --> MapRenderer
    WindowView --> Level

    MapRenderer --> EnemyRenderer
    MapRenderer --> Level
    MapRenderer --> Wave

    Level --> PathNode
    Level --> Position

    PathNode --> GridPosition
    PathNode --> Position

    Enemy --> PathNode
    Enemy --> Position
    Enemy --> EnemyType

    Tower <|-- Puncher
    Tower <|-- Freezer
    Tower <|-- Bomber
    Tower <|-- Base

    ScoreManager --> scoreEntry

    SoundController --> SoundController : Singleton

    LevelLoader --> Level
    
  ```  
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