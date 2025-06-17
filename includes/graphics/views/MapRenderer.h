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
#include "../../../includes/graphics/views/EnemyRenderer.h"

class EnemyRenderer;
class Wave;

class MapRenderer {
private:
    sf::RenderWindow& window;
    const sf::Color spawnColor;
    const sf::Color pathColor;
    const sf::Color towerSpotColor;
    const sf::Color defaultColor;
    const sf::Color gridColor;
    bool levelDebugPrinted;
    std::unique_ptr<EnemyRenderer> enemyRenderer;
    std::shared_ptr<Level> currentLevel;
    std::shared_ptr<Wave> currentWave;
    sf::Texture baseTexture;
    sf::Sprite baseSprite;

public:
    static const float CELL_SIZE;
    static const float GAME_FIELD_X;
    static const float GAME_FIELD_Y;

    explicit MapRenderer(sf::RenderWindow& window);
    void setLevel(const std::shared_ptr<Level>& level);
    void setCurrentWave(const std::shared_ptr<Wave>& wave);
    void render();

private:
    void renderGrid();
    void renderLevelElements();
    void renderTowerSpots();
    void printLevelDebugInfo();
    void renderEnemyPath();
    void renderEnemies();
};

#endif // MAP_RENDERER_H