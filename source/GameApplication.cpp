//
// Created by chris on 16/06/2025.
//

#include "GameApplication.h"
#include <iostream>

GameApplication::GameApplication()
    : window(sf::VideoMode(2160, 1440), "Tower Defense Game")
    , windowView(std::make_unique<WindowView>(window))
    , uiController(std::make_shared<UIController>())
    , eventController(std::make_shared<EventController>())
    , applicationRunning(true)
{
    std::cout << "[DEBUG] GameApplication: Constructor - Setting up controllers" << std::endl;

    // Connect all controllers together
    uiController->connectWithWindowView(windowView.get());
    uiController->connectWithEventController(eventController);

    //Callback to close the app
    uiController->setApplicationQuitCallback([this]() {
        std::cout << "[DEBUG] GameApplication: Application quit requested" << std::endl;
        applicationRunning = false;
        window.close();
    });

    std::cout << "[DEBUG] GameApplication: All controllers connected successfully" << std::endl;
}

GameApplication::~GameApplication() {
    std::cout << "[DEBUG] GameApplication: Destructor - Cleaning up" << std::endl;
}

void GameApplication::run() {
    std::cout << "[DEBUG] GameApplication: Starting main game loop" << std::endl;

    sf::Clock clock;

    while (window.isOpen() && applicationRunning) {
        float deltaTime = clock.restart().asSeconds();

        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                std::cout << "[DEBUG] GameApplication: Window close requested" << std::endl;
                applicationRunning = false;
                window.close();
            }

            // Let EventController handle all events
            eventController->handleEvent(event, window);
        }

        // Update game logic
        uiController->update(deltaTime);

        // Render everything
        window.clear();
        windowView->render(window);

        // Enemy renderer
        if (auto waveManager = uiController->getWaveManager()) {
            waveManager->renderEnemies(window);
        }

        window.display();
    }

    std::cout << "[DEBUG] GameApplication: Game loop ended" << std::endl;
}