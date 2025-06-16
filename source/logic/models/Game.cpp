#include "../../../includes/logic/models/Game.h"
#include "../../../includes/logic/controllers/WaveManager.h"
#include "../../../includes/utils/Level.h"
#include "../../../includes/logic/models/Tower.h"
#include "../../../includes/logic/models/Enemy.h"
#include "../../includes/logic/models/Economy.h"
#include "../utils/GridPosition.h"
#include "../utils/LevelLoader.h"
#include "../graphics/views/MapRenderer.h"
#include <iostream>
#include <algorithm>

Game::Game()
    : running(false)
    , paused(false)
    , gameOver(false)
    , gameTime(0.0f)
    , baseHealth(100)
    , currentScore(0)
{
    waveManager = std::make_unique<WaveManager>();
    economy = std::make_unique<Economy>();
    currentLevel = std::make_shared<Level>(1);
    waveManager->setLevel(currentLevel);
    std::cout << "[DEBUG] Game: Constructor completed" << std::endl;
}

Game::~Game() {
    quit();
    std::cout << "[DEBUG] Game: Destructor completed" << std::endl;
}

//Start Game
void Game::start() {
    if (!running) {
        std::cout << "[DEBUG] Game::start: Initializing new game" << std::endl;

        running = true;
        paused = false;
        gameOver = false;
        gameTime = 0.0f;
        // Reset game state
        resetGame();
        // Initialize game systems
        initializeGameState();
        // Start first wave
        waveManager->initializeWave(currentLevel->getSpawnPoint());
        std::cout << "[DEBUG] Game: Started successfully" << std::endl;
    }
}

//Pause game
void Game::pause() {
    if (running && !paused && !gameOver) {
        std::cout << "[DEBUG] Game::pause: Game paused" << std::endl;
        paused = true;
    }
}

//Play Game
void Game::play() {
    if (running && paused && !gameOver) {
        std::cout << "[DEBUG] Game::play: Game resumed" << std::endl;
        paused = false;
    }
}

//Quit game
void Game::quit() {
    if (running) {
        std::cout << "[DEBUG] Game::quit: Cleaning up game resources" << std::endl;
        running = false;
        paused = false;
        // Clear all resources
        towers.clear();
        std::cout << "[DEBUG] Game: Quit completed" << std::endl;
    }
}

//Stop game
void Game::stop() {
    if (running) {
        std::cout << "[DEBUG] Game::stop: Stopping game" << std::endl;
        running = false;
        paused = false;
        gameOver = true;
    }
}

//Update
void Game::update(float deltaTime) {
    if (!running || paused || gameOver) {
        return;
    }
    gameTime += deltaTime;
    // Update wave manager
    waveManager->update(deltaTime);
    // Start new wave if needed
    if (waveManager->isWaveComplete() && waveManager->canStartNextWave()) {
        waveManager->startNewWave(currentLevel->getSpawnPoint());
    }
    // Check win/lose conditions
    checkGameConditions();
}

void Game::resetGame() {
    std::cout << "[DEBUG] Game: Resetting game state" << std::endl;

    gameTime = 0.0f;
    baseHealth = 100;
    currentScore = 0;
    gameOver = false;

    towers.clear();

    // Reset economy
    if (economy) {
        economy->goldAmount = 0;
    }
    // Reset wave manager
    if (waveManager) {
        waveManager->setLevel(currentLevel);
    }
}

// State queries
bool Game::isRunning() const {
    return running && !paused;
}

bool Game::isPaused() const {
    return paused;
}

float Game::getGameTime() const {
    return gameTime;
}

bool Game::isGameOver() const {
    return gameOver || baseHealth <= 0;
}

bool Game::isGameWon() const {
    return Tower::getInstance().getBaseHealth() > 0 && waveManager && waveManager->isWaveComplete();
}

// Game objects access
const std::vector<std::shared_ptr<Enemy>>& Game::getEnemies() const {
    return waveManager->getEnemies();
}

const std::vector<std::shared_ptr<Tower>>& Game::getTowers() const {
    return towers;
}

std::shared_ptr<Level> Game::getCurrentLevel() const {
    return currentLevel;
}

// Game actions
bool Game::placeTower(const std::string& towerType, const Position& position) {
    if (!isValidTowerPosition(position)) {
        std::cout << "[DEBUG] Game::placeTower: Invalid position" << std::endl;
        return false;
    }

    // Create tower using Tower factory
    Tower* newTower = Tower::getInstance().createTower(towerType);
    if (!newTower) {
        std::cout << "[DEBUG] Game::placeTower: Failed to create tower" << std::endl;
        return false;
    }
    // Check if player has enough money
    if (!economy->buyTower(newTower)) {
        std::cout << "[DEBUG] Game::placeTower: Cannot buy tower (not enough money or other reason)" << std::endl;
        delete newTower;
        return false;
    }
    // Tower already purchased by buyTower(), just add to vector
    towers.push_back(std::shared_ptr<Tower>(newTower));
    std::cout << "[DEBUG] Game: Tower placed at (" << position.x << ", " << position.y << ")" << std::endl;
    return true;
}

//upgrade tower
void Game::upgradeTower(std::shared_ptr<Tower> tower) {
    if (tower) {
        // Calculate upgrade cost
        int upgradeCost = tower->price * tower->level;

        if (economy->goldAmount >= upgradeCost) {
            economy->goldAmount -= upgradeCost;
            tower->upgrade();
            std::cout << "[DEBUG] Game: Tower upgraded" << std::endl;
        } else {
            std::cout << "[DEBUG] Game: Not enough money to upgrade tower" << std::endl;
        }
    }
}

//Sell tower
void Game::sellTower(std::shared_ptr<Tower> tower) {
    if (tower) {
        // 1/2 the price
        int sellValue = tower->price / 2;
        economy->goldAmount += sellValue;

        towers.erase(std::remove(towers.begin(), towers.end(), tower), towers.end());
        std::cout << "[DEBUG] Game: Tower sold for " << sellValue << " gold" << std::endl;
    }
}

// Game stats
int Game::getBaseHealth() const {
    return Tower::getInstance().getBaseHealth();
}

int Game::getCurrentScore() const {
    return currentScore;
}

int Game::getCurrentWave() const {
    return waveManager->getCurrentWaveNumber();
}

int Game::getCurrentMoney() const {
    return economy ? economy->goldAmount : 0;
}

//Init game state
void Game::initializeGameState() {
    std::cout << "[DEBUG] Game: Initializing game state" << std::endl;
    // Initialize economy
    if (economy) {
        economy->goldAmount = 100; // Starting money
    }
}

//Check game conditions
void Game::checkGameConditions() {
    // Check lose condition using Tower
    if (Tower::getInstance().getBaseHealth() <= 0) {
        std::cout << "[DEBUG] Game: Base destroyed - Game Over!" << std::endl;
        gameOver = true;
        stop();
        return;
    }
    // Check win condition
    if (isGameWon()) {
        std::cout << "[DEBUG] Game: Victory achieved!" << std::endl;
        gameOver = true;
        stop();
    }
}

//Verify if tower position is valid
bool Game::isValidTowerPosition(const Position& position) const {
    if (!currentLevel) return false;
    // Use MapRenderer
    if (position.x < MapRenderer::GAME_FIELD_X ||
        position.y < MapRenderer::GAME_FIELD_Y ||
        position.x >= MapRenderer::GAME_FIELD_X + 28 * MapRenderer::CELL_SIZE ||
        position.y >= MapRenderer::GAME_FIELD_Y + 18 * MapRenderer::CELL_SIZE) {
        return false;
        }
    return currentLevel->isValidTowerPosition(position);
}

//Handle enemy killed
void Game::handleEnemyKilled(std::shared_ptr<Enemy> enemy) {
    if (enemy) {
        int reward = enemy->reward;
        economy->goldAmount += reward;
        //Simple score based on reward
        int scoreValue = reward * 3;  // 3 gold reward
        addScore(scoreValue);
        std::cout << "[DEBUG] Game: Enemy killed. Reward: " << reward << std::endl;
    }
}

//Add score
void Game::addScore(int points) {
    currentScore += points;
    std::cout << "[DEBUG] Game: Score added. Current score: " << currentScore << std::endl;
}

//Damage Base
void Game::damageBase(int damage) {
    // Use existing Tower singleton for base damage
    Tower::getInstance().damageBase(damage);
    std::cout << "[DEBUG] Game: Base damaged by " << damage << std::endl;
}