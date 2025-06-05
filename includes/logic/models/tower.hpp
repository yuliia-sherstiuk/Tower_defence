#ifndef TOWER_H
#define TOWER_H

#include <iostream>
#include <string>
#include <memory>
#include "position.h"

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

    std::string name;
    int hp=100;
    int atk=1;
    int level=1;
    double atkMultiplier=0.1;
    bool visible=true;
    std::string spritePath;

    Tower(std::string name, int hp, int atk, std::string spritePath);

    void attack(Enemy* enemy);
    void upgrade();
};



#endif