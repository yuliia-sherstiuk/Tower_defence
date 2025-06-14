//WindowView.h
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
    void setInputText(const std::string& text);
    void updateVolumeSliderPosition();
    void handleScrollEvent(const sf::Event& event);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

private:
    sf::Font font;

    sf::RectangleShape gameField;
    sf::RectangleShape sidePanel;

    sf::Text scoreLabel, moneyText, livesText;
    sf::Text chronoLabel, mapLabel, difficultyLabel, towerLabel;

    sf::Text usernameLabel;
    sf::Text inputField;
    sf::Text enterButton;

    // Volume elements
    sf::Text volumeLabel;
    sf::RectangleShape volumeBarBackground;
    sf::CircleShape volumeSlider;

    float volume = 1.f;
    bool isMuted = false;
    bool muteChecked = false;
    bool isDraggingVolume = false;

    sf::RectangleShape muteBox;
    sf::Text muteLabel;

    std::vector<std::string> usernames;

    sf::Text mapButtons[2];
    sf::Text difficultyButtons[3];
    std::vector<sf::Text> towerButtons;
    sf::Text bottomButtons[5];

    sf::RectangleShape usernameInputBox;
    sf::Text usernameInputText;
    sf::Text usernameDisplayText;

    sf::Clock chronoClock;
    sf::Text chronoTimeText;
    bool isChronoRunning = true;
    sf::RectangleShape chronoTimeBox;

    sf::Texture towerTextures[3];
    sf::Sprite towerSprites[3];
    bool isDragging = false;
    int draggedTowerIndex = -1;
    sf::Vector2f dragOffset;
    sf::RectangleShape draggableRect;
    std::vector<sf::RectangleShape> towerImageContainers;


    sf::RectangleShape enterButtonShape;
    sf::Text enterButtonText;

    std::string currentUsernameInput;

    sf::Text nextWaveBtn;
    sf::RectangleShape scrollBarBackground;
    sf::RectangleShape scrollBarThumb;
    std::vector<sf::RectangleShape> labelBoxes;
    std::vector<sf::RectangleShape> buttonBoxes;

    std::string inputText;

    sf::RectangleShape scoreListArea;
    std::vector<sf::Text> scoreEntries;
    int scrollOffset = 0;
};
