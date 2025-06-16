#ifndef ECONOMY_H
#define ECONOMY_H

#include "../models/Enemy.h"
#include "../models/Tower.h"
#include <vector>

class Economy {
public:
    static Economy& getInstance();

    static int goldAmount; //amount of gold the player has
    int profitMultiplier{}; //to increase the profit depending on the difficulty

    void earnGold(std::vector<Enemy*> enemiesDefeated);

    static int returnGoldAmount();

    bool buyTower(Tower* towerToBuy);

private:
    Economy();

    Economy(const Economy&)=delete;

    Economy& operator=(const Economy&)=delete;

};

#endif //ECONOMY_H
