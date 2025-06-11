#ifndef TOWERVARIANTS_H
#define TOWERVARIANTS_H

#include "Enemy.h"
#include "Tower.h"

class Puncher: public Tower {
    public:
    Puncher();
    void Puncher::attack(Enemy* enemy);

    void Puncher::takeDamage(int damage);

    void Puncher::upgrade();

    void Puncher::getDestroyed();

};

class Freezer: public Tower {
public:
    Freezer();
    void Freezer::attack(Enemy* enemy);

    void Freezer::takeDamage(int damage);

    void Freezer::upgrade();

    void Freezer::getDestroyed();
};

class Bomber: public Tower {
public:
    Bomber();
    void Bomber::attack(Enemy* enemy);

    void Bomber::takeDamage(int damage);

    void Bomber::upgrade();

    void Bomber::getDestroyed();
};



#endif //TOWERVARIANTS_H
