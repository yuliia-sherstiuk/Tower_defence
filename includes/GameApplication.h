//
// Created by chris on 16/06/2025.
//

#ifndef GAMEAPPLICATION_H
#define GAMEAPPLICATION_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "graphics/views/WindowView.h"
#include "logic/controllers/UIController.h"
#include "logic/controllers/EventController.h"

class GameApplication {
public:
    GameApplication();
    ~GameApplication();

    void run();

private:
    sf::RenderWindow window;
    std::unique_ptr<WindowView> windowView;
    std::shared_ptr<UIController> uiController;
    std::shared_ptr<EventController> eventController;
    bool applicationRunning;
};

#endif // GAMEAPPLICATION_H