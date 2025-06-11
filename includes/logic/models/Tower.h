#ifndef TOWER_H
#define TOWER_H

#include <iostream>
#include <memory>
#include <string>
#include "Position.h"
#include "Enemy.h"

class Tower{
private:
    static Tower instance; //for singleton
    int baseHealth;

    Tower(): baseHealth(100){};

public:
    static Tower& getInstance() {
        static Tower instance;
        return instance;
    }
    void damageBase(int damage);
    int getBaseHealth() const;

    std::string name{}; //tower name
    int health{}; //tower health
    int atk{};
    int level{};
    double atkMultiplier{};
    bool visible=true;
    std::string spritePath{};
    int price{};

    Tower(std::string name, int hp, int atk,int price, std::string spritePath);

    void attack(Enemy* enemy);
    void upgrade();
    void takeDamage(int amount);
    void getDestroyed();
};



#endif