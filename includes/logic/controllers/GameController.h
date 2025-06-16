//
// Created by chris on 14/06/2025.
//

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../models/Game.h"
#include "../models/Tower.h"
#include "../models/ScoreManager.h"
#include "../models/scoreEntry.h"
#include <memory>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

// Forward declarations to avoid circular dependencies
class WindowView;
class EventController;

class GameController {
public:
    GameController();

    // Component connection methods (called by UIController)
    void setWindowView(WindowView* windowView);
    void setEventController(const std::shared_ptr<EventController>& eventCtrl);

    // Player management
    void loginPlayer(const std::string& playerName);
    std::string getCurrentPlayer() const;

    // Game control
    void startGame();
    void pauseGame();
    void playGame();
    void stopGame();
    void quitGame();

    // Game logic and updates
    void update(float deltaTime);
    void handleTowerDamage(int damage);

    // Score management
    void addPlayerScore(int score);
    void setCurrentScore(int score);
    int getCurrentScore() const;
    std::vector<scoreEntry> getHighScores() const;

    // Game state queries
    bool isGameRunning() const;

private:
    // Core game components
    std::unique_ptr<Game> game;
    std::unique_ptr<ScoreManager> scoreManager;

    // Player and score tracking
    std::string currentPlayer;
    int currentScore;

    // Shared components (set by UIController)
    WindowView* windowView;
    std::shared_ptr<EventController> eventController;

    // Game state
    bool gameRunning;

    // Private setup methods
    void setupEventCallbacks();
};

#endif // GAMECONTROLLER_H
