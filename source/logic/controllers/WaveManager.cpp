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

//Start new wave
void WaveManager::startNewWave(const std::shared_ptr<PathNode>& spawnPoint) {
    if (currentWave) {
        currentWave = std::make_shared<Wave>(
            currentWave->getWaveNumber() + 1,
            currentDifficulty,
            spawnPoint
        );
    } else {
        // current wave
        currentWave = std::make_shared<Wave>(1, currentDifficulty, spawnPoint);
    }

    isWaveManualStart = false;
}

//Update Wave
void WaveManager::update(float deltaTime) {
    waveTimer += deltaTime;

    if (currentWave) {
        currentWave->update(deltaTime);

        // Verify if we can start a new wave
        if (currentWave->isWaveComplete()) {
            if (isWaveManualStart) {
                // Manual start immediate
                std::shared_ptr<PathNode> spawnPoint = getValidSpawnPoint();
                if (spawnPoint) {
                    startNewWave(spawnPoint);
                    waveTimer = 0.0f; // Reset timer only after manual start
                }
            } else if (waveTimer >= WAVE_DELAY) {
                //Automatic start after delay
                std::shared_ptr<PathNode> spawnPoint = getValidSpawnPoint();
                if (spawnPoint) {
                    startNewWave(spawnPoint);
                    waveTimer = 0.0f; // Reset timer only after automatic start
                }
            }
        }
    }
}

// Force wave to start
void WaveManager::forceStartWave() {
    // Allow to start even if the wave is not completed
    if (currentWave) {
        // if a new wave is completed create another one
        if (currentWave->isWaveComplete()) {
            isWaveManualStart = true;
            std::shared_ptr<PathNode> spawnPoint = getValidSpawnPoint();
            if (spawnPoint) {
                startNewWave(spawnPoint);
                waveTimer = 0.0f;
            }
        }
        // if wave is not completed allow to force it
        else {
            // Force the enemy spawn if left or speed
            // For debug we can temporally mark wave as complete
            isWaveManualStart = true;
        }
    }
    // if no wave create one
    else {
        std::shared_ptr<PathNode> spawnPoint = getValidSpawnPoint();
        if (spawnPoint) {
            currentWave = std::make_shared<Wave>(1, currentDifficulty, spawnPoint);
            isWaveManualStart = true;
            waveTimer = 0.0f;
        }
    }
}

//Set difficulty
void WaveManager::setDifficulty(const std::string& difficulty) {
    currentDifficulty = difficulty;
    if(currentWave) {
        currentWave->setDifficulty(difficulty);
    }
}

//init wave
void WaveManager::initializeWave(const std::shared_ptr<PathNode>& spawnPoint) {
    currentWave = std::make_shared<Wave>(1, currentDifficulty, spawnPoint);
    waveTimer = 0.0f;
    isWaveManualStart = false;
}

//Get valid spawn point
std::shared_ptr<PathNode> WaveManager::getValidSpawnPoint() const {
    if (currentLevel) {
        return currentLevel->getSpawnPoint();
    }

    // if no level, use the spawn point of the current wave
    if (currentWave && !currentWave->getEnemies().empty()) {
        // create a default spawn point
        return std::make_shared<PathNode>(0, "spawn", GridPosition(0, 0));
    }

    // Fallback: create a default spawn point for tests
    return std::make_shared<PathNode>(0, "spawn", GridPosition(0, 0));
}

//Get enemies
const std::vector<std::shared_ptr<Enemy>>& WaveManager::getEnemies() const {
    static const std::vector<std::shared_ptr<Enemy>> emptyVector;
    return currentWave ? currentWave->getEnemies() : emptyVector;
}