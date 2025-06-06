//
// Created by chris on 04/06/2025.
//

#include "Wave.h"
#include "Enemy.h"
#include <algorithm> //for remove if

Wave::Wave(int number, std::string diff, const std::shared_ptr<PathNode>& spawn)
    : waveNumber(number), difficulty(std::move(diff)), spawnNode(spawn),
      isComplete(false), enemiesToSpawn(5 + number * 2),
      spawnTimer(0.0f), spawnInterval(1.0f) {
}

void Wave::spawnEnemies(float deltaTime) {
    if (enemiesToSpawn <= 0) return;

    spawnTimer += deltaTime;
    if (spawnTimer >= spawnInterval) {
        // Create a new enemy
        int health = static_cast<int>(100 + waveNumber * 10); // to adjust
        float speed = 50.0f + static_cast<float>(waveNumber * 2); // to adjust
        int damage = static_cast<int>(1 + waveNumber / 2); // to adjust

        auto enemy = std::make_shared<Enemy>(
            enemies.size(), health, speed, damage, spawnNode
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