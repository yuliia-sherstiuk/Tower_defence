#include "../../../includes/logic/models/Game.h"
#include "../../../includes/logic/controllers/WaveManager.h"
#include "../../../includes/utils/Level.h"
#include "../../../includes/logic/models/Tower.h"
#include <iostream>

Game::Game()
    : running(false)
    , paused(false)
{
    waveManager = std::make_unique<WaveManager>();
    currentLevel = std::make_shared<Level>(1);
    waveManager->setLevel(currentLevel);
}

void Game::start() {
    running = true;
    paused = false;
    std::cout << "Game started!\n";
    waveManager->initializeWave(currentLevel->getSpawnPoint());
}

void Game::pause() {
    if (running && !paused) {
        paused = true;
        std::cout << "Game paused.\n";
    }
}

void Game::play() {
    if (running && paused) {
        paused = false;
        std::cout << "Game resumed.\n";
    }
}

void Game::quit() {
    running = false;
    paused = false;
    std::cout << "Quit!\n";
}

void Game::update(float deltaTime) {
    if (!running || paused) return;

    waveManager->update(deltaTime);

    if (waveManager->isWaveComplete()) {
        waveManager->startNewWave(currentLevel->getSpawnPoint());
    }

    if (Tower::getInstance().getBaseHealth() <= 0) {
        std::cout << "Base destroyed. Game over!\n";
        stop();
    }
}

void Game::stop() {
    running = false;
    paused = false;
    std::cout << "Game stopped.\n";
}

bool Game::isRunning() const {
    return running;
}

bool Game::isPaused() const {
    return paused;
}