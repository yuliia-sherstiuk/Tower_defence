//
// Created by chris on 04/06/2025.
//

#ifndef WAVE_H
#define WAVE_H

#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include "../models/Enemy.h"

// Forward declarations
class PathNode;

class Wave {
private:
    std::vector<std::shared_ptr<Enemy>> enemies;
    int waveNumber;
    std::string difficulty;
    std::shared_ptr<PathNode> spawnNode;
    bool isComplete;

    int enemiesToSpawn;
    float spawnTimer;
    float spawnInterval;

    EnemyType getDifficultyType() const;

public:
    Wave(int number, std::string difficulty, const std::shared_ptr<PathNode>& spawn);

    // Getters
    int getWaveNumber() const { return waveNumber; }
    const std::string& getDifficulty() const { return difficulty; }
    bool isWaveComplete() const { return isComplete; }
    const std::vector<std::shared_ptr<Enemy>>& getEnemies() const { return enemies; }

    //Enemy state
    bool areAllEnemiesDead() const {
        return std::all_of(enemies.begin(), enemies.end(),
            [](const auto& enemy) { return enemy->isDead(); });
    }

    // Getters for Ui
    int getEnemiesSpawned() const { return (5 + waveNumber * 2) - enemiesToSpawn; }
    int getTotalEnemiesInWave() const { return 5 + waveNumber * 2; }
    int getEnemiesRemaining() const { return enemiesToSpawn; }
    float getSpawnProgress() const {
        int totalEnemies = getTotalEnemiesInWave();
        if (totalEnemies == 0) return 0.0f;
        return static_cast<float>(getEnemiesSpawned()) / static_cast<float>(totalEnemies);
    }

    // Timing infos
    float getSpawnTimer() const { return spawnTimer; }
    float getSpawnInterval() const { return spawnInterval; }
    float getTimeUntilNextSpawn() const { return spawnInterval - spawnTimer; }

    void setDifficulty(const std::string& diff) { difficulty = diff; }

    // Methods
    void spawnEnemies(float deltaTime);
    void update(float deltaTime);
    void nextWave();
    void removeDeadEnemies();
};

#endif //WAVE_H