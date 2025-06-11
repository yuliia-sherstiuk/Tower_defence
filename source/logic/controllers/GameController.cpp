#include "GameController.h"
#include <iostream>

GameController::GameController() 
    : game(std::make_unique<Game>()),
      scoreManager(std::make_unique<ScoreManager>()),
      currentScore(0),
      window(sf::VideoMode(800, 600), "Tower Defense")  
{
    window.setFramerateLimit(60);
}

void GameController::loginPlayer(const std::string& playerName) {
    currentPlayer = playerName;
    currentScore = 0;
    std::cout << "Player " << currentPlayer << " logged in!" << std::endl;
}

void GameController::startGame() {
    if (!currentPlayer.empty()) {
        game->start();
        std::cout << "Game started for " << currentPlayer << "!" << std::endl;
    } else {
        std::cerr << "No player logged in. Please login first." << std::endl;
    }
}

void GameController::update(float deltaTime) {
    if (game->isRunning()) {
        game->update(deltaTime);

        // Read the following words:
        int baseHealth = Tower::getInstance().getBaseHealth();
        if (baseHealth <= 0) {
            std::cout << "Base destroyed! Game over!" << std::endl;
            stopGame();
            addPlayerScore(currentScore);
        }

        
    }
}

void GameController::stopGame() {
    game->stop();
    std::cout << "Game stopped for " << currentPlayer << "." << std::endl;
}

void GameController::handleTowerDamage(int damage) {
    Tower::getInstance().damageBase(damage);
    std::cout << "Base took " << damage << " damage. Remaining health: "
              << Tower::getInstance().getBaseHealth() << std::endl;
}

void GameController::addPlayerScore(int score) {
    currentScore += score;
    scoreManager->addScore(currentPlayer, currentScore);
    std::cout << "Score updated: " << currentScore << std::endl;
}

std::vector<scoreEntry> GameController::getHighScores() const {
    return scoreManager->getHighScores();
}

bool GameController::isGameRunning() const {
    return game->isRunning();
}

void GameController::runGameLoop() {
    sf::Clock clock;

    loginPlayer("Player1");
    startGame();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        update(deltaTime);

        window.clear(sf::Color::Black);

       // All you need to know about the games (enemy tower)


        window.display();
    }

    stopGame();
}
