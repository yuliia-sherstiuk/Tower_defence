#pragma once
#include <SFML/Graphics.hpp>

class WindowView {
public:
    WindowView();
    void setupUI();
    void render(sf::RenderWindow& window);

private:
    sf::Font font;

    sf::RectangleShape gameField;
    sf::RectangleShape sidePanel;

    sf::Text scoreLabel, moneyText, livesText;
    sf::Text chronoLabel, mapLabel, difficultyLabel, towerLabel;

    sf::Text mapButtons[2];
    sf::Text difficultyButtons[3];
    sf::Text towerButtons[3];

    sf::Text bottomButtons[5]; // START, PLAY, PAUSE, RESUME, QUIT
    sf::Text nextWaveBtn;
};