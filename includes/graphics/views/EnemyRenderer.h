//
// Created by chris on 16/06/2025.
//

#ifndef ENEMYRENDERER_H
#define ENEMYRENDERER_H

#include <SFML/Graphics.hpp>
#include "../../../includes/logic/models/Enemy.h"

class EnemyRenderer {
private:
    sf::Sprite enemySprites[3];
    sf::Font font;
    sf::Texture textures[3];

public:
    EnemyRenderer();
    ~EnemyRenderer();

    void loadSprites();

    void renderEnemy(const std::shared_ptr<Enemy>& enemy, sf::RenderWindow& window);
    void renderHealthBar(const std::shared_ptr<Enemy>& enemy, sf::RenderWindow& window);
    void renderHealthText(const std::shared_ptr<Enemy>& enemy, sf::RenderWindow& window);
};

#endif // ENEMYRENDERER_H