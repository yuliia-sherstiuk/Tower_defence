//
// Created by chris on 04/06/2025.
//
#ifndef WAVE_H
#define WAVE_H

#include <vector>
#include <memory>
#include <string>

// Forward declaration
class Enemy;
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

public:
    Wave(int number, std::string difficulty, const std::shared_ptr<PathNode>& spawn);

    //Getters
    int getWaveNumber() const { return waveNumber; }
    const std::string& getDifficulty() const { return difficulty; }
    bool isWaveComplete() const { return isComplete; }
    const std::vector<std::shared_ptr<Enemy>>& getEnemies() const { return enemies; }

    //Methods
    void spawnEnemies(float deltaTime);
    void update(float deltaTime);
    void nextWave();

    //Handling enemies
    void removeDeadEnemies();
};

#endif //WAVE_H