
#include "logic/models/Game.h"
#include "logic/models/ScoreManager.h"
#include <iostream>

Game::Game()
    : currentWave(0), isGameOver(false), playerHealth(100), playerResources(100)
{

}

void Game::startGame() {
    isGameOver = false;
    currentWave = 0;

    // Reset gold and account via Singleton
    ScoreManager::getInstance().resetGold(500);
    ScoreManager::getInstance().resetScore();  // <--- ADDED: points reset

    ScoreManager::getInstance().setTowerConfig("Archer", 100, 50, 0.6f);
    ScoreManager::getInstance().setTowerConfig("Cannon", 150, 70, 0.5f);

    setupInitialWaves();
    spawnWave();  // create the first wave
}

void Game::endGame(bool victory) {
    isGameOver = true;
    if (victory)
        std::cout << "Congratulations! You defended against all waves!" << std::endl;
    else
        std::cout << "Game Over! You lost." << std::endl;

    std::cout << "Final gold: " << ScoreManager::getInstance().getGold() << std::endl;
    std::cout << "Final score: " << ScoreManager::getInstance().getScore() << std::endl;  // <--- ДОБАВЛЕНО: вывод очков

    returnToMainMenu();
}

void Game::updateScore(int points) {
    ScoreManager::getInstance().addGold(points);
    ScoreManager::getInstance().addScore(points);
    playerResources += points / 2;
}

void Game::spawnWave() {
    if (currentWave < waves.size()) {
        std::cout << "Spawning Wave " << waves[currentWave].getWaveNumber() << std::endl;
        waves[currentWave].spawnEnemies();
        currentWave++;
    } else {
        endGame(true);
    }
}

std::vector<Enemy>& Game::getCurrentWaveEnemies() {
    int idx = currentWave - 1; // index of already spawned wave
    if (idx >= 0 && idx < (int)waves.size()) {
        return waves[idx].getEnemies();
    }
    static std::vector<Enemy> empty;
    return empty;
}

void Game::playerTakeDamage(int damage) {
    playerHealth -= damage;
    if (playerHealth <= 0) endGame(false);
}

bool Game::checkGameOver() const {
    return isGameOver;
}

void Game::update() {

}

void Game::setupInitialWaves() {
    waves.clear();
    for (int i = 1; i <= 7; ++i) {
        waves.emplace_back(i, "Difficulty " + std::to_string(i));
    }
}

void Game::displayFinalScore() const {
    std::cout << "Final gold: " << ScoreManager::getInstance().getGold() << std::endl;
    std::cout << "Final score: " << ScoreManager::getInstance().getScore() << std::endl;  // <--- ДОБАВЛЕНО: вывод очков
}

void Game::returnToMainMenu() const {
    std::cout << "Returning to main menu..." << std::endl;
}

void Game::endGame() {

    isGameOver = true;

    displayFinalScore();

    returnToMainMenu();
}









