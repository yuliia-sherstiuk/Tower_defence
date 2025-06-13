#include "../../../includes/logic/models/Tower.h"
#include "../../../includes/logic/models/towerVariants.h"

/**Tower constructor, params should be obvious enough */
Tower::Tower(std::string name, int hp, int atk,int price, std::string spritePath) {
    this->name = name;
    this->health = hp;
    this->atk = atk;
    this->spritePath = spritePath;
    this->price = price;

    if (hp<=0) {
        std::cout<<"Tower "<<this->name<<" has been destroyed"<<std::endl;
        //this->visible=false;
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

/** attack an enemy and trigger its damage taking function
 * @params enemy(Enemy*) the enemy to be attacked
 */
void Tower::attack(Enemy* enemy) {
    enemy->takeDamage(this->atk);
}

/**take damage from a specific attack
 *@params damage (int) the damage to be taken
 */
void Tower::takeDamage(int damage) {
    health-=damage;
    if (health<=0) {
        health=0;
    }
}

/** upgrade the tower once*/
void Tower::upgrade() {
    this->level+=1;
    this->atk=this->atk*this->atkMultiplier;
}


/** in case we want to add an animation or a special effect to a tower when destroyed*/
void Tower::getDestroyed() {
        // overload with an animation or something for when a tower gets destroyed
}

/**
 *@brief returns a tower type depending on the name passed in
 * @param towerType tower name to be returned
 * @return a tower variant depending on the name
 */
Tower* Tower::createTower(std::string towerType) {

    if (towerType=="Puncher"){
        return new Puncher;
        }
    if (towerType=="Freezer"){
        return new Freezer;
        }
    if (towerType=="Bomber"){
        return new Bomber;
        }
    if (towerType=="Base"){
        return new Base;
        }

    std::cerr<<"Tower creation failed, incorrect tower type"<<std::endl;
    exit(1);
}

Tower:: ~Tower(){};