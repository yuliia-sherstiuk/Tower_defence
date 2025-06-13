#include "../../../includes/graphics/views/towerView.h"

void towerView::displayTower(Tower *tower) {

    sf::Texture texture{};

    if (!texture.loadFromFile(tower->spritePath)) {
        std::cerr << "Failed to load sprite texture" << std::endl;
    }

}
