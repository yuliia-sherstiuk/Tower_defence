#include "graphics/views/WindowView.h"
#include <iostream>

WindowView::WindowView() {
    if (!font.loadFromFile("assets/Space_Grotesk.ttf")) {
        std::cerr << "Failed to load font\n";
    }
    setupUI();
}

void WindowView::setupUI() {
    // Game Field (larger)
    gameField.setSize(sf::Vector2f(800, 600));
    gameField.setFillColor(sf::Color(30, 30, 30));
    gameField.setPosition(20, 20);

    // Right Panel
    sidePanel.setSize(sf::Vector2f(240, 600));
    sidePanel.setFillColor(sf::Color(50, 50, 50));
    sidePanel.setPosition(740, 20);


    // Labels
    scoreLabel.setFont(font);
    scoreLabel.setString("SCORE");
    scoreLabel.setCharacterSize(24);
    scoreLabel.setFillColor(sf::Color::White);
    scoreLabel.setPosition(30, 30);


    // Username
    scoreLabel.setFont(font);
    scoreLabel.setString("USERNAME");
    scoreLabel.setCharacterSize(24);
    scoreLabel.setFillColor(sf::Color::White);
    scoreLabel.setPosition(400, 30);





    moneyText.setFont(font);
    moneyText.setString("Money: 100");
    moneyText.setCharacterSize(20);
    moneyText.setFillColor(sf::Color::White);
    moneyText.setPosition(750, 30);

    livesText.setFont(font);
    livesText.setString("Lives: 100");
    livesText.setCharacterSize(20);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(750, 60);

    chronoLabel.setFont(font);
    chronoLabel.setString("CHRONO");
    chronoLabel.setCharacterSize(20);
    chronoLabel.setFillColor(sf::Color::White);
    chronoLabel.setPosition(750, 100);

    // Map Section
    mapLabel.setFont(font);
    mapLabel.setString("MAP");
    mapLabel.setCharacterSize(20);
    mapLabel.setFillColor(sf::Color::White);
    mapLabel.setPosition(750, 140);

    for (int i = 0; i < 2; i++) {
        mapButtons[i].setFont(font);
        mapButtons[i].setString(std::to_string(i + 1));
        mapButtons[i].setCharacterSize(20);
        mapButtons[i].setFillColor(sf::Color(255, 255, 255));
        mapButtons[i].setPosition(750 + i * 40, 170);
    }

    // Difficulty
    difficultyLabel.setFont(font);
    difficultyLabel.setString("Difficulty");
    difficultyLabel.setCharacterSize(18);
    difficultyLabel.setFillColor(sf::Color::White);
    difficultyLabel.setPosition(750, 210);

    for (int i = 0; i < 3; i++) {
        difficultyButtons[i].setFont(font);
        difficultyButtons[i].setString(std::to_string(i + 1));
        difficultyButtons[i].setCharacterSize(20);
        difficultyButtons[i].setFillColor(sf::Color::White);
        difficultyButtons[i].setPosition(750 + i * 35, 240);
    }

    // Towers
    towerLabel.setFont(font);
    towerLabel.setString("TAWER");
    towerLabel.setCharacterSize(18);
    towerLabel.setFillColor(sf::Color::White);
    towerLabel.setPosition(750, 280);

    const std::string towerSymbols[3] = { "1", "2", "3" };
    for (int i = 0; i < 3; i++) {
        towerButtons[i].setFont(font);
        towerButtons[i].setString(towerSymbols[i]);
        towerButtons[i].setCharacterSize(20);
        towerButtons[i].setFillColor(sf::Color::White);
        towerButtons[i].setPosition(750 + i * 35, 310);
    }

    // Next Wave
    nextWaveBtn.setFont(font);
    nextWaveBtn.setString("NEXT WAVE");
    nextWaveBtn.setCharacterSize(18);
    nextWaveBtn.setFillColor(sf::Color::White);
    nextWaveBtn.setPosition(750, 360);

    // Bottom buttons
    const std::string labels[5] = { "START", "PAUSE", "PLAY", " NEXT WAVE ", "QUIT" };
    for (int i = 0; i < 5; i++) {
        bottomButtons[i].setFont(font);
        bottomButtons[i].setString(labels[i]);
        bottomButtons[i].setCharacterSize(18);
        bottomButtons[i].setFillColor(sf::Color::White);
        bottomButtons[i].setPosition(20 + i * 120 , 650);
    }
}

void WindowView::render(sf::RenderWindow& window) {
    window.draw(gameField);
    window.draw(sidePanel);
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
}