#ifndef TOWERVARIANTS_H
#define TOWERVARIANTS_H

#include "../models/Enemy.h"
#include "../models/Tower.h"

class Puncher final: public Tower {
    public:
    Puncher();
    void attack(Enemy* enemy) override;

    void takeDamage(int damage) override;

    void upgrade() override;

    void getDestroyed() override;

};

class Freezer final: public Tower {
public:
    Freezer();
    void attack(Enemy* enemy) override;

    void takeDamage(int damage) override;

    void upgrade() override;

    void getDestroyed() override;
};

class Bomber final: public Tower {
public:
    Bomber();
    void attack(Enemy* enemy) override;

    void takeDamage(int damage) override;

    void upgrade() override;

    void getDestroyed() override;
};

class Base final: public Tower {
    public:

        Base();

        void takeDamage(int damage) override;

        void getDestroyed() override;
};



#endif //TOWERVARIANTS_H
