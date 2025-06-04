#include "tower.hpp"

Tower::Tower(std::string name, int hp, int atk) {
    this->name = name;
    this->hp = hp;
    this->atk = atk;

    if (hp<=0) {
        std::cout<<"Tower "<<this->name<<" has been destroyed"<<std::endl;
        //this->visible=false;
    }
}

void Tower::attack(Enemy* enemy) {
    enemy->hp-=this->atk;
}

void Tower::upgrade() {
    this->level+=1;
    this->atk=this->atk*this->atkMultiplier;
}