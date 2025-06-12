#ifndef TOWERVARIANTS_H
#define TOWERVARIANTS_H

#include "Enemy.h"
#include "Tower.h"

class Puncher final: public Tower {
    public:
    Puncher();
    void Puncher::attack(Enemy* enemy) override;

    void Puncher::takeDamage(int damage) override;

    void Puncher::upgrade() override;

    void Puncher::getDestroyed() override;

};

class Freezer final: public Tower {
public:
    Freezer();
    void Freezer::attack(Enemy* enemy) override;

    void Freezer::takeDamage(int damage) override;

    void Freezer::upgrade() override;

    void Freezer::getDestroyed() override;
};

class Bomber final: public Tower {
public:
    Bomber();
    void Bomber::attack(Enemy* enemy) override;

    void Bomber::takeDamage(int damage) override;

    void Bomber::upgrade() override;

    void Bomber::getDestroyed() override;
};

class Base final: public Tower {
    public:

        Base();

        void Base::takeDamage(int damage) override;

        void Base::getDestroyed() override;
};



#endif //TOWERVARIANTS_H
