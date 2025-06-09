// Created by chris on 04/06/2025.
//
#include "Wave.h"
#include "Enemy.h"
#include "Economy.h"
#include <algorithm>

EnemyType Wave::getDifficultyType() const {
    if (difficulty == "corporal") return EnemyType::CORPORAL;
    if (difficulty == "sergeant") return EnemyType::SERGEANT;
    return EnemyType::PRIVATE;
}

Wave::Wave(int number, std::string diff, const std::shared_ptr<PathNode>& spawn)
    : waveNumber(number), difficulty(std::move(diff)), spawnNode(spawn),
      isComplete(false), enemiesToSpawn(5 + number * 2),
      spawnTimer(0.0f), spawnInterval(1.0f) {
}

void Wave::spawnEnemies(float deltaTime) {
    if (enemiesToSpawn <= 0) return;

    spawnTimer += deltaTime;
    if (spawnTimer >= spawnInterval) {
        // Base stats
        int health = static_cast<int>(100 + waveNumber * 10);
        float speed = 50.0f + static_cast<float>(waveNumber * 2);
        int damage = static_cast<int>(1 + waveNumber / 2);

        int enemiesSpawned = (5 + waveNumber * 2) - enemiesToSpawn;

        // Determine enemy type based on difficulty and spawn position
        EnemyType enemyType = EnemyType::PRIVATE;

        if (difficulty == "corporal" || difficulty == "sergeant") {
            // Spawn corporal every 5 ennemies (0, 5, 10, 15...)
            if (enemiesSpawned % 5 == 0 && enemiesSpawned > 0) {
                enemyType = EnemyType::CORPORAL;
            }
        }

        if (difficulty == "sergeant") {
            // Spawn Sergeant every 10 enemies (10, 20, 30...)
            if (enemiesSpawned % 10 == 0 && enemiesSpawned > 0) {
                enemyType = EnemyType::SERGEANT;
            }
        }

        auto enemy = std::make_shared<Enemy>(
            enemies.size(), health, speed, damage, spawnNode, enemyType
        );
        enemies.push_back(enemy);

        enemiesToSpawn--;
        spawnTimer = 0.0f;
    }
}

void Wave::update(float deltaTime) {
    spawnEnemies(deltaTime);

    for (auto& enemy : enemies) {
        enemy->move(deltaTime);
    }

    removeDeadEnemies();

    isComplete = (enemiesToSpawn == 0 && enemies.empty());
}

void Wave::nextWave() {
    waveNumber++;
    enemiesToSpawn = 5 + waveNumber * 2;
    isComplete = false;
    spawnTimer = 0.0f; // Reset spawn timer
}

void Wave::removeDeadEnemies() {
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const auto& enemy) {
                if (enemy->isDead()) {
                    Economy::getInstance().addEnemyReward(
                        enemy->getType(),
                        enemy->getHealth()
                    );
                    return true;
                }
                return false;
            }),
        enemies.end()
    );
}