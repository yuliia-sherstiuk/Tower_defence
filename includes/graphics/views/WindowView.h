
#ifndef TOWER_WINDOWVIEW_H
#define TOWER_WINDOWVIEW_H

#include <SFML/Graphics.hpp>
#include "../models/Game.h"

class WindowView {
private:
    sf::RenderWindow& window;
    Game* game;

public:
    explicit WindowView(sf::RenderWindow& window, Game* game);
    void render();

    /* Methods to draw - change as desired
    * void drawTowers();
    * void drawEnemies();
    * void drawUI();
    */
};

#endif