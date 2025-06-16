#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>
#include "../controllers/WaveManager.h"
#include "../../utils/Level.h"
#include "Tower.h"
#include "Economy.h"

class Game {
public:
    Game();
    ~Game();

    // Lifecycle management
    void start();
    void pause();
    void play();
    void quit();
    void stop();

    // Game loop
    void update(float deltaTime);

    // State queries
    bool isRunning() const;
    bool isPaused() const;
    float getGameTime() const;
    
    // Game state management
    void resetGame();
    bool isGameOver() const;
    bool isGameWon() const;

    // Game objects access (needed by GameController)
    const std::vector<std::shared_ptr<Enemy>>& getEnemies() const;
    const std::vector<std::shared_ptr<Tower>>& getTowers() const;
    std::shared_ptr<Level> getCurrentLevel() const;
    
    // Game actions (needed by UIController)
    bool placeTower(const std::string& towerType, const Position& position);
    void upgradeTower(std::shared_ptr<Tower> tower);
    void sellTower(std::shared_ptr<Tower> tower);
    
    // Game stats (needed by GameController and UIController)
    int getBaseHealth() const;
    int getCurrentScore() const;
    int getCurrentWave() const;
    int getCurrentMoney() const;

private:
    // Core game state
    bool running;
    bool paused;
    bool gameOver;
    float gameTime;
    int baseHealth;
    int currentScore;
    
    // Game managers
    std::unique_ptr<WaveManager> waveManager;
    std::unique_ptr<Economy> economy;
    
    // Game world
    std::shared_ptr<Level> currentLevel;
    std::vector<std::shared_ptr<Tower>> towers;
    
    // Helper methods
    void initializeGameState();
    void checkGameConditions();
    bool isValidTowerPosition(const Position& position) const;
    void handleEnemyKilled(std::shared_ptr<Enemy> enemy);
    void addScore(int points);
    void damageBase(int damage);
};

#endif // GAME_H

