//
// Created by chris on 09/06/2025.
//
#include "../../../includes/logic/controllers/WaveManager.h"

WaveManager::WaveManager()
    : waveTimer(0.0f)
    , isWaveManualStart(false)
    , currentDifficulty("private")
{
}

void WaveManager::startNewWave(const std::shared_ptr<PathNode>& spawnPoint) {
    if (currentWave) {
        currentWave = std::make_shared<Wave>(
            currentWave->getWaveNumber() + 1,
            currentDifficulty,
            spawnPoint
        );
    } else {
        // first wave
        currentWave = std::make_shared<Wave>(1, currentDifficulty, spawnPoint);
    }

    isWaveManualStart = false;
}

void WaveManager::update(float deltaTime) {
    waveTimer += deltaTime;

    if (currentWave) {
        currentWave->update(deltaTime);

        // verify if next wave can ru
        if (currentWave->isWaveComplete()) {
            if (isWaveManualStart) {
                //  manual start
                std::shared_ptr<PathNode> spawnPoint = getValidSpawnPoint();
                if (spawnPoint) {
                    startNewWave(spawnPoint);
                    waveTimer = 0.0f; // Reset timer after manual start
                }
            } else if (waveTimer >= WAVE_DELAY) {
                // auto run after delay
                std::shared_ptr<PathNode> spawnPoint = getValidSpawnPoint();
                if (spawnPoint) {
                    startNewWave(spawnPoint);
                    waveTimer = 0.0f; // Reset timer seulement après démarrage auto
                }
            }
        }
    }
}

void WaveManager::forceStartWave() {

    if (currentWave) {

        if (currentWave->isWaveComplete()) {
            isWaveManualStart = true;
            std::shared_ptr<PathNode> spawnPoint = getValidSpawnPoint();
            if (spawnPoint) {
                startNewWave(spawnPoint);
                waveTimer = 0.0f;
            }
        }

        else {
            isWaveManualStart = true;
        }
    }

    else {
        std::shared_ptr<PathNode> spawnPoint = getValidSpawnPoint();
        if (spawnPoint) {
            currentWave = std::make_shared<Wave>(1, currentDifficulty, spawnPoint);
            isWaveManualStart = true;
            waveTimer = 0.0f;
        }
    }
}

void WaveManager::setDifficulty(const std::string& difficulty) {
    currentDifficulty = difficulty;
    if(currentWave) {
        currentWave->setDifficulty(difficulty);
    }
}

void WaveManager::initializeWave(const std::shared_ptr<PathNode>& spawnPoint) {
    currentWave = std::make_shared<Wave>(1, currentDifficulty, spawnPoint);
    waveTimer = 0.0f;
    isWaveManualStart = false;
}

std::shared_ptr<PathNode> WaveManager::getValidSpawnPoint() const {
    if (currentLevel) {
        return currentLevel->getSpawnPoint();
    }

    if (currentWave && !currentWave->getEnemies().empty()) {

        return std::make_shared<PathNode>(0, "spawn", GridPosition(0, 0));
    }

    return std::make_shared<PathNode>(0, "spawn", GridPosition(0, 0));
}

const std::vector<std::shared_ptr<Enemy>>& WaveManager::getEnemies() const {
    static const std::vector<std::shared_ptr<Enemy>> emptyVector;
    return currentWave ? currentWave->getEnemies() : emptyVector;
}