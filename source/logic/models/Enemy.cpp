//
// Created by chris on 04/06/2025.
//
#include "Enemy.h"
#include "PathNode.h"
#include "Tower.h"

Enemy::Enemy(int id, int health, float speed, int damage,
             std::shared_ptr<PathNode> startNode, EnemyType type)
    : id(id), health(health), speed(speed), damage(damage),
      currentNode(std::move(startNode)), nextNode(nullptr),
      progress(0.0f), type(type) {

    if (currentNode) {
        position = currentNode->getPixelPosition();
    }

    // Adjust stats depending on type
    switch(type) {
        case EnemyType::CORPORAL:
            health *= 2;
            damage *= 1.5;
            break;
        case EnemyType::SERGEANT:
            health *= 3;
            damage *= 2;
            speed *= 0.8f; // speed see if not relevant comment
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
        currentNode = nextNode;
        nextNode = nullptr;
        progress = 0.0f;
        position = currentNode->getPixelPosition();
    } else {
        Position startPos = currentNode->getPixelPosition();
        Position endPos = nextNode->getPixelPosition();
        position.x = startPos.x + (endPos.x - startPos.x) * progress;
        position.y = startPos.y + (endPos.y - startPos.y) * progress;
    }
}

void Enemy::attack() {
    // if enemy is not on a base node no attack
    if (!currentNode || currentNode->getType() != "base") {
        return;
    }
    // Apply base damage
    if (attackTimer >= attackCooldown) {
        // Inflict damage
        Tower::getInstance().damageBase(damage);
        // Reset attack timer
        attackTimer = 0.0f;
    }
}

void Enemy::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

bool Enemy::hasReachedEnd() const {
    return currentNode && currentNode->getType() == "base";
}
