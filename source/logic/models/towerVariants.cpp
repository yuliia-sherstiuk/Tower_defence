#include "towerVariants.h"

Puncher::Puncher() : Tower("Punchy", 200, 2, 10, " "){}

void Puncher::attack(Enemy* enemy) {
    enemy->takeDamage(this->atk);
    std::cout<<"Enemy was punched!"<<std::endl;
}

void Puncher::takeDamage(int damage) {
    health-=damage;
    if (health<=0) {
        health=0;
    }
    std::cout<<"ouchie"<<std::endl;
}

void Puncher::upgrade() {
    this->level+=1;
    this->atk=this->atk*this->atkMultiplier;
    std::cout<<"puncher just got upgraded"<<std::endl;
}

void Puncher::getDestroyed() {
    std::cout<<"the puncher was punched...TO OBLIVION"<<std::endl;
}

/** END PUNCHER↑
 *
 *
 * START FREEZER↓
 */

Freezer:: Freezer():Tower("Freezie", 1, 10, 30, " ") {}

void Freezer::attack(Enemy* enemy) {
    enemy->takeDamage(this->atk);
    std::cout<<"Enemy was frozen!"<<std::endl;
    float originalSpeed=enemy->speed;
    enemy->speed=0;
    //wait 3 seconds then:
    enemy->speed=originalSpeed;
}

void Freezer::takeDamage(int damage) {
    health-=damage;
    if (health<=0) {
        health=0;
    }
    std::cout<<"the ice was cracked, oh no"<<std::endl;
}

void Freezer::upgrade() {
    this->level+=1;
    this->atk=this->atk*this->atkMultiplier;
    std::cout<<"freezer just got upgraded"<<std::endl;
    std::cout<<"explosion radius increased!"<<std::endl;
}

void Freezer::getDestroyed() {
    std::cout<<"the ice was melted..."<<std::endl;
}

/** END FREEZER ↑
 *
 * START BOMBER↓
 */

Bomber::Bomber(): Tower("bombie",1, 999, 100, " "){}

void Bomber::attack(Enemy *enemy) {
    enemy->takeDamage(this->atk);
    this->health=0;
    std::cout<<"BOOM"<<std::endl;
}

void Bomber::takeDamage(int damage) {
    health-=damage;
    if (health<=0) {
        health=0;
    }
    std::cout<<"the bomb exploded too early!"<<std::endl;
}

void Bomber::getDestroyed() {
    std::cout<<"Bomb exploded."<<std::endl;
}

void Bomber::upgrade() {
    //increase explosion size
    std::cout<<"the bomb was upgraded, explosion radius increased"<<std::endl;
}
