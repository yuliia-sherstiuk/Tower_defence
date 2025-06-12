#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H


#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "../models/Game.h"
#include "../controllers/WaveManager.h"
#include "../models/Tower.h"
#include "../models/ScoreManager.h"
#include "../models/scoreEntry.h"

// Main controller class that manages the overall game flow.
class GameController {
public:
    // Constructor: initializes the game, score manager, and the window.
    GameController();

    // Logs in a player with the given name.
    void loginPlayer(const std::string& playerName);

    // Starts the game if a player is logged in.
    void startGame();

    void pauseGame();
    void playGame();
    void quitGame();


    // Updates the game logic every frame.
    void update(float deltaTime);

    // Stops the game and performs cleanup.
    void stopGame();

    // Applies damage to the tower base.
    void handleTowerDamage(int damage);

    // Adds score points to the current player.
    void addPlayerScore(int score);

    // Returns the list of high scores.
    std::vector<scoreEntry> getHighScores() const;

    // Checks if the game is currently running.
    bool isGameRunning() const;

    // Runs the main game loop: processes events, updates game, renders graphics.
    void runGameLoop();

private:
    std::unique_ptr<Game> game;               // Core game logic.
    std::unique_ptr<ScoreManager> scoreManager; // Manages the player scores.
    std::string currentPlayer;                // Current player's name.
    int currentScore;                         // Current player's score.

    sf::RenderWindow window;                  // Main SFML window for rendering.
};

#endif // GAMECONTROLLER_H