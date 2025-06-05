// Защита от повторного включения заголовочного файла
#ifndef GAME_H
#define GAME_H


#include <vector>

#include "Wave.h"
#include "ScoreManager.h"


class Game {
private:

    std::vector<Wave> waves;

    ScoreManager scoreManager;

    int currentWave;

    bool isGameOver;

public:

    Game();

    void startGame();

    void endGame();

    void updateScore(int points);

private:

    void setupInitialWaves();

    void displayFinalScore();

    void returnToMainMenu();
};


#endif // GAME_H