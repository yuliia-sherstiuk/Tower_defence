#include "../../../includes/logic/controllers/GameController.h"
#include "../../../includes/graphics/views/WindowView.h"
#include "../../../includes/logic/controllers/EventController.h"
#include <iostream>

GameController::GameController()
    : game(std::make_unique<Game>())
    , scoreManager(std::make_unique<ScoreManager>())
    , currentScore(0)
    , windowView(nullptr)
    , eventController(nullptr)
    , gameRunning(false)
{
    std::cout << "[DEBUG] GameController: Constructor called" << std::endl;
}

// Set the shared WindowView (called by UIController)
void GameController::setWindowView(WindowView* wv) {
    std::cout << "[DEBUG] GameController::setWindowView: WindowView set" << std::endl;
    windowView = wv;

    if (windowView) {
        windowView->setRegisterCallback([this](const std::string& username) {
            this->loginPlayer(username);
            std::cout << "[DEBUG] GameController: Username registered: " << username << std::endl;
        });
    }
}

// Set the shared EventController (called by UIController)
void GameController::setEventController(const std::shared_ptr<EventController>& eventCtrl) {
    std::cout << "[DEBUG] GameController::setEventController: EventController set" << std::endl;
    eventController = eventCtrl;

    // Only setup callbacks if we have both windowView and eventController
    if (eventController && windowView) {
        setupEventCallbacks();
    }
}

void GameController::setupEventCallbacks() {
    std::cout << "[DEBUG] GameController::setupEventCallbacks: Setting up event callbacks" << std::endl;
    if (!eventController) return;

    // Register callbacks with EventController
    //handle game-specific events here

    eventController->registerMouseClickCallback([this](sf::Vector2f pos, sf::Mouse::Button button) {
        if (button == sf::Mouse::Left && game->isRunning()) {
            // Handle game area clicks (tower placement logic should be in UIController)
            sf::FloatRect gameArea(20, 200, 1700, 1080);
            if (gameArea.contains(pos)) {
                std::cout << "[DEBUG] GameController: Game area clicked at (" << pos.x << ", " << pos.y << ")" << std::endl;
                // Specific game logic here
            }
        }
    });
}

void GameController::loginPlayer(const std::string& playerName) {
    currentPlayer = playerName;
    currentScore = 0;
    std::cout << "[DEBUG] GameController::loginPlayer: Player " << currentPlayer << " logged in!" << std::endl;
}

void GameController::startGame() {
    std::cout << "[DEBUG] GameController::startGame: Starting game" << std::endl;
    game->start();
    gameRunning = true;

    if (!currentPlayer.empty()) {
        std::cout << "[DEBUG] GameController: Game started for player: " << currentPlayer << std::endl;
    } else {
        std::cout << "[DEBUG] GameController: Game started (no player logged in - scores won't be saved)" << std::endl;
    }
}

void GameController::pauseGame() {
    std::cout << "[DEBUG] GameController::pauseGame: Pausing game" << std::endl;
    game->pause();
}

void GameController::playGame() {
    std::cout << "[DEBUG] GameController::playGame: Resuming game" << std::endl;
    game->play();
}

void GameController::quitGame() {
    std::cout << "[DEBUG] GameController::quitGame: Quitting game" << std::endl;
    game->quit();
    gameRunning = false;
}

void GameController::update(float deltaTime) {
    if (game->isRunning()) {
        game->update(deltaTime);

        // Update score and check game over conditions
        int baseHealth = Tower::getInstance().getBaseHealth();
        if (baseHealth <= 0) {
            std::cout << "[DEBUG] GameController::update: Base destroyed! Game over!" << std::endl;
            stopGame();
            addPlayerScore(currentScore);
        }
    }
}

void GameController::stopGame() {
    std::cout << "[DEBUG] GameController::stopGame: Stopping game for " << currentPlayer << std::endl;
    game->stop();
    gameRunning = false;
}

void GameController::handleTowerDamage(int damage) {
    Tower::getInstance().damageBase(damage);
    std::cout << "[DEBUG] GameController::handleTowerDamage: Base took " << damage << " damage. Remaining health: "
              << Tower::getInstance().getBaseHealth() << std::endl;
}

void GameController::addPlayerScore(int score) {
    currentScore += score;
    if (!currentPlayer.empty()) {
        scoreManager->addScore(currentPlayer, currentScore);
        std::cout << "[DEBUG] GameController::addPlayerScore: Score saved for " << currentPlayer << ": " << currentScore << std::endl;
    } else {
        std::cout << "[DEBUG] GameController::addPlayerScore: Score achieved: " << currentScore << " (not saved - no player logged in)" << std::endl;
    }
}

std::vector<scoreEntry> GameController::getHighScores() const {
    return scoreManager->getHighScores();
}

bool GameController::isGameRunning() const {
    return gameRunning && game->isRunning();
}

int GameController::getCurrentScore() const {
    return currentScore;
}

std::string GameController::getCurrentPlayer() const {
    return currentPlayer;
}

void GameController::setCurrentScore(int score) {
    std::cout << "[DEBUG] GameController::setCurrentScore: Score set to " << score << std::endl;
    currentScore = score;
}
