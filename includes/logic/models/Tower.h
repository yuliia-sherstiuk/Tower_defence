#ifndef TOWER_H
#define TOWER_H

#include <iostream>
#include <memory>
#include <string>
#include "../../utils/Position.h"
#include "../models/Enemy.h"

class Tower{
private:
    static Tower instance; //for singleton
    int baseHealth;

    Tower(): baseHealth(){};

public:
    static Tower& getInstance() {
        static Tower instance;
        return instance;
    }
    void damageBase(int damage);
    int getBaseHealth() const;

    //tower attributes
    std::string name{}; //tower name
    int health{}; //tower health
    int atk{};
    int level=1;
    double atkMultiplier{};
    bool visible=true;
    std::string spritePath{};
    int price{};
    int atkRange{};
    double rangeMultiplier{};
    //tower attributes

    //constructor
    Tower(std::string name, int hp, int atk,int price, std::string spritePath);

    //virtual functions to be overridden
    virtual void attack(Enemy* enemy);
    virtual void upgrade();
    virtual void takeDamage(int amount);
    virtual void getDestroyed();

    //concrete functions
    void setRadius();

    Tower* createTower(std::string towerType);


    //destructor
    virtual ~Tower();
};



#endif