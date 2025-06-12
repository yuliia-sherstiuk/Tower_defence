#include <SFML/Graphics.hpp>
#include "graphics/views/WindowView.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1100, 700), "Tower Defense UI");
    window.setFramerateLimit(60);

    WindowView view;

    std::string inputBuffer;
    bool inputActive = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Закрытие окна
            if (event.type == sf::Event::Closed)
                window.close();

            // Ввод текста
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

            // Обработка мыши
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                // Кнопка [entrer]
                sf::FloatRect enterBounds(160, 110, 70, 25);
                if (enterBounds.contains(mousePos)) {
                    view.addUsername(inputBuffer);
                    inputBuffer.clear();
                    view.setInputText("");
                }

                // Другие кнопки
                view.handleClick(mousePos);
            }

            // Прокрутка списка стрелками
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    view.scrollUp();
                }
                if (event.key.code == sf::Keyboard::Down) {
                    view.scrollDown();
                }
            }
        }

        window.clear();
        view.render(window);
        window.display();
    }

    return 0;
}
