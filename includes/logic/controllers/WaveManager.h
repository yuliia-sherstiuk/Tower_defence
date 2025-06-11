// Created by chris on 08/06/2025.
//


#ifndef WAVE_MANAGER_H
#define WAVE_MANAGER_H

#include <memory>
#include <vector>
#include <string>
#include "models/Wave.h"
#include "utils/PathNode.h"
#include "utils/Level.h"
#include "models/Enemy.h"

class WaveManager {
private:
    std::shared_ptr<Wave> currentWave;
    std::shared_ptr<Level> currentLevel;
    float waveTimer;
    bool isWaveManualStart;
    std::string currentDifficulty;
    static constexpr float WAVE_DELAY = 30.0f; //delay wave 30 sec

    // Helper method to get a valid spawn point
    std::shared_ptr<PathNode> getValidSpawnPoint() const;

public:
    WaveManager();

    //Wave manager action
    void setLevel(const std::shared_ptr<Level>& level) { currentLevel = level; }
    void startNewWave(const std::shared_ptr<PathNode>& spawnPoint);
    void update(float deltaTime);
    void forceStartWave();

    //Wave state verification
    bool isWaveComplete() const { return currentWave && currentWave->isWaveComplete(); }
    bool canStartNextWave() const { return waveTimer >= WAVE_DELAY; }
    float getWaveTimer() const { return waveTimer; }

    //Difficulty
    void setDifficulty(const std::string& difficulty);
    std::string getDifficulty() const { return currentDifficulty; }

    //init wave
    void initializeWave(const std::shared_ptr<PathNode>& spawnPoint);

    //Getters
    const std::vector<std::shared_ptr<Enemy>>& getEnemies() const;
    int getCurrentWaveNumber() const { return currentWave ? currentWave->getWaveNumber() : 0; }
};

#endif //WAVE_MANAGER_H //


