//
// Created by chris on 04/06/2025.
//

#ifndef ENEMY_H
#define ENEMY_H

#include <memory>
#include "Position.h"

class PathNode;

class Enemy {
private:
	int id;
	int health;
	float speed;
	int damage;
	Position position;
	std::shared_ptr<PathNode> currentNode;
	std::shared_ptr<PathNode> nextNode;
	float progress; //progress between currentNode and nextNode (0.0 to 1.0)
	float attackTimer = 0.0f;
	const float attackCooldown = 1.0f; //attack each second

public:
	Enemy(int id, int health, float speed, int damage, std::shared_ptr<PathNode> startNode);

	//Getters
	int getId() const { return id; }
	int getHealth() const { return health; }
	float getSpeed() const { return speed; }
	int getDamage() const { return damage; }
	const Position& getPosition() const { return position; }

	//methods
	void move(float deltaTime);
	void attack();
	void takeDamage(int amount);

	//State methods
	bool isDead() const { return health <= 0; }
	bool hasReachedEnd() const;

	//Handling the path
	void setNextNode(std::shared_ptr<PathNode>&& node) { nextNode = std::move(node); }
	std::shared_ptr<PathNode> getCurrentNode() const { return currentNode; }
	std::shared_ptr<PathNode> getNextNode() const { return nextNode; }
};

#endif //ENEMY_H
