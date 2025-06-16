//
// Created by chris on 16/06/2025.
//

#ifndef MAP_RENDERER_H
#define MAP_RENDERER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <cmath>
#include <set>
#include "../../../includes/utils/Level.h"
#include "../../../includes/utils/GridPosition.h"
#include "../../../includes/utils/PathNode.h"

class MapRenderer {
private:
    static const float CELL_SIZE;
    static const float GAME_FIELD_X;
    static const float GAME_FIELD_Y;

    sf::RenderWindow& window;
    std::shared_ptr<Level> currentLevel;
    bool levelDebugPrinted;
    sf::Texture baseTexture;
    sf::Sprite baseSprite;

    const sf::Color spawnColor;
    const sf::Color pathColor;
    const sf::Color towerSpotColor;
    const sf::Color defaultColor;
    const sf::Color gridColor;

public:
    explicit MapRenderer(sf::RenderWindow& window);
    void setLevel(const std::shared_ptr<Level>& level);
    void render();

private:
    void renderGrid();
    void renderLevelElements();
    void renderTowerSpots();
    void printLevelDebugInfo();
    void renderEnemyPath();
};

#endif // MAP_RENDERER_H