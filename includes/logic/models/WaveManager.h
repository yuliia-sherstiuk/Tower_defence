// Created by chris on 08/06/2025.
//

#ifndef WAVE_MANAGER_H
#define WAVE_MANAGER_H

#include <memory>
#include <vector>
#include <string>
#include "Wave.h"
#include "PathNode.h"
#include "Level.h"
#include "Enemy.h"

class WaveManager {
private:
    std::shared_ptr<Wave> currentWave;
    std::shared_ptr<Level> currentLevel;
    float waveTimer;
    bool isWaveManualStart;
    std::string currentDifficulty;
    static constexpr float WAVE_DELAY = 30.0f;


    std::shared_ptr<PathNode> getValidSpawnPoint() const;

public:
    WaveManager();

    void setLevel(const std::shared_ptr<Level>& level) { currentLevel = level; }
    void startNewWave(const std::shared_ptr<PathNode>& spawnPoint);
    void update(float deltaTime);
    void forceStartWave();

    bool isWaveComplete() const { return currentWave && currentWave->isWaveComplete(); }
    bool canStartNextWave() const { return waveTimer >= WAVE_DELAY; }
    float getWaveTimer() const { return waveTimer; }

    void setDifficulty(const std::string& difficulty);
    std::string getDifficulty() const { return currentDifficulty; }

    void initializeWave(const std::shared_ptr<PathNode>& spawnPoint);
    const std::vector<std::shared_ptr<Enemy>>& getEnemies() const;
    int getCurrentWaveNumber() const { return currentWave ? currentWave->getWaveNumber() : 0; }
};

#endif //WAVE_MANAGER_H //

