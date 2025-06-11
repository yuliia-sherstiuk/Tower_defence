#include "Game.h"
#include "controllers/WaveManager.h"
#include "utils/Level.h"
#include "models/Tower.h"
#include <iostream>

Game::Game()
    : running(false)
{
    waveManager = std::make_unique<WaveManager>();
    currentLevel = std::make_shared<Level>(1); 
    waveManager->setLevel(currentLevel);
}

void Game::start() {
    running = true;
    std::cout << "Game started!\n";
    waveManager->initializeWave(currentLevel->getSpawnPoint());
}

void Game::update(float deltaTime) {
    if (!running) return;

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
    std::cout << "Game stopped.\n";
}

bool Game::isRunning() const {
    return running;
}
