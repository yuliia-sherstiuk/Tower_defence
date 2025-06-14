#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>
#include "graphics/views/WindowView.h"

sf::RectangleShape createLabelBox(sf::Vector2f position, sf::Vector2f size = {140, 30}) {
    sf::RectangleShape box(size);
    box.setFillColor(sf::Color::Transparent);
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(2);
    box.setPosition(position);
    return box;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1100, 700), "Tower Defense UI");
    window.setFramerateLimit(60);

    WindowView view;

    std::string inputBuffer;
    bool inputActive = true;


    sf::Clock chronoClock;
    bool isChronoRunning = true;

    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    sf::Text chronoTimeText;
    chronoTimeText.setFont(font);
    chronoTimeText.setCharacterSize(20);
    chronoTimeText.setFillColor(sf::Color::White);
    chronoTimeText.setPosition(1000, 110);
    chronoTimeText.setString("00:00");

    sf::RectangleShape chronoBox = createLabelBox({1000, 110}, {60, 30});

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::TextEntered && inputActive) {
                if (event.text.unicode == '\b') {
                    if (!inputBuffer.empty()) {
                        inputBuffer.pop_back();
                        view.setInputText(inputBuffer);
                    }
                } else if (event.text.unicode < 128 && std::isprint(event.text.unicode)) {
                    if (inputBuffer.length() < 20) {
                        inputBuffer += static_cast<char>(event.text.unicode);
                        view.setInputText(inputBuffer);
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                sf::FloatRect enterBounds(160, 110, 70, 25);
                if (enterBounds.contains(mousePos)) {
                    view.addUsername(inputBuffer);
                    inputBuffer.clear();
                    view.setInputText("");
                }

                view.handleClick(mousePos);
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    view.scrollUp();
                }
                if (event.key.code == sf::Keyboard::Down) {
                    view.scrollDown();
                }
            }
        }


        if (isChronoRunning) {
            sf::Time elapsed = chronoClock.getElapsedTime();
            int seconds = static_cast<int>(elapsed.asSeconds());
            int minutes = seconds / 60;
            seconds = seconds % 60;

            std::ostringstream oss;
            oss << std::setfill('0') << std::setw(2) << minutes << ":"
                << std::setfill('0') << std::setw(2) << seconds;
            chronoTimeText.setString(oss.str());
        }

        window.clear();
        view.render(window);


        window.draw(chronoBox);
        window.draw(chronoTimeText);

        window.display();
    }

    return 0;
}


