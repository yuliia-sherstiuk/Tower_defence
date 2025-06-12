
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class WindowView {
public:
    WindowView();
    void setupUI();
    void render(sf::RenderWindow& window);
    void handleClick(sf::Vector2f mousePos);
    void addUsername(const std::string& name);
    void scrollUp();
    void scrollDown();
    void setInputText(const std::string& text); // для обновления текста из главного цикла

private:
    sf::Font font;

    sf::RectangleShape gameField;
    sf::RectangleShape sidePanel;

    sf::Text scoreLabel, moneyText, livesText;
    sf::Text chronoLabel, mapLabel, difficultyLabel, towerLabel;

    sf::Text usernameLabel;
    sf::Text inputField;
    sf::Text enterButton;

    std::vector<sf::Text> scoreEntries;
    std::vector<std::string> usernames;
    int scrollOffset = 0;




    sf::Text mapButtons[2];
    sf::Text difficultyButtons[3];
    sf::Text towerButtons[3];
    sf::Text bottomButtons[5];

    sf::Text nextWaveBtn;

    std::vector<sf::RectangleShape> labelBoxes;
    std::vector<sf::RectangleShape> buttonBoxes;

    std::string inputText;
};