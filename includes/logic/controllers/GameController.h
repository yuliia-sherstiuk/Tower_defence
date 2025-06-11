#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "WaveManager.h"
#include "Tower.h"
#include "ScoreManager.h"
#include "scoreEntry.h"

class GameController {
public:
    GameController();

    void loginPlayer(const std::string& playerName);
    void startGame();
    void update(float deltaTime);
    void stopGame();
    void handleTowerDamage(int damage);
    void addPlayerScore(int score);
    std::vector<scoreEntry> getHighScores() const;

    bool isGameRunning() const;

    void runGameLoop();  // новый метод

private:
    std::unique_ptr<Game> game;
    std::unique_ptr<ScoreManager> scoreManager;
    std::string currentPlayer;
    int currentScore;

    sf::RenderWindow window;  // окно
};

#endif // GAMECONTROLLER_HPP
