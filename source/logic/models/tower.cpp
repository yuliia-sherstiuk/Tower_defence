#include "tower.hpp"

Tower::Tower(std::string name, int hp, int atk, std::string spritePath) {
    this->name = name;
    this->hp = hp;
    this->atk = atk;
    this->spritePath = spritePath;

    if (hp<=0) {
        std::cout<<"Tower "<<this->name<<" has been destroyed"<<std::endl;
        this->visible=false;
    }
}

void Tower::damageBase(int damage) {
    baseHealth -= damage;
    if (baseHealth<0) {
        baseHealth = 0;
    }
}

int Tower::getBaseHealth() const {
    return baseHealth;
}


void Tower::attack(Enemy* enemy) {
    enemy->hp-=this->atk;
}

void Tower::upgrade() {
    this->level+=1;
    this->atk=this->atk*this->atkMultiplier;
}