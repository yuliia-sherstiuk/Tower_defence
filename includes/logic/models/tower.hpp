#ifndef TOWER_H
#define TOWER_H

#include <iostream>
#include <string>

class Tower{
    public:
    std::string name;
    int hp=100;
    int atk=1;
    int level=1;
    double atkMultiplier=0.1;
    bool visible=true;

    Tower(std::string name, int hp, int atk);

    void attack(Enemy* enemy);
    void upgrade();
};



#endif