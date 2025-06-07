#ifndef ECONOMY_H
#define ECONOMY_H

#include "Enemy.h"
#include "Tower.h"
#include <vector>

class Economy {
public:
    int goldAmount{}; //amount of gold the player has
    int profitMultiplier{}; //to increase the profit depending on the difficulty

    void earnGold(std::vector<Enemy*> enemiesDefeated);

    int getGoldAmount();

    bool buyTower(Tower* towerToBuy);

};

#endif //ECONOMY_H
