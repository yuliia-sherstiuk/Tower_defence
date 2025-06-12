#include <SFML/Graphics.hpp>
#include "graphics/views/WindowView.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Tower Defense UI");
    WindowView view;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        view.render(window);
        window.display();
    }

    return 0;
}