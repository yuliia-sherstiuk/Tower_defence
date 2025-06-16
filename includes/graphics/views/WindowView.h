
#ifndef WINDOWVIEW_H
#define WINDOWVIEW_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <functional>
#include "MapRenderer.h"

class WindowView {
public:
    //WindowView();
    explicit WindowView(sf::RenderWindow& window);

    // Core rendering
    void render(sf::RenderWindow& window);

    // Game state update methods
    void updateScore(int score);
    void updateMoney(int money);
    void updateLives(int lives);
    void updateWaveCountdown(int countdown);
    void setMessage(const std::string& message);

    // UI Updates
    void updateUsernameDisplay(const std::string& text);
    void updateVolumeDisplay(float volume, bool muted);
    void updateScrollDisplay(int offset);
    void addScoreEntry(const std::string& entry);

    // Input Detection
    void handleClick(sf::Vector2f mousePos);
    void handleTextInput(sf::Uint32 unicode);
    void handleScrollEvent(const sf::Event& event);

    // Callback setters
    void setClickCallback(const std::function<void(const std::string&, sf::Vector2f)>& callback);
    void setVolumeCallback(const std::function<void(float)>& callback);
    void setTextInputCallback(const std::function<void(sf::Uint32)>& callback);
    void setScrollCallback(const std::function<void(bool)>& callback);
    void setRegisterCallback(const std::function<void(const std::string&)>& callback);

    // to convert coordinates
    sf::Vector2f getViewCoords(sf::RenderWindow& window, sf::Vector2i mousePos);

    //Level
    void setLevel(const std::shared_ptr<Level>& level);

private:
    // Dimension
    /*
    const float baseWidth = 1100;
    const float baseHeight = 720;
    */
    const float baseWidth = 2160;
    const float baseHeight = 1440;

    sf::RenderWindow& window;
    std::unique_ptr<MapRenderer> mapRenderer;
    std::shared_ptr<Level> currentLevel;
    sf::View view;

    // UI Elements
    sf::Font font;
    sf::RectangleShape gameField;
    sf::RectangleShape sidePanel;
    sf::RectangleShape messageArea;

    // Text elements
    sf::Text messageText;
    sf::Text scoreLabel;
    sf::Text moneyText;
    sf::Text livesText;
    sf::Text chronoLabel;
    sf::Text waveCountdownText;
    sf::Text mapLabel;
    sf::Text difficultyLabel;
    sf::Text towerLabel;
    sf::Text nextWaveBtn;
    sf::Text volumeLabel;
    sf::Text muteLabel;
    sf::Text registerPromptLabel;
    sf::Text usernameInputText;
    sf::Text registerButtonText;

    // Buttons and interactive elements
    sf::Text mapButtons[2];
    sf::Text difficultyButtons[3];
    sf::Text towerButtons[3];
    sf::Text bottomButtons[4];

    // Input elements
    sf::RectangleShape usernameInputField;
    sf::RectangleShape registerButton;
    sf::RectangleShape muteBox;

    // Volume control
    sf::RectangleShape volumeBarBackground;
    sf::CircleShape volumeSlider;

    // Score list and scrolling
    sf::RectangleShape scoreListArea;
    sf::RectangleShape scrollBarBackground;
    sf::RectangleShape scrollBarThumb;
    std::vector<sf::Text> scoreEntries;

    // Visual containers
    std::vector<sf::RectangleShape> labelBoxes;
    std::vector<sf::RectangleShape> buttonBoxes;

    // Display state
    int currentScore;
    int playerMoney;
    int baseLives;
    int waveCountdown;
    bool isCountingDown;
    float volume;
    bool isMuted;
    int scrollOffset;
    std::string currentUsernameInput;
    bool inputFieldActive;

    // Callbacks
    std::function<void(const std::string&, sf::Vector2f)> clickCallback;
    std::function<void(float)> volumeCallback;
    std::function<void(sf::Uint32)> textInputCallback;
    std::function<void(bool)> scrollCallback;
    std::function<void(const std::string&)> registerCallback;

    // Setup methods
    void setupUI();
    void updateView(sf::RenderWindow& window);
    std::string getButtonId(sf::Vector2f mousePos);
};

#endif // WINDOWVIEW_H
