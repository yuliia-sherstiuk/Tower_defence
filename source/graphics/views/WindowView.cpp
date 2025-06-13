#include "../../../includes/graphics/views/WindowView.h"

WindowView::WindowView(sf::RenderWindow& window, Game* game)
    : window(window), game(game) {}

void WindowView::render() {
    window.clear(sf::Color::Black);

    /* Add methods
     * drawTowers();
     * drawEnemies();
     * drawUI();
    */
    window.display();
}

// add methods to draw