//WindowView.cpp


#include "graphics/views/WindowView.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <sstream>


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
    scoreLabel.setPosition(15, 15);


    scoreListArea.setSize({300, 200 / 3});
    scoreListArea.setFillColor(sf::Color(20, 20, 20));
    scoreListArea.setOutlineColor(sf::Color::White);
    scoreListArea.setOutlineThickness(2);
    scoreListArea.setPosition(scoreLabel.getPosition().x +90, scoreLabel.getPosition().y);

    sf::RectangleShape scoreBox;
    scoreBox.setSize({400,70});
    scoreBox.setFillColor(sf::Color::Transparent);
    scoreBox.setOutlineColor(sf::Color::White);
    scoreBox.setOutlineThickness(1);
    scoreBox.setPosition(scoreLabel.getPosition());
    labelBoxes.push_back(scoreBox);


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
    usernameLabel.setCharacterSize(15);
    usernameLabel.setFillColor(sf::Color::White);
    usernameLabel.setPosition(450, 15);

    sf::RectangleShape usernameBox;
    usernameBox.setSize({400, 70});
    usernameBox.setFillColor(sf::Color::Transparent);
    usernameBox.setOutlineColor(sf::Color::White);
    usernameBox.setOutlineThickness(1);
    usernameBox.setPosition(usernameLabel.getPosition());
    labelBoxes.push_back(usernameBox);

    moneyText.setFont(font);
    moneyText.setString("Money: ");
    moneyText.setCharacterSize(20);
    moneyText.setFillColor(sf::Color::White);
    moneyText.setPosition(900, 20);


	sf::RectangleShape moneyValueBox;
	moneyValueBox.setSize({60, 30});
	moneyValueBox.setFillColor(sf::Color::Transparent);
	moneyValueBox.setOutlineColor(sf::Color::White);
	moneyValueBox.setOutlineThickness(1);
	moneyValueBox.setPosition(moneyText.getPosition().x + 100, moneyText.getPosition().y - 1);
	labelBoxes.push_back(moneyValueBox);


    livesText.setFont(font);
    livesText.setString("Lives: ");
    livesText.setCharacterSize(20);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(900, 60);


	sf::RectangleShape livesValueBox;
	livesValueBox.setSize({60, 30});
	livesValueBox.setFillColor(sf::Color::Transparent);
	livesValueBox.setOutlineColor(sf::Color::White);
	livesValueBox.setOutlineThickness(1);
	livesValueBox.setPosition(livesText.getPosition().x + 100, livesText.getPosition().y - 1);
	labelBoxes.push_back(livesValueBox);

	sf::RectangleShape livesMoneyBox;
	livesMoneyBox.setSize({180, 90});
	livesMoneyBox.setFillColor(sf::Color::Transparent);
	livesMoneyBox.setOutlineColor(sf::Color::White);
	livesMoneyBox.setOutlineThickness(1);
	livesMoneyBox.setPosition(890, 10);
	labelBoxes.push_back(livesMoneyBox);


    chronoLabel.setFont(font);
    chronoLabel.setString("Chrono:");
	chronoLabel.setCharacterSize(20);
	chronoLabel.setFillColor(sf::Color::White);
	chronoLabel.setPosition(900, 110);


	sf::FloatRect chronoBounds = chronoLabel.getLocalBounds();
	sf::RectangleShape chronoBox({180, chronoBounds.height + 25});
	chronoBox.setFillColor(sf::Color::Transparent);
	chronoBox.setOutlineColor(sf::Color::White);
	chronoBox.setOutlineThickness(1);
	chronoBox.setPosition(890, chronoLabel.getPosition().y - 5);
	labelBoxes.push_back(chronoBox);


	chronoTimeText.setFont(font);
	chronoTimeText.setCharacterSize(20);
	chronoTimeText.setFillColor(sf::Color::White);
	chronoTimeText.setString(" ");
	chronoTimeText.setPosition(chronoLabel.getPosition().x + 100, chronoLabel.getPosition().y);


	sf::RectangleShape chronoTimeBox;
	chronoTimeBox.setSize({60, 30});
	chronoTimeBox.setFillColor(sf::Color::Transparent);
	chronoTimeBox.setOutlineColor(sf::Color::White);
	chronoTimeBox.setOutlineThickness(1);
	chronoTimeBox.setPosition(chronoTimeText.getPosition().x, chronoTimeText.getPosition().y );
	labelBoxes.push_back(chronoTimeBox);



    mapLabel.setFont(font);
    mapLabel.setString("MAP");
    mapLabel.setCharacterSize(20);
    mapLabel.setFillColor(sf::Color::White);
    mapLabel.setPosition(900,160);

	sf::RectangleShape mapContainer({180,85});
    mapContainer.setFillColor(sf::Color::Transparent);
    mapContainer.setOutlineColor(sf::Color::White);
    mapContainer.setOutlineThickness(1);
    mapContainer.setPosition(890, 150);
    labelBoxes.push_back(mapContainer);

    for (int i = 0; i < 2; i++) {
        mapButtons[i].setFont(font);
        mapButtons[i].setString(std::to_string(i + 1));
        mapButtons[i].setCharacterSize(20);
        mapButtons[i].setFillColor(sf::Color::White);
        mapButtons[i].setPosition(930 + i * 75, 200);

        sf::RectangleShape btnBox({30, 30});
        btnBox.setPosition(mapButtons[i].getPosition());
        btnBox.setFillColor(sf::Color::Transparent);
        btnBox.setOutlineColor(sf::Color::White);
        btnBox.setOutlineThickness(1);
        buttonBoxes.push_back(btnBox);
    }

    difficultyLabel.setFont(font);
    difficultyLabel.setString("DIFFICULTY");
    difficultyLabel.setCharacterSize(18);
    difficultyLabel.setFillColor(sf::Color::White);
    difficultyLabel.setPosition(900, 250);

    sf::RectangleShape difficultyContainer({180, 95});
    difficultyContainer.setFillColor(sf::Color::Transparent);
    difficultyContainer.setOutlineColor(sf::Color::White);
    difficultyContainer.setOutlineThickness(1);
    difficultyContainer.setPosition(890, 240);
    labelBoxes.push_back(difficultyContainer);




	const std::string difficultyLevels[3] = { "1", "2", "3" };
    	for (int i = 0; i < 3; i++) {
        difficultyButtons[i].setFont(font);
        difficultyButtons[i].setString(std::to_string(i + 1));
        difficultyButtons[i].setCharacterSize(20);
        difficultyButtons[i].setFillColor(sf::Color::White);
        difficultyButtons[i].setPosition(900 + i * 65, 300);

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
    towerLabel.setPosition(900, 350);

    sf::RectangleShape towerContainer({180, 95});
    towerContainer.setFillColor(sf::Color::Transparent);
    towerContainer.setOutlineColor(sf::Color::White);
    towerContainer.setOutlineThickness(1);
    towerContainer.setPosition(890, 340);
    labelBoxes.push_back(towerContainer);

    const std::string towerSymbols[3] = { "1", "2", "3" };
    for (int i = 0; i < 3; i++) {
        towerButtons[i].setFont(font);
        towerButtons[i].setString(towerSymbols[i]);
        towerButtons[i].setCharacterSize(20);
        towerButtons[i].setFillColor(sf::Color::White);
        towerButtons[i].setPosition(900 + i * 65, 400);

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
    nextWaveBtn.setPosition(900, 600);


	sf::RectangleShape nwBox({180, 30});
	nwBox.setPosition(890, 595);
	nwBox.setFillColor(sf::Color::Transparent);
	nwBox.setOutlineColor(sf::Color::White);
	nwBox.setOutlineThickness(1);
	buttonBoxes.push_back(nwBox);

    volumeLabel.setFont(font);
    volumeLabel.setString("VOLUME");
    volumeLabel.setCharacterSize(18);
    volumeLabel.setFillColor(sf::Color::White);
    volumeLabel.setPosition(900, 450);



    sf::RectangleShape volumeContainer({180, 135});
    volumeContainer.setFillColor(sf::Color::Transparent);
    volumeContainer.setOutlineColor(sf::Color::White);
    volumeContainer.setOutlineThickness(1);
    volumeContainer.setPosition(890, 440);
    labelBoxes.push_back(volumeContainer);

    volumeBarBackground.setSize({150, 5});
    volumeBarBackground.setFillColor(sf::Color(100, 100, 100));
    volumeBarBackground.setPosition(900, 500);

    volumeSlider.setRadius(8);
    volumeSlider.setFillColor(sf::Color::White);
    volumeSlider.setOrigin(8, 8);
    volumeSlider.setPosition(900 + volume * 150, 500);

    muteBox.setSize({20, 20});
    muteBox.setFillColor(sf::Color::Transparent);
    muteBox.setOutlineColor(sf::Color::White);
    muteBox.setOutlineThickness(2);
    muteBox.setPosition(900, 530);

    muteLabel.setFont(font);
    muteLabel.setString("Mute");
    muteLabel.setCharacterSize(18);
    muteLabel.setFillColor(sf::Color::White);
    muteLabel.setPosition(940, 530);

    const std::string labels[4] = { "START", "PAUSE", "PLAY", "QUIT"  };
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
	window.draw(chronoTimeText);
    // Отрисовка ползунка
    window.draw(scrollBarBackground);
    window.draw(scrollBarThumb);


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

    usernameInputBox.setSize({200, 30});
    usernameInputBox.setFillColor(sf::Color::Black);
    usernameInputBox.setOutlineColor(sf::Color::White);
    usernameInputBox.setOutlineThickness(2);
    usernameInputBox.setPosition(usernameLabel.getPosition().x, usernameLabel.getPosition().y + 30);


    usernameInputText.setFont(font);
    usernameInputText.setCharacterSize(18);
    usernameInputText.setFillColor(sf::Color::White);
    usernameInputText.setPosition(usernameInputBox.getPosition().x + 5, usernameInputBox.getPosition().y + 5);


    enterButtonShape.setSize({100, 30});
    enterButtonShape.setFillColor(sf::Color(70, 70, 70));
    enterButtonShape.setOutlineColor(sf::Color::White);
    enterButtonShape.setOutlineThickness(2);
    enterButtonShape.setPosition(
        usernameInputBox.getPosition().x + usernameInputBox.getSize().x + 10,
        usernameInputBox.getPosition().y
    );


    enterButtonText.setFont(font);
    enterButtonText.setString("Entrer");
    enterButtonText.setCharacterSize(18);
    enterButtonText.setFillColor(sf::Color::White);


    sf::FloatRect bounds = enterButtonText.getLocalBounds();
    enterButtonText.setPosition(
        enterButtonShape.getPosition().x + (enterButtonShape.getSize().x - bounds.width) / 2 - bounds.left,
        enterButtonShape.getPosition().y + (enterButtonShape.getSize().y - bounds.height) / 2 - bounds.top
    );


    usernameDisplayText.setFont(font);
    usernameDisplayText.setCharacterSize(18);
    usernameDisplayText.setFillColor(sf::Color::Green);
    usernameDisplayText.setPosition(usernameLabel.getPosition().x + 120, usernameLabel.getPosition().y);

    window.draw(usernameInputBox);
    window.draw(usernameInputText);


    window.draw(enterButtonShape);
    window.draw(enterButtonText);


    window.draw(usernameDisplayText);


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

void WindowView::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    // --- Обработка скролла (из handleScrollEvent) ---
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


    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b' && !currentUsernameInput.empty()) {
            currentUsernameInput.pop_back(); // удаление символа
        } else if (event.text.unicode < 128 && std::isprint(event.text.unicode)) {
            if (currentUsernameInput.size() < 20)
                currentUsernameInput += static_cast<char>(event.text.unicode);
        }
        usernameInputText.setString(currentUsernameInput);
    }


    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});

        if (enterButtonShape.getGlobalBounds().contains(mousePos)) {
            usernameDisplayText.setString(currentUsernameInput);

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
        std::cout << "Volume set to " << volume << std::endl;
        return;
    }

    for (size_t i = 0; i < buttonBoxes.size(); ++i) {
        if (buttonBoxes[i].getGlobalBounds().contains(mousePos)) {
            std::cout << "Button " << i << " clicked!" << std::endl;
        }
    }
}
