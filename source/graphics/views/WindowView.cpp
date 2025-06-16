#include "WindowView.h"
#include <iostream>
#include <algorithm>

WindowView::WindowView() : currentScore(0), playerMoney(100), baseLives(100), waveCountdown(0), isCountingDown(false), isMuted(false), volume(1.0f)  {
    if (!font.loadFromFile("fonts/Space_Grotesk.ttf")) {
        std::cerr << "Failed to load font \"fonts/Space_Grotesk.ttf\" (failed to create the font face)\n";
        std::cerr << "Failed to load font\n";
    }

    // Initialiser la vue
    view = sf::View(sf::FloatRect(0, 0, baseWidth, baseHeight));
    setupUI();
}

void WindowView::updateView(sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    float windowRatio = windowSize.x / static_cast<float>(windowSize.y);
    float viewRatio = baseWidth / baseHeight;

    float viewportWidth = 1.f;
    float viewportHeight = 1.f;
    float viewportX = 0.f;
    float viewportY = 0.f;

    if (windowRatio > viewRatio) {
        viewportWidth = viewRatio / windowRatio;
        viewportX = (1.f - viewportWidth) / 2.f;
    } else {
        viewportHeight = windowRatio / viewRatio;
        viewportY = (1.f - viewportHeight) / 2.f;
    }

    view = sf::View(sf::FloatRect(0, 0, baseWidth, baseHeight));
    view.setViewport(sf::FloatRect(viewportX, viewportY, viewportWidth, viewportHeight));
}

sf::Vector2f WindowView::getViewCoords(sf::RenderWindow& window, sf::Vector2i mousePos) {
    return window.mapPixelToCoords(mousePos, view);
}

void WindowView::setupUI() {
    gameField.setSize({1700, 1080});
    gameField.setFillColor(sf::Color(30, 30, 30));
    gameField.setPosition(20, 260);

    messageArea.setSize({2160, 50});
    messageArea.setFillColor(sf::Color(60, 60, 60));
    messageArea.setPosition(20, 20);

    messageText.setFont(font);
    messageText.setString("Welcome to Tower Defense!");
    messageText.setCharacterSize(28);
    messageText.setFillColor(sf::Color::White);
    messageText.setPosition(30, 30);

    //Top panel
    sf::RectangleShape topPanel;
    topPanel.setSize({1700, 160});
    topPanel.setFillColor(sf::Color(40, 40, 40));
    topPanel.setPosition(20, 80);
    labelBoxes.push_back(topPanel);

    sidePanel.setSize({440, 1260});
    sidePanel.setFillColor(sf::Color(50, 50, 50));
    sidePanel.setPosition(1740, 80);

    // Score
    scoreLabel.setFont(font);
    scoreLabel.setString("SCORE: " + std::to_string(currentScore));
    scoreLabel.setCharacterSize(30);
    scoreLabel.setFillColor(sf::Color::White);
    scoreLabel.setPosition(40, 100);

    //Scores area list
    scoreListArea.setSize({360, 132});
    scoreListArea.setFillColor(sf::Color(20, 20, 20));
    scoreListArea.setOutlineColor(sf::Color::White);
    scoreListArea.setOutlineThickness(4);
    scoreListArea.setPosition(scoreLabel.getPosition().x, scoreLabel.getPosition().y + 80);

    sf::RectangleShape scoreBox;
    scoreBox.setSize({280, 60});
    scoreBox.setFillColor(sf::Color::Transparent);
    scoreBox.setOutlineColor(sf::Color::White);
    scoreBox.setOutlineThickness(4);
    scoreBox.setPosition(scoreLabel.getPosition());
    labelBoxes.push_back(scoreBox);

    scrollBarBackground.setSize({20.f, scoreListArea.getSize().y});
    scrollBarBackground.setFillColor(sf::Color(50, 50, 50));
    scrollBarBackground.setPosition(
        scoreListArea.getPosition().x + scoreListArea.getSize().x,
        scoreListArea.getPosition().y
    );

    scrollBarThumb.setSize({20.f, scoreListArea.getSize().y / 3});
    scrollBarThumb.setFillColor(sf::Color::White);
    scrollBarThumb.setPosition(scrollBarBackground.getPosition());

    registerPromptLabel.setFont(font);
    registerPromptLabel.setString("Register your score! Enter your username:");
    registerPromptLabel.setCharacterSize(24);
    registerPromptLabel.setFillColor(sf::Color::White);
    registerPromptLabel.setPosition(800, 90);

    usernameInputField.setSize({240, 50});
    usernameInputField.setFillColor(sf::Color(20, 20, 20));
    usernameInputField.setOutlineColor(sf::Color::White);
    usernameInputField.setOutlineThickness(2);
    usernameInputField.setPosition(800, 130);

    usernameInputText.setFont(font);
    usernameInputText.setString("");
    usernameInputText.setCharacterSize(28);
    usernameInputText.setFillColor(sf::Color::White);
    usernameInputText.setPosition(810, 140);

    registerButton.setSize({120, 50});
    registerButton.setFillColor(sf::Color::Transparent);
    registerButton.setOutlineColor(sf::Color::White);
    registerButton.setOutlineThickness(2);
    registerButton.setPosition(1050, 130);

    registerButtonText.setFont(font);
    registerButtonText.setString("Register");
    registerButtonText.setCharacterSize(24);
    registerButtonText.setFillColor(sf::Color::White);
    registerButtonText.setPosition(1060, 140);

    moneyText.setFont(font);
    moneyText.setString("Gold: " + std::to_string(playerMoney));
    moneyText.setCharacterSize(40);
    moneyText.setFillColor(sf::Color::White);
    moneyText.setPosition(1780, 100);

    sf::RectangleShape moneyBox = scoreBox;
    moneyBox.setPosition(moneyText.getPosition());
    labelBoxes.push_back(moneyBox);

    livesText.setFont(font);
    livesText.setString("Lives: " + std::to_string(baseLives));
    livesText.setCharacterSize(40);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(1780, 160);
    sf::RectangleShape livesBox = scoreBox;
    livesBox.setPosition(livesText.getPosition());
    labelBoxes.push_back(livesBox);

    chronoLabel.setFont(font);
    chronoLabel.setString("COUNT DOWN");
    chronoLabel.setCharacterSize(40);
    chronoLabel.setFillColor(sf::Color::White);
    chronoLabel.setPosition(1780, 300);
    sf::RectangleShape chronoBox = scoreBox;
    chronoBox.setPosition(chronoLabel.getPosition());
    labelBoxes.push_back(chronoBox);

    waveCountdownText.setFont(font);
    waveCountdownText.setString("Next wave in: " + std::to_string(waveCountdown));
    waveCountdownText.setCharacterSize(32);
    waveCountdownText.setFillColor(sf::Color::Yellow);
    waveCountdownText.setPosition(1780, 360);

    mapLabel.setFont(font);
    mapLabel.setString("MAP");
    mapLabel.setCharacterSize(40);
    mapLabel.setFillColor(sf::Color::White);
    mapLabel.setPosition(1780, 460);
    sf::RectangleShape mapBox = scoreBox;
    mapBox.setPosition(mapLabel.getPosition());
    labelBoxes.push_back(mapBox);

    for (int i = 0; i < 2; i++) {
        mapButtons[i].setFont(font);
        mapButtons[i].setString(std::to_string(i + 1));
        mapButtons[i].setCharacterSize(40);
        mapButtons[i].setFillColor(sf::Color::White);
        mapButtons[i].setPosition(1780 + i * 80, 560);

        sf::RectangleShape btnBox({60, 60});
        btnBox.setPosition(mapButtons[i].getPosition());
        btnBox.setFillColor(sf::Color::Transparent);
        btnBox.setOutlineColor(sf::Color::White);
        btnBox.setOutlineThickness(2);
        buttonBoxes.push_back(btnBox);
    }

    difficultyLabel.setFont(font);
    difficultyLabel.setString("Difficulty");
    difficultyLabel.setCharacterSize(36);
    difficultyLabel.setFillColor(sf::Color::White);
    difficultyLabel.setPosition(1780, 660);
    sf::RectangleShape diffBox = scoreBox;
    diffBox.setPosition(difficultyLabel.getPosition());
    labelBoxes.push_back(diffBox);

    for (int i = 0; i < 3; i++) {
        difficultyButtons[i].setFont(font);
        difficultyButtons[i].setString(std::to_string(i + 1));
        difficultyButtons[i].setCharacterSize(40);
        difficultyButtons[i].setFillColor(sf::Color::White);
        difficultyButtons[i].setPosition(1780 + i * 70, 760);

        sf::RectangleShape btnBox({60, 60});
        btnBox.setPosition(difficultyButtons[i].getPosition());
        btnBox.setFillColor(sf::Color::Transparent);
        btnBox.setOutlineColor(sf::Color::White);
        btnBox.setOutlineThickness(2);
        buttonBoxes.push_back(btnBox);
    }

    towerLabel.setFont(font);
    towerLabel.setString("TOWER");
    towerLabel.setCharacterSize(36);
    towerLabel.setFillColor(sf::Color::White);
    towerLabel.setPosition(1780, 860);
    sf::RectangleShape towerBox = scoreBox;
    towerBox.setPosition(towerLabel.getPosition());
    labelBoxes.push_back(towerBox);

    for (int i = 0; i < 3; i++) {
        const std::string towerSymbols[3] = { "1", "2", "3" };
        towerButtons[i].setFont(font);
        towerButtons[i].setString(towerSymbols[i]);
        towerButtons[i].setCharacterSize(40);
        towerButtons[i].setFillColor(sf::Color::White);
        towerButtons[i].setPosition(1780 + i * 70, 960);

        sf::RectangleShape btnBox({60, 60});
        btnBox.setPosition(towerButtons[i].getPosition());
        btnBox.setFillColor(sf::Color::Transparent);
        btnBox.setOutlineColor(sf::Color::White);
        btnBox.setOutlineThickness(2);
        buttonBoxes.push_back(btnBox);
    }

    nextWaveBtn.setFont(font);
    nextWaveBtn.setString("NEXT WAVE");
    nextWaveBtn.setCharacterSize(36);
    nextWaveBtn.setFillColor(sf::Color::White);
    nextWaveBtn.setPosition(1780, 1060);
    sf::RectangleShape nwBox({280, 60});
    nwBox.setPosition(nextWaveBtn.getPosition());
    nwBox.setFillColor(sf::Color::Transparent);
    nwBox.setOutlineColor(sf::Color::White);
    nwBox.setOutlineThickness(2);
    buttonBoxes.push_back(nwBox);

    volumeLabel.setFont(font);
    volumeLabel.setString("Volume");
    volumeLabel.setCharacterSize(36);
    volumeLabel.setFillColor(sf::Color::White);
    volumeLabel.setPosition(1780, 1140);
    labelBoxes.push_back(scoreBox);
    labelBoxes.back().setPosition(volumeLabel.getPosition());

    volumeBarBackground.setSize({300, 10});
    volumeBarBackground.setFillColor(sf::Color(100, 100, 100));
    volumeBarBackground.setPosition(1780, 1220);

    volumeSlider.setRadius(16);
    volumeSlider.setFillColor(sf::Color::White);
    volumeSlider.setOrigin(16, 16);
    float initialSliderX = volumeBarBackground.getPosition().x;
    float sliderY = volumeBarBackground.getPosition().y + volumeBarBackground.getSize().y / 2.0f;
    volumeSlider.setPosition(initialSliderX, sliderY);

    muteBox.setSize({40, 40});
    muteBox.setFillColor(sf::Color::Transparent);
    muteBox.setOutlineColor(sf::Color::White);
    muteBox.setOutlineThickness(4);
    muteBox.setPosition(1780, 1260);

    muteLabel.setFont(font);
    muteLabel.setString("Mute");
    muteLabel.setCharacterSize(36);
    muteLabel.setFillColor(sf::Color::White);
    muteLabel.setPosition(1830, muteBox.getPosition().y + (muteBox.getSize().y - 36) / 2.0f);

    for (int i = 0; i < 4; i++) {
        const std::string labels[4] = { "START", "PAUSE", "PLAY", "QUIT" };
        bottomButtons[i].setFont(font);
        bottomButtons[i].setString(labels[i]);
        bottomButtons[i].setCharacterSize(36);
        bottomButtons[i].setFillColor(sf::Color::White);

        sf::RectangleShape btnBox({200, 60});
        btnBox.setPosition(40 + i * 484, 1360);
        btnBox.setFillColor(sf::Color::Transparent);
        btnBox.setOutlineColor(sf::Color::White);
        btnBox.setOutlineThickness(4);

        sf::FloatRect textBounds = bottomButtons[i].getLocalBounds();
        bottomButtons[i].setPosition(
            btnBox.getPosition().x + (btnBox.getSize().x - textBounds.width) / 2 - textBounds.left,
            btnBox.getPosition().y + (btnBox.getSize().y - textBounds.height) / 2 - textBounds.top
        );

        buttonBoxes.push_back(btnBox);
    }
}

void WindowView::render(sf::RenderWindow& window) {
    updateView(window);
    window.setView(view);

    window.draw(messageArea);
    window.draw(messageText);
    window.draw(gameField);
    window.draw(sidePanel);

    for (auto& box : labelBoxes) window.draw(box);
    for (auto& box : buttonBoxes) window.draw(box);

    window.draw(registerPromptLabel);
    window.draw(usernameInputField);
    window.draw(usernameInputText);
    window.draw(registerButton);
    window.draw(registerButtonText);

    window.draw(scoreLabel);
    window.draw(scoreListArea);
    window.draw(moneyText);
    window.draw(livesText);
    window.draw(chronoLabel);

    if (isCountingDown) {
        window.draw(waveCountdownText);
    }

    window.draw(mapLabel);
    for (auto& b : mapButtons) window.draw(b);
    window.draw(difficultyLabel);
    for (auto& b : difficultyButtons) window.draw(b);
    window.draw(towerLabel);
    for (auto& b : towerButtons) window.draw(b);
    window.draw(nextWaveBtn);
    window.draw(volumeLabel);
    window.draw(muteBox);
    window.draw(muteLabel);
    for (auto& b : bottomButtons) window.draw(b);

    window.draw(scrollBarBackground);
    window.draw(scrollBarThumb);

    float baseY = scoreListArea.getPosition().y + 5.f;
    const int visibleCount = 3;
    int totalEntries = static_cast<int>(scoreEntries.size());

    if (totalEntries > visibleCount) {
        float scrollHeight = scoreListArea.getSize().y;
        float thumbHeight = scrollHeight * (visibleCount / static_cast<float>(totalEntries));
        thumbHeight = std::max(20.f, thumbHeight);

        scrollBarThumb.setSize({scrollBarThumb.getSize().x, thumbHeight});

        float maxThumbY = scrollBarBackground.getPosition().y + scrollHeight - thumbHeight;
        float thumbY = scrollBarBackground.getPosition().y + scrollOffset * ((scrollHeight - thumbHeight) / (totalEntries - visibleCount));
        scrollBarThumb.setPosition(scrollBarBackground.getPosition().x, std::min(std::max(thumbY, scrollBarBackground.getPosition().y), maxThumbY));
    }

    for (size_t i = scrollOffset; i < scoreEntries.size() && i < scrollOffset + visibleCount; ++i) {
        scoreEntries[i].setPosition(scoreListArea.getPosition().x + 5.f, baseY + (i - scrollOffset) * 20.f);
        window.draw(scoreEntries[i]);
    }

    // Dans la fonction render()
    if (isMuted) {
        // Dessiner une croix (X)
        sf::RectangleShape line1({14, 2});
        sf::RectangleShape line2({14, 2});

        line1.setFillColor(sf::Color::White);
        line2.setFillColor(sf::Color::White);

        float centerX = muteBox.getPosition().x + muteBox.getSize().x / 2.0f;
        float centerY = muteBox.getPosition().y + muteBox.getSize().y / 2.0f;

        line1.setOrigin(7, 1);
        line2.setOrigin(7, 1);

        line1.setPosition(centerX, centerY);
        line2.setPosition(centerX, centerY);

        line1.rotate(45);
        line2.rotate(-45);

        window.draw(line1);
        window.draw(line2);
    }

    window.draw(volumeBarBackground);
    window.draw(volumeSlider);
}

void WindowView::handleClick(sf::Vector2f mousePos) {
    if (muteBox.getGlobalBounds().contains(mousePos)) {
        isMuted = !isMuted;
        if (volumeCallback) {
            volumeCallback(isMuted ? 0.0f : volume);
        }
        return;
    }

    std::string buttonId = getButtonId(mousePos);
    if (!buttonId.empty()) {
        if (clickCallback) {
            clickCallback(buttonId, mousePos);
        }
        return;
    }

    if (volumeBarBackground.getGlobalBounds().contains(mousePos)) {
        float localX = mousePos.x - volumeBarBackground.getPosition().x;
        float maxX = volumeBarBackground.getSize().x;
        float newVolume = std::min(std::max(localX / maxX, 0.0f), 1.0f);

        float sliderX = volumeBarBackground.getPosition().x + (newVolume * volumeBarBackground.getSize().x);
        float sliderY = volumeBarBackground.getPosition().y + volumeBarBackground.getSize().y / 2.0f;
        volumeSlider.setPosition(sliderX, sliderY);

        if (volumeCallback) {
            volumeCallback(newVolume);
        }
    }
}

std::string WindowView::getButtonId(sf::Vector2f mousePos) {
    if (registerButton.getGlobalBounds().contains(mousePos)) {
        return "register";
    }

    if (usernameInputField.getGlobalBounds().contains(mousePos)) {
        return "username_field";
    }

    if (muteBox.getGlobalBounds().contains(mousePos)) {
        return "mute_toggle";
    }

    for (int i = 0; i < 2; i++) {
        sf::FloatRect buttonBounds = buttonBoxes[i].getGlobalBounds();
        if (buttonBounds.contains(mousePos)) {
            return "map_" + std::to_string(i + 1);
        }
    }

    for (int i = 0; i < 3; i++) {
        sf::FloatRect buttonBounds = buttonBoxes[i + 2].getGlobalBounds();
        if (buttonBounds.contains(mousePos)) {
            return "difficulty_" + std::to_string(i + 1);
        }
    }

    for (int i = 0; i < 3; i++) {
        sf::FloatRect buttonBounds = buttonBoxes[i + 5].getGlobalBounds();
        if (buttonBounds.contains(mousePos)) {
            return "tower_" + std::to_string(i + 1);
        }
    }

    if (buttonBoxes[8].getGlobalBounds().contains(mousePos)) {
        return "next_wave";
    }

    const std::string bottomButtonIds[4] = {"start", "pause", "play", "quit"};
    for (int i = 0; i < 4; i++) {
        if (buttonBoxes[i + 9].getGlobalBounds().contains(mousePos)) {
            return bottomButtonIds[i];
        }
    }

    return "";
}

void WindowView::handleTextInput(sf::Uint32 unicode) {
    if (inputFieldActive && textInputCallback) {
        textInputCallback(unicode);
    }
}

void WindowView::handleScrollEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            bool scrollUp = (event.mouseWheelScroll.delta > 0);
            if (scrollCallback) {
                scrollCallback(scrollUp);
            }
        }
    }
}

void WindowView::setClickCallback(const std::function<void(const std::string&, sf::Vector2f)>& callback) {
    clickCallback = callback;
}

void WindowView::setVolumeCallback(const std::function<void(float)>& callback) {
    volumeCallback = callback;
}

void WindowView::setTextInputCallback(const std::function<void(sf::Uint32)>& callback) {
    textInputCallback = callback;
}

void WindowView::setScrollCallback(const std::function<void(bool)>& callback) {
    scrollCallback = callback;
}

void WindowView::setRegisterCallback(const std::function<void(const std::string&)>& callback) {
    registerCallback = callback;
}

void WindowView::updateScore(int score) {
    currentScore = score;
    scoreLabel.setString("SCORE: " + std::to_string(currentScore));
}

void WindowView::updateMoney(int money) {
    playerMoney = money;
    moneyText.setString("Gold: " + std::to_string(playerMoney));
}

void WindowView::updateLives(int lives) {
    baseLives = lives;
    livesText.setString("Lives: " + std::to_string(baseLives));
}

void WindowView::updateWaveCountdown(int countdown) {
    waveCountdown = countdown;
    waveCountdownText.setString("Next wave in: " + std::to_string(waveCountdown));
    isCountingDown = (countdown > 0);
}

void WindowView::setMessage(const std::string& message) {
    messageText.setString(message);
}

void WindowView::updateUsernameDisplay(const std::string& text) {
    currentUsernameInput = text;
    usernameInputText.setString(text);
}


void WindowView::updateVolumeDisplay(float newVolume, bool muted) {
    volume = newVolume;
    isMuted = muted;

    float sliderX = volumeBarBackground.getPosition().x + (volume * volumeBarBackground.getSize().x);
    float sliderY = volumeBarBackground.getPosition().y + volumeBarBackground.getSize().y / 2.0f;

    sliderX = std::min(
        std::max(sliderX, volumeBarBackground.getPosition().x),
        volumeBarBackground.getPosition().x + volumeBarBackground.getSize().x
    );

    volumeSlider.setPosition(sliderX, sliderY);
}

void WindowView::updateScrollDisplay(int offset) {
    scrollOffset = offset;
}

void WindowView::addScoreEntry(const std::string& entry) {
    sf::Text text;
    text.setFont(font);
    text.setString(entry);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);
    scoreEntries.push_back(text);
}
