//
// Created by chris on 16/06/2025.
//

#include "EnemyRenderer.h"
#include <iostream>

//Enemy renderer
EnemyRenderer::EnemyRenderer() {
    //load textures
    if (!textures[0].loadFromFile("assets/sprites/soldier.png")) {
        std::cerr << "Error loading soldier.png" << std::endl;
    }
    if (!textures[1].loadFromFile("assets/sprites/corporal.png")) {
        std::cerr << "Error loading corporal.png" << std::endl;
    }
    if (!textures[2].loadFromFile("assets/sprites/sergeant.png")) {
        std::cerr << "Error loading sergeant.png" << std::endl;
    }

    // Init sprites
    for (int i = 0; i < 3; ++i) {
        enemySprites[i].setTexture(textures[i]);
    }
    if (!font.loadFromFile("assets/fonts/Space_Grotesk.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
}

EnemyRenderer::~EnemyRenderer() {
}

void EnemyRenderer::loadSprites() {
    //sprite already in constructor
}

//Display enemy
void EnemyRenderer::renderEnemy(const std::shared_ptr<Enemy>& enemy, sf::RenderWindow& window) {
    // Select correct sprite depending on enemy type
    switch (enemy->getType()) {
        case EnemyType::PRIVATE:
            enemySprites[0].setPosition(enemy->getPosition().x, enemy->getPosition().y);
            window.draw(enemySprites[0]);
            break;
        case EnemyType::CORPORAL:
            enemySprites[1].setPosition(enemy->getPosition().x, enemy->getPosition().y);
            window.draw(enemySprites[1]);
            break;
        case EnemyType::SERGEANT:
            enemySprites[2].setPosition(enemy->getPosition().x, enemy->getPosition().y);
            window.draw(enemySprites[2]);
            break;
    }

    // display bar life
    renderHealthBar(enemy, window);

    // Display life text
    renderHealthText(enemy, window);
}

//Display health bar
void EnemyRenderer::renderHealthBar(const std::shared_ptr<Enemy>& enemy, sf::RenderWindow& window) {
    // Enemy position
    float x = enemy->getPosition().x;
    float y = enemy->getPosition().y;

    // Size of bar life
    const float BAR_WIDTH = 40.0f;
    const float BAR_HEIGHT = 5.0f;

    // Calculate actual life
    float currentHealth = static_cast<float>(enemy->getHealth());
    float maxHealth = static_cast<float>(enemy->getMaxHealth());
    float healthRatio = currentHealth / maxHealth;

    // Rectangle for maximal life - back
    sf::RectangleShape backgroundBar;
    backgroundBar.setSize(sf::Vector2f(BAR_WIDTH, BAR_HEIGHT));
    backgroundBar.setPosition(x - BAR_WIDTH / 2, y - BAR_HEIGHT / 2 - 10);
    backgroundBar.setFillColor(sf::Color::Red);

    // Rectangle for now health
    sf::RectangleShape healthBar;
    healthBar.setSize(sf::Vector2f(BAR_WIDTH * healthRatio, BAR_HEIGHT));
    healthBar.setPosition(x - BAR_WIDTH / 2, y - BAR_HEIGHT / 2 - 10);
    healthBar.setFillColor(sf::Color::Green);

    //Draw rectangles
    window.draw(backgroundBar);
    window.draw(healthBar);
}

//Display health text
void EnemyRenderer::renderHealthText(const std::shared_ptr<Enemy>& enemy, sf::RenderWindow& window) {
    // enemy pos
    float x = enemy->getPosition().x;
    float y = enemy->getPosition().y;

    // Create text
    sf::Text healthText;
    healthText.setFont(font);
    healthText.setString(std::to_string(enemy->getHealth()));
    healthText.setCharacterSize(12);
    healthText.setFillColor(sf::Color::White);
    healthText.setPosition(x - 10, y - 25);

    // Draw text
    window.draw(healthText);
}