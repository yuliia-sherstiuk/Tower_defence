//
// Created by chris on 04/06/2025.
//

#include "Wave.h"
#include "Enemy.h"
#include <algorithm>

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
        int baseHealth = 100 + waveNumber * 10;
        float baseSpeed = 50.0f + static_cast<float>(waveNumber * 2);
        int baseDamage = 1 + waveNumber / 2;

        // Determine enemy type based on difficulty and wave patterns
        EnemyType enemyType = EnemyType::PRIVATE;

        if (difficulty == "corporal" || difficulty == "sergeant") {
            // for each 5 ennemies, create a Corporal
            if (enemiesToSpawn % 5 == 0) {
                enemyType = EnemyType::CORPORAL;
            }
        }

        if (difficulty == "sergeant") {
            // for each 15 ennemies (5 * 3) create a Sergeant
            if (enemiesToSpawn % 15 == 0) {
                enemyType = EnemyType::SERGEANT;
            }
        }

        auto enemy = std::make_shared<Enemy>(
            enemies.size(),
            baseHealth,
            baseSpeed,
            baseDamage,
            spawnNode,
            enemyType
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

    // Verify if wave is complete
    isComplete = (enemiesToSpawn == 0 && enemies.empty());
}

void Wave::nextWave() {
    waveNumber++;
    enemiesToSpawn = 5 + waveNumber * 2; // Re init for next wave
    isComplete = false;
}

void Wave::removeDeadEnemies() {
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const auto& enemy) { return enemy->isDead(); }),
        enemies.end()
    );
}