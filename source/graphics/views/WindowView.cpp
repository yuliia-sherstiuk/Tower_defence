#include "graphics/views/WindowView.h"
#include <iostream>

WindowView::WindowView() {
    if (!font.loadFromFile("assets/Space_Grotesk.ttf")) {
        std::cerr << "Failed to load font\n";
    }
    setupUI();
}

void WindowView::setupUI() {
    gameField.setSize({800, 600});
    gameField.setFillColor(sf::Color(30, 30, 30));
    gameField.setPosition(20, 20);

    sidePanel.setSize({240, 600});
    sidePanel.setFillColor(sf::Color(50, 50, 50));
    sidePanel.setPosition(740, 20);

    // SCORE label
    scoreLabel.setFont(font);
    scoreLabel.setString("SCORE");
    scoreLabel.setCharacterSize(24);
    scoreLabel.setFillColor(sf::Color::White);
    scoreLabel.setPosition(750, 30);  // Сдвинем вправо

    sf::RectangleShape scoreBox;
    scoreBox.setSize({140, 30});  // Чуть больше
    scoreBox.setFillColor(sf::Color::Transparent);
    scoreBox.setOutlineColor(sf::Color::White);
    scoreBox.setOutlineThickness(2);
    scoreBox.setPosition(scoreLabel.getPosition());
    labelBoxes.push_back(scoreBox);
    // USERNAME
    usernameLabel.setFont(font);
    usernameLabel.setString("USERNAME");
    usernameLabel.setCharacterSize(24);
    usernameLabel.setFillColor(sf::Color::White);
    usernameLabel.setPosition(750, 0);  // Позиция выше SCORE

    sf::RectangleShape usernameBox;
    usernameBox.setSize({140, 30});
    usernameBox.setFillColor(sf::Color::Transparent);
    usernameBox.setOutlineColor(sf::Color::White);
    usernameBox.setOutlineThickness(2);
    usernameBox.setPosition(usernameLabel.getPosition());
    labelBoxes.push_back(usernameBox);
    // Money
    moneyText.setFont(font);
    moneyText.setString("Money: 100");
    moneyText.setCharacterSize(20);
    moneyText.setFillColor(sf::Color::White);
    moneyText.setPosition(750, 30);

    sf::RectangleShape moneyBox = scoreBox;
    moneyBox.setPosition(moneyText.getPosition());
    labelBoxes.push_back(moneyBox);

    // Lives
    livesText.setFont(font);
    livesText.setString("Lives: 100");
    livesText.setCharacterSize(20);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(750, 60);
    sf::RectangleShape livesBox = scoreBox;
    livesBox.setPosition(livesText.getPosition());
    labelBoxes.push_back(livesBox);

    // CHRONO
    chronoLabel.setFont(font);
    chronoLabel.setString("CHRONO");
    chronoLabel.setCharacterSize(20);
    chronoLabel.setFillColor(sf::Color::White);
    chronoLabel.setPosition(750, 100);
    sf::RectangleShape chronoBox = scoreBox;
    chronoBox.setPosition(chronoLabel.getPosition());
    labelBoxes.push_back(chronoBox);

    // MAP
    mapLabel.setFont(font);
    mapLabel.setString("MAP");
    mapLabel.setCharacterSize(20);
    mapLabel.setFillColor(sf::Color::White);
    mapLabel.setPosition(750, 140);
    sf::RectangleShape mapBox = scoreBox;
    mapBox.setPosition(mapLabel.getPosition());
    labelBoxes.push_back(mapBox);

    for (int i = 0; i < 2; i++) {
        mapButtons[i].setFont(font);
        mapButtons[i].setString(std::to_string(i + 1));
        mapButtons[i].setCharacterSize(20);
        mapButtons[i].setFillColor(sf::Color::White);
        mapButtons[i].setPosition(750 + i * 40, 170);

        sf::RectangleShape btnBox({30, 30});
        btnBox.setPosition(mapButtons[i].getPosition());
        btnBox.setFillColor(sf::Color::Transparent);
        btnBox.setOutlineColor(sf::Color::White);
        btnBox.setOutlineThickness(1);
        buttonBoxes.push_back(btnBox);
    }

    // Difficulty
    difficultyLabel.setFont(font);
    difficultyLabel.setString("Difficulty");
    difficultyLabel.setCharacterSize(18);
    difficultyLabel.setFillColor(sf::Color::White);
    difficultyLabel.setPosition(750, 210);
    sf::RectangleShape diffBox = scoreBox;
    diffBox.setPosition(difficultyLabel.getPosition());
    labelBoxes.push_back(diffBox);

    for (int i = 0; i < 3; i++) {
        difficultyButtons[i].setFont(font);
        difficultyButtons[i].setString(std::to_string(i + 1));
        difficultyButtons[i].setCharacterSize(20);
        difficultyButtons[i].setFillColor(sf::Color::White);
        difficultyButtons[i].setPosition(750 + i * 35, 240);

        sf::RectangleShape btnBox({30, 30});
        btnBox.setPosition(difficultyButtons[i].getPosition());
        btnBox.setFillColor(sf::Color::Transparent);
        btnBox.setOutlineColor(sf::Color::White);
        btnBox.setOutlineThickness(1);
        buttonBoxes.push_back(btnBox);
    }

    // TAWER
    towerLabel.setFont(font);
    towerLabel.setString("TOWER");
    towerLabel.setCharacterSize(18);
    towerLabel.setFillColor(sf::Color::White);
    towerLabel.setPosition(750, 280);
    sf::RectangleShape towerBox = scoreBox;
    towerBox.setPosition(towerLabel.getPosition());
    labelBoxes.push_back(towerBox);

    const std::string towerSymbols[3] = { "1", "2", "3" };
    for (int i = 0; i < 3; i++) {
        towerButtons[i].setFont(font);
        towerButtons[i].setString(towerSymbols[i]);
        towerButtons[i].setCharacterSize(20);
        towerButtons[i].setFillColor(sf::Color::White);
        towerButtons[i].setPosition(750 + i * 35, 310);

        sf::RectangleShape btnBox({30, 30});
        btnBox.setPosition(towerButtons[i].getPosition());
        btnBox.setFillColor(sf::Color::Transparent);
        btnBox.setOutlineColor(sf::Color::White);
        btnBox.setOutlineThickness(1);
        buttonBoxes.push_back(btnBox);
    }

    // NEXT WAVE
    nextWaveBtn.setFont(font);
    nextWaveBtn.setString("NEXT WAVE");
    nextWaveBtn.setCharacterSize(18);
    nextWaveBtn.setFillColor(sf::Color::White);
    nextWaveBtn.setPosition(750, 360);
    sf::RectangleShape nwBox({140, 30});
    nwBox.setPosition(nextWaveBtn.getPosition());
    nwBox.setFillColor(sf::Color::Transparent);
    nwBox.setOutlineColor(sf::Color::White);
    nwBox.setOutlineThickness(1);
    buttonBoxes.push_back(nwBox);

    const std::string labels[5] = { "START", "PAUSE", "PLAY",  "QUIT" };
    for (int i = 0; i < 4; i++) {
        bottomButtons[i].setFont(font);
        bottomButtons[i].setString(labels[i]);
        bottomButtons[i].setCharacterSize(18);
        bottomButtons[i].setFillColor(sf::Color::White);
        bottomButtons[i].setPosition(20 + i * 120, 650);

        sf::RectangleShape btnBox({100, 30});
        btnBox.setPosition(bottomButtons[i].getPosition());
        btnBox.setFillColor(sf::Color::Transparent);
        btnBox.setOutlineColor(sf::Color::White);
        btnBox.setOutlineThickness(2);
        buttonBoxes.push_back(btnBox);
    }


    inputField.setFont(font);
    inputField.setCharacterSize(18);
    inputField.setFillColor(sf::Color::White);
    inputField.setPosition(20, 700); // изменить при необходимости
}

void WindowView::render(sf::RenderWindow& window) {
    window.draw(gameField);
    window.draw(sidePanel);

    for (auto& box : labelBoxes) window.draw(box);
    for (auto& box : buttonBoxes) window.draw(box);
    window.draw(usernameLabel);
    window.draw(scoreLabel);
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
    for (auto& b : bottomButtons) window.draw(b);

    // 👇 ДОБАВЬ ЭТО
    window.draw(inputField);

    float baseY = 100.f;
    int visibleCount = 10;
    for (int i = scrollOffset; i < static_cast<int>(scoreEntries.size()) && i < scrollOffset + visibleCount; ++i) {
        scoreEntries[i].setPosition(30.f, baseY + (i - scrollOffset) * 20.f);
        window.draw(scoreEntries[i]);
    }
}


void WindowView::setInputText(const std::string& text) {
    inputText = text;
    inputField.setFont(font);
    inputField.setString(text);
    inputField.setCharacterSize(18);
    inputField.setFillColor(sf::Color::White);
    inputField.setPosition(20, 700);  // примерная позиция, измени по желанию
}


void WindowView::addUsername(const std::string& name) {
    usernames.push_back(name);

    sf::Text text;
    text.setFont(font);
    text.setString(name);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);
    float yOffset = 100.f + (scoreEntries.size() - scrollOffset) * 20.f;
    text.setPosition(30.f, yOffset);
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

void WindowView::handleClick(sf::Vector2f mousePos) {
    for (size_t i = 0; i < buttonBoxes.size(); ++i) {
        if (buttonBoxes[i].getGlobalBounds().contains(mousePos)) {
            std::cout << "Button " << i << " clicked!" << std::endl;

            // Реакция на кнопки по индексу
            switch (i) {
                case 0:
                    std::cout << "Action for button 0\n";
                    break;
                case 1:
                    std::cout << "Action for button 1\n";
                    break;
                    // добавь больше по необходимости
            }
        }
    }
}