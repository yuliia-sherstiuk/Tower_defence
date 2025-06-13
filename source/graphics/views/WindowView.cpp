#include "graphics/views/WindowView.h"
#include <iostream>
#include <algorithm>

WindowView::WindowView() {
    if (!font.loadFromFile("assets/Space_Grotesk.ttf")) {
        std::cerr << "Failed to load font\n";
    }
    setupUI();
}

void WindowView::setupUI() {
    gameField.setSize({850, 540});
    gameField.setFillColor(sf::Color(30, 30, 30));
    gameField.setPosition(10, 100);

    sf::RectangleShape topPanel;
    topPanel.setSize({850, 80});
    topPanel.setFillColor(sf::Color(40, 40, 40));
    topPanel.setPosition(10, 10);
    labelBoxes.push_back(topPanel);

    sidePanel.setSize({220, 630});
    sidePanel.setFillColor(sf::Color(50, 50, 50));
    sidePanel.setPosition(870, 10);

    scoreLabel.setFont(font);
    scoreLabel.setString("SCORE");
    scoreLabel.setCharacterSize(15);
    scoreLabel.setFillColor(sf::Color::White);
    scoreLabel.setPosition(20, 20);

    // Область для списка очков
    scoreListArea.setSize({180, 200 / 3});
    scoreListArea.setFillColor(sf::Color(20, 20, 20));
    scoreListArea.setOutlineColor(sf::Color::White);
    scoreListArea.setOutlineThickness(2);
    scoreListArea.setPosition(scoreLabel.getPosition().x, scoreLabel.getPosition().y + 40);

    sf::RectangleShape scoreBox;
    scoreBox.setSize({140, 30});
    scoreBox.setFillColor(sf::Color::Transparent);
    scoreBox.setOutlineColor(sf::Color::White);
    scoreBox.setOutlineThickness(2);
    scoreBox.setPosition(scoreLabel.getPosition());
    labelBoxes.push_back(scoreBox);

    // Ползунок для списка очков
    scrollBarBackground.setSize({10.f, scoreListArea.getSize().y});
    scrollBarBackground.setFillColor(sf::Color(50, 50, 50));
    scrollBarBackground.setPosition(
        scoreListArea.getPosition().x + scoreListArea.getSize().x,
        scoreListArea.getPosition().y
    );

    scrollBarThumb.setSize({10.f, scoreListArea.getSize().y / 3});
    scrollBarThumb.setFillColor(sf::Color::White);
    scrollBarThumb.setPosition(scrollBarBackground.getPosition());
    usernameLabel.setFont(font);
    usernameLabel.setString("USERNAME");
    usernameLabel.setCharacterSize(24);
    usernameLabel.setFillColor(sf::Color::White);
    usernameLabel.setPosition(400, 20);

    sf::RectangleShape usernameBox;
    usernameBox.setSize({140, 30});
    usernameBox.setFillColor(sf::Color::Transparent);
    usernameBox.setOutlineColor(sf::Color::White);
    usernameBox.setOutlineThickness(2);
    usernameBox.setPosition(usernameLabel.getPosition());
    labelBoxes.push_back(usernameBox);

    moneyText.setFont(font);
    moneyText.setString("Money: 100");
    moneyText.setCharacterSize(20);
    moneyText.setFillColor(sf::Color::White);
    moneyText.setPosition(890, 20);

    sf::RectangleShape moneyBox = scoreBox;
    moneyBox.setPosition(moneyText.getPosition());
    labelBoxes.push_back(moneyBox);

    livesText.setFont(font);
    livesText.setString("Lives: 100");
    livesText.setCharacterSize(20);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(890, 50);
    sf::RectangleShape livesBox = scoreBox;
    livesBox.setPosition(livesText.getPosition());
    labelBoxes.push_back(livesBox);

    chronoLabel.setFont(font);
    chronoLabel.setString("CHRONO");
    chronoLabel.setCharacterSize(20);
    chronoLabel.setFillColor(sf::Color::White);
    chronoLabel.setPosition(890, 120);
    sf::RectangleShape chronoBox = scoreBox;
    chronoBox.setPosition(chronoLabel.getPosition());
    labelBoxes.push_back(chronoBox);

    mapLabel.setFont(font);
    mapLabel.setString("MAP");
    mapLabel.setCharacterSize(20);
    mapLabel.setFillColor(sf::Color::White);
    mapLabel.setPosition(890, 200);
    sf::RectangleShape mapBox = scoreBox;
    mapBox.setPosition(mapLabel.getPosition());
    labelBoxes.push_back(mapBox);

    for (int i = 0; i < 2; i++) {
        mapButtons[i].setFont(font);
        mapButtons[i].setString(std::to_string(i + 1));
        mapButtons[i].setCharacterSize(20);
        mapButtons[i].setFillColor(sf::Color::White);
        mapButtons[i].setPosition(890 + i * 40, 250);

        sf::RectangleShape btnBox({30, 30});
        btnBox.setPosition(mapButtons[i].getPosition());
        btnBox.setFillColor(sf::Color::Transparent);
        btnBox.setOutlineColor(sf::Color::White);
        btnBox.setOutlineThickness(1);
        buttonBoxes.push_back(btnBox);
    }

    difficultyLabel.setFont(font);
    difficultyLabel.setString("Difficulty");
    difficultyLabel.setCharacterSize(18);
    difficultyLabel.setFillColor(sf::Color::White);
    difficultyLabel.setPosition(890, 300);
    sf::RectangleShape diffBox = scoreBox;
    diffBox.setPosition(difficultyLabel.getPosition());
    labelBoxes.push_back(diffBox);

    for (int i = 0; i < 3; i++) {
        difficultyButtons[i].setFont(font);
        difficultyButtons[i].setString(std::to_string(i + 1));
        difficultyButtons[i].setCharacterSize(20);
        difficultyButtons[i].setFillColor(sf::Color::White);
        difficultyButtons[i].setPosition(890 + i * 35, 350);

        sf::RectangleShape btnBox({30, 30});
        btnBox.setPosition(difficultyButtons[i].getPosition());
        btnBox.setFillColor(sf::Color::Transparent);
        btnBox.setOutlineColor(sf::Color::White);
        btnBox.setOutlineThickness(1);
        buttonBoxes.push_back(btnBox);
    }

    towerLabel.setFont(font);
    towerLabel.setString("TOWER");
    towerLabel.setCharacterSize(18);
    towerLabel.setFillColor(sf::Color::White);
    towerLabel.setPosition(890, 400);
    sf::RectangleShape towerBox = scoreBox;
    towerBox.setPosition(towerLabel.getPosition());
    labelBoxes.push_back(towerBox);

    const std::string towerSymbols[3] = { "1", "2", "3" };
    for (int i = 0; i < 3; i++) {
        towerButtons[i].setFont(font);
        towerButtons[i].setString(towerSymbols[i]);
        towerButtons[i].setCharacterSize(20);
        towerButtons[i].setFillColor(sf::Color::White);
        towerButtons[i].setPosition(890 + i * 35, 450);

        sf::RectangleShape btnBox({30, 30});
        btnBox.setPosition(towerButtons[i].getPosition());
        btnBox.setFillColor(sf::Color::Transparent);
        btnBox.setOutlineColor(sf::Color::White);
        btnBox.setOutlineThickness(1);
        buttonBoxes.push_back(btnBox);
    }

    nextWaveBtn.setFont(font);
    nextWaveBtn.setString("NEXT WAVE");
    nextWaveBtn.setCharacterSize(18);
    nextWaveBtn.setFillColor(sf::Color::White);
    nextWaveBtn.setPosition(890, 500);
    sf::RectangleShape nwBox({140, 30});
    nwBox.setPosition(nextWaveBtn.getPosition());
    nwBox.setFillColor(sf::Color::Transparent);
    nwBox.setOutlineColor(sf::Color::White);
    nwBox.setOutlineThickness(1);
    buttonBoxes.push_back(nwBox);

    volumeLabel.setFont(font);
    volumeLabel.setString("Volume");
    volumeLabel.setCharacterSize(18);
    volumeLabel.setFillColor(sf::Color::White);
    volumeLabel.setPosition(890, 540);
    labelBoxes.push_back(scoreBox);
    labelBoxes.back().setPosition(volumeLabel.getPosition());

    volumeBarBackground.setSize({150, 5});
    volumeBarBackground.setFillColor(sf::Color(100, 100, 100));
    volumeBarBackground.setPosition(890, 580);

    volumeSlider.setRadius(8);
    volumeSlider.setFillColor(sf::Color::White);
    volumeSlider.setOrigin(8, 8);
    volumeSlider.setPosition(890 + volume * 150, 580);

    muteBox.setSize({20, 20});
    muteBox.setFillColor(sf::Color::Transparent);
    muteBox.setOutlineColor(sf::Color::White);
    muteBox.setOutlineThickness(2);
    muteBox.setPosition(890, 600);

    muteLabel.setFont(font);
    muteLabel.setString("Mute");
    muteLabel.setCharacterSize(18);
    muteLabel.setFillColor(sf::Color::White);
    muteLabel.setPosition(915, 610);

    const std::string labels[4] = { "START", "PAUSE", "PLAY", "QUIT" };
    for (int i = 0; i < 4; i++) {
        bottomButtons[i].setFont(font);
        bottomButtons[i].setString(labels[i]);
        bottomButtons[i].setCharacterSize(18);
        bottomButtons[i].setFillColor(sf::Color::White);

        sf::RectangleShape btnBox({100, 30});
        btnBox.setPosition(20 + i * 242, 650);
        btnBox.setFillColor(sf::Color::Transparent);
        btnBox.setOutlineColor(sf::Color::White);
        btnBox.setOutlineThickness(2);

        sf::FloatRect textBounds = bottomButtons[i].getLocalBounds();


        bottomButtons[i].setPosition(
            btnBox.getPosition().x + (btnBox.getSize().x - textBounds.width) / 2 - textBounds.left,
            btnBox.getPosition().y + (btnBox.getSize().y - textBounds.height) / 2 - textBounds.top
        );

        buttonBoxes.push_back(btnBox);
    }



    inputField.setFont(font);
    inputField.setCharacterSize(18);
    inputField.setFillColor(sf::Color::White);
    inputField.setPosition(20, 700);
}

void WindowView::render(sf::RenderWindow& window) {
    window.draw(gameField);
    window.draw(sidePanel);

    for (auto& box : labelBoxes) window.draw(box);
    for (auto& box : buttonBoxes) window.draw(box);
    window.draw(usernameLabel);
    window.draw(scoreLabel);
    window.draw(scoreListArea);
    window.draw(moneyText);
    window.draw(livesText);
    window.draw(chronoLabel);
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
    window.draw(inputField);

    // Отрисовка ползунка
    window.draw(scrollBarBackground);
    window.draw(scrollBarThumb);

    // Отрисовка элементов списка
    float baseY = scoreListArea.getPosition().y + 5.f;
    int visibleCount = 10 / 3;
    int totalEntries = static_cast<int>(scoreEntries.size());

    if (totalEntries > visibleCount) {
        float scrollHeight = scoreListArea.getSize().y;
        float thumbHeight = scrollHeight * (visibleCount / static_cast<float>(totalEntries));
        thumbHeight = std::max(20.f / 3, thumbHeight);

        scrollBarThumb.setSize({scrollBarThumb.getSize().x, thumbHeight});

        float maxThumbY = scrollBarBackground.getPosition().y + scrollHeight - thumbHeight;
        float thumbY = scrollBarBackground.getPosition().y + scrollOffset * ((scrollHeight - thumbHeight) / (totalEntries - visibleCount));
        scrollBarThumb.setPosition(scrollBarBackground.getPosition().x, std::clamp(thumbY, scrollBarBackground.getPosition().y, maxThumbY));
    }

    for (size_t i = scrollOffset; i < scoreEntries.size() && i < scrollOffset + visibleCount; ++i) {
        scoreEntries[i].setPosition(scoreListArea.getPosition().x + 5.f, baseY + (i - scrollOffset) * 20.f);
        window.draw(scoreEntries[i]);
    }

    if (isMuted) {
        sf::RectangleShape checkMark({14, 14});
        checkMark.setFillColor(sf::Color::White);
        checkMark.setPosition(muteBox.getPosition().x + 3, muteBox.getPosition().y + 3);
        window.draw(checkMark);
    }

    window.draw(volumeBarBackground);
    window.draw(volumeSlider);
}

void WindowView::updateVolumeSliderPosition() {
    float x = volumeBarBackground.getPosition().x + volume * volumeBarBackground.getSize().x;
    float y = volumeBarBackground.getPosition().y + volumeBarBackground.getSize().y / 2.f;
    volumeSlider.setPosition(x, y);
}

void WindowView::setInputText(const std::string& text) {
    inputText = text;
    inputField.setFont(font);
    inputField.setString(text);
    inputField.setCharacterSize(18);
    inputField.setFillColor(sf::Color::White);
    inputField.setPosition(20, 700);
}

void WindowView::addUsername(const std::string& name) {
    usernames.push_back(name);

    sf::Text text;
    text.setFont(font);
    text.setString(name);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);
    scoreEntries.push_back(text);
}

void WindowView::scrollUp() {
    if (scrollOffset > 0) {
        scrollOffset--;
    }
}

void WindowView::scrollDown() {
    if ((scrollOffset + 1) * 20 < static_cast<int>(scoreEntries.size()) * 20) {
        scrollOffset++;
    }
}

void WindowView::handleScrollEvent(const sf::Event& event) {
    int visibleCount = 10;

    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            if (event.mouseWheelScroll.delta < 0) {
                if (scrollOffset + visibleCount < scoreEntries.size())
                    scrollOffset++;
            } else {
                if (scrollOffset > 0)
                    scrollOffset--;
            }
        }
    }
}

void WindowView::handleClick(sf::Vector2f mousePos) {
    if (muteBox.getGlobalBounds().contains(mousePos)) {
        isMuted = !isMuted;
        volume = isMuted ? 0.f : 1.f;
        updateVolumeSliderPosition();
        return;
    }

    if (volumeBarBackground.getGlobalBounds().contains(mousePos)) {
        float localX = mousePos.x - volumeBarBackground.getPosition().x;
        volume = std::clamp(localX / volumeBarBackground.getSize().x, 0.f, 1.f);
        isMuted = (volume == 0.f);
        updateVolumeSliderPosition();
        return;
    }

    for (size_t i = 0; i < buttonBoxes.size(); ++i) {
        if (buttonBoxes[i].getGlobalBounds().contains(mousePos)) {
            std::cout << "Button " << i << " clicked!" << std::endl;
        }
    }
}
