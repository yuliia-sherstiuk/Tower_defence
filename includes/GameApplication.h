//
// Created by chris on 16/06/2025.
//

#ifndef GAMEAPPLICATION_H
#define GAMEAPPLICATION_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "logic/controllers/UIController.h"
#include "logic/controllers/EventController.h"
#include "graphics/views/WindowView.h"

class GameApplication {
private:
    sf::RenderWindow window;
    std::shared_ptr<UIController> uiController;
    std::shared_ptr<EventController> eventController;
    std::unique_ptr<WindowView> windowView;

public:
    GameApplication();
    ~GameApplication();
    void run();
};

#endif // GAMEAPPLICATION_H
