//
// Created by chris on 04/06/2025.
//

#include "Enemy.h"
#include "PathNode.h"
#include "Tower.h"

// Multiplier const stats
static constexpr int CORPORAL_HEALTH_MULT = 2;    //Life Multiplier for corporal
static constexpr int CORPORAL_DAMAGE_MULT = 2;    //Damage Multiplier for corporal
static constexpr int SERGEANT_HEALTH_MULT = 3;    //Life Multiplier for Sergeant
static constexpr int SERGEANT_DAMAGE_MULT = 3;    //Damage Multiplier for Sergeant
static constexpr float ELITE_SPEED_MULT = 0.8f;   //Speed Multiplier for Elite


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
            this->health *= CORPORAL_HEALTH_MULT;
            this->damage *= CORPORAL_DAMAGE_MULT;
            this->speed *= ELITE_SPEED_MULT;
            break;
        case EnemyType::SERGEANT:
            this->health *= SERGEANT_HEALTH_MULT;
            this->damage *= SERGEANT_DAMAGE_MULT;
            this->speed *= ELITE_SPEED_MULT;
            break;
        default:
            break;
    }
}

void Enemy::move(float deltaTime) {
    attackTimer += deltaTime;

    if (!nextNode) {
        if (currentNode && currentNode->getType() == "base") {
            attack();
        }
        return;
    }

    progress += speed * deltaTime;

    if (progress >= 1.0f) {
        // Move to next node
        std::shared_ptr<PathNode> previousNode = currentNode;
        currentNode = nextNode;

        // Find the next node in the path
        nextNode = currentNode->findNextNode(previousNode);

        progress = 0.0f;
        position = currentNode->getPixelPosition();
    } else {
        // Interpolate position between current and next node
        Position startPos = currentNode->getPixelPosition();
        Position endPos = nextNode->getPixelPosition();
        position.x = startPos.x + (endPos.x - startPos.x) * progress;
        position.y = startPos.y + (endPos.y - startPos.y) * progress;
    }
}

void Enemy::attack() {
    if (!currentNode || currentNode->getType() != "base") {
        return;
    }
    if (attackTimer >= attackCooldown) {
        Tower::getInstance().damageBase(damage);
        attackTimer = 0.0f;
    }
}

void Enemy::takeDamage(int amount) {
    health -= amount;
    if (health < 0) {
        health = 0;
    }
}

bool Enemy::hasReachedEnd() const {
    return currentNode && currentNode->getType() == "base";
}