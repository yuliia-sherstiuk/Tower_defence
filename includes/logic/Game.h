
#ifndef GAME_H
#define GAME_H

#include <vector>
#include "logic/models/Wave.h"
#include "logic/models/ScoreManager.h"
#include "logic/models/Enemy.h"

class Game {
private:
    std::vector<Wave> waves;
    //ScoreManager scoreManager;
    int currentWave;
    bool isGameOver;
    int playerHealth;
    int playerResources;

    void setupInitialWaves();
    void displayFinalScore() const;
    void returnToMainMenu() const;

public:
    Game();
    void startGame();                 // Initialization of the game and the first wave
    void endGame(bool victory);
    void updateScore(int points);
    void spawnWave();                  // Spawn the current wave and move to the next one
    void playerTakeDamage(int damage);
    bool checkGameOver() const;
    void update();                     // Update logic (optional)
    std::vector<Enemy>& getCurrentWaveEnemies();
};

#endif // GAME_H
