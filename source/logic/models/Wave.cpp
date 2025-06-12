// Created by chris on 04/06/2025.
//
#include "../models/Wave.h"
#include "../models/Enemy.h"
#include "../models/Economy.h"
#include <algorithm>

// Returns the corresponding EnemyType based on the difficulty string.
EnemyType Wave::getDifficultyType() const {
    if (difficulty == "corporal") return EnemyType::CORPORAL;
    if (difficulty == "sergeant") return EnemyType::SERGEANT;
    return EnemyType::PRIVATE;
}

// Constructor initializing the wave with its number, difficulty, and spawn node.
Wave::Wave(int number, std::string diff, const std::shared_ptr<PathNode>& spawn)
    : waveNumber(number), difficulty(std::move(diff)), spawnNode(spawn),
      isComplete(false), enemiesToSpawn(5 + number * 2),
      spawnTimer(0.0f), spawnInterval(1.0f) {
}

// Spawns enemies based on the elapsed time and current wave conditions.
void Wave::spawnEnemies(float deltaTime) {
    if (enemiesToSpawn <= 0) return; // Exit if no enemies left to spawn

    spawnTimer += deltaTime; // Update spawn timer
    if (spawnTimer >= spawnInterval) {
        // Base stats
        int health = static_cast<int>(100 + waveNumber * 10);
        float speed = 50.0f + static_cast<float>(waveNumber * 2);
        int damage = static_cast<int>(1 + waveNumber / 2);

        int enemiesSpawned = (5 + waveNumber * 2) - enemiesToSpawn;

        // Determine enemy type based on difficulty and spawn position
        EnemyType enemyType = EnemyType::PRIVATE;

        if (difficulty == "corporal" || difficulty == "sergeant") {
            // Spawn corporal every 5 enemies (0, 5, 10, 15...)
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

// Updates the wave state and moves all enemies.
void Wave::update(float deltaTime) {
    spawnEnemies(deltaTime);

    for (auto& enemy : enemies) {
        enemy->move(deltaTime); // Move each enemy
    }

    removeDeadEnemies();

    isComplete = (enemiesToSpawn == 0 && enemies.empty()); // Check if wave is complete
}

// Prepares for the next wave by incrementing the wave number and resetting parameters.
void Wave::nextWave() {
    waveNumber++;
    enemiesToSpawn = 5 + waveNumber * 2;
    isComplete = false;
    spawnTimer = 0.0f;
}

// Removes dead enemies from the list and rewards the economy.
void Wave::removeDeadEnemies() {
    Economy economy;
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [&economy](const auto& enemy) {
                if (enemy->isDead()) {
                    std::vector<Enemy*> deadEnemy = {enemy.get()};
                    economy.earnGold(deadEnemy);
                    return true;
                }
                return false;
            }),
        enemies.end()
    );
}