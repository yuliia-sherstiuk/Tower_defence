#include "controllers/GameController.h"
#include "models/Tower.h"
#include <iostream>

// Constructor: Initializes the game and the window.
GameController::GameController() 
    : game(std::make_unique<Game>()),
      scoreManager(std::make_unique<ScoreManager>()),
      currentScore(0),
      window(sf::VideoMode(800, 600), "Tower Defense")  
{
    window.setFramerateLimit(60);
}


// Logs in the player and resets the current score.
void GameController::loginPlayer(const std::string& playerName) {
    currentPlayer = playerName;
    currentScore = 0;
    std::cout << "Player " << currentPlayer << " logged in!" << std::endl;
}


// Starts the game if a player is logged in.
void GameController::startGame() {
    if (!currentPlayer.empty()) {
        game->start();
        std::cout << "Game started for " << currentPlayer << "!" << std::endl;
    } else {
        std::cerr << "No player logged in. Please login first." << std::endl;
    }
}


// Updates the game state (called every frame).
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


// Stops the game
void GameController::stopGame() {
    game->stop();
    std::cout << "Game stopped for " << currentPlayer << "." << std::endl;
}

// Applies damage to the tower's base and logs the new health.
void GameController::handleTowerDamage(int damage) {
    Tower::getInstance().damageBase(damage);
    std::cout << "Base took " << damage << " damage. Remaining health: "
              << Tower::getInstance().getBaseHealth() << std::endl;
}

// Adds the current score to the player's total and updates the leaderboard.
void GameController::addPlayerScore(int score) {
    currentScore += score;
    scoreManager->addScore(currentPlayer, currentScore);
    std::cout << "Score updated: " << currentScore << std::endl;
}
// Returns the list of high scores.
std::vector<scoreEntry> GameController::getHighScores() const {
    return scoreManager->getHighScores();
}

// Checks if the game is currently running.
bool GameController::isGameRunning() const {
    return game->isRunning();
}

// Runs the main game loop: handles events, updates, and rendering.
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

       // Render game objects here (e.g. tower, enemies,


        window.display();
    }

    stopGame();
}
