//
// Created by chris on 04/06/2025.
//
#include "Enemy.h"
#include "PathNode.h"
#include "Tower.h"

// Multiplier const stats
static constexpr int CORPORAL_HEALTH_MULT = 2;    // Life Multiplier for corporal
static constexpr int CORPORAL_DAMAGE_MULT = 2;    // Damage Multiplier for corporal
static constexpr int SERGEANT_HEALTH_MULT = 3;    // Life Multiplier for Sergeant
static constexpr int SERGEANT_DAMAGE_MULT = 3;    // Damage Multiplier for Sergeant
static constexpr float ELITE_SPEED_MULT = 0.8f;   // Speed Multiplier for Elite

// Constructor initializing the Enemy with specific properties based on its type.
Enemy::Enemy(int id, int health, float speed, int damage,
             std::shared_ptr<PathNode> startNode, EnemyType type)
    : id(id), health(health), speed(speed), damage(damage),
      currentNode(std::move(startNode)), nextNode(nullptr),
      progress(0.0f), type(type) {

    if (currentNode) {
        position = currentNode->getPixelPosition();
        // SET UP THE INITIAL PATH
        nextNode = currentNode->findNextNode();
    }

    switch(type) {
        case EnemyType::CORPORAL:
            this->health *= CORPORAL_HEALTH_MULT; // Apply corporal health multiplier
            this->damage *= CORPORAL_DAMAGE_MULT; // Apply corporal damage multiplier
            this->speed *= ELITE_SPEED_MULT;      // Apply elite speed multiplier
            break;
        case EnemyType::SERGEANT:
            this->health *= SERGEANT_HEALTH_MULT; // Apply sergeant health multiplier
            this->damage *= SERGEANT_DAMAGE_MULT; // Apply sergeant damage multiplier
            this->speed *= ELITE_SPEED_MULT;      // Apply elite speed multiplier
            break;
        default:
            break;
    }
}

// Updates the enemy's position based on elapsed time.
void Enemy::move(float deltaTime) {
    attackTimer += deltaTime;

    if (!nextNode) {
        if (currentNode && currentNode->getType() == "base") {
            attack(); // Attack if at the base
        }
        return;
    }

    progress += speed * deltaTime; // Update progress based on speed and time

    if (progress >= 1.0f) {
        // Move to next node
        std::shared_ptr<PathNode> previousNode = currentNode;
        currentNode = nextNode;

        // Find the next node in the path
        nextNode = currentNode->findNextNode(previousNode);

        progress = 0.0f; // Reset progress
        position = currentNode->getPixelPosition(); // Update position to next node
    } else {
        // Interpolate position between current and next node
        Position startPos = currentNode->getPixelPosition();
        Position endPos = nextNode->getPixelPosition();
        position.x = startPos.x + (endPos.x - startPos.x) * progress; // Calculate new x position
        position.y = startPos.y + (endPos.y - startPos.y) * progress; // Calculate new y position
    }
}

// Executes an attack on the base if conditions are met.
void Enemy::attack() {
    if (!currentNode || currentNode->getType() != "base") {
        return; // Exit if not at base
    }
    if (attackTimer >= attackCooldown) {
        Tower::getInstance().damageBase(damage); // Deal damage to the base
        attackTimer = 0.0f; // Reset attack timer
    }
}

// Reduces the enemy's health by a specified amount.
void Enemy::takeDamage(int amount) {
    health -= amount; // Subtract damage from health
    if (health < 0) {
        health = 0; // Ensure health does not go below zero
    }
}

// Checks if the enemy has reached the end of its path.
bool Enemy::hasReachedEnd() const {
    return currentNode && currentNode->getType() == "base"; // Return true if at base
}