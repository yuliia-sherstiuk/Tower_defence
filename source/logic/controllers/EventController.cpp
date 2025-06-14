//
// Created by chris on 12/06/2025.
//

#include "../../../includes/logic/controllers/EventController.h"

// Constructor for EventController class. Initializes mouse position coordinates to (0,0) and
// sets dragging volume state to false. Sets up all window view buttons upon creation.
EventController::EventController()
    : mousePosition(0,0), isDraggingVolume(false) {
    setupWindowViewButtons();
}

//Sets up and register Ui buttons for the window view : each button is assigned a unique ID and bounds
void EventController::setupWindowViewButtons() {
    //difficulty buttons - exact WindowView //update if needed: difficultyButtons
    for (int i = 0; i < 3; i++) {
        std::string buttonId = "difficulty_" + std::to_string(i+1);
        sf::FloatRect bounds(890 + i*35, 350, 30, 30);
        registerUIButton(buttonId, bounds);
    }

    //Map button - exact WindowView //update if needed: mapButtons
    for (int i = 0; i < 2; i++) {
        std::string buttonId = "map_" + std::to_string(i+1);
        sf::FloatRect bounds(890 + i*40, 250, 30, 30);
        registerUIButton(buttonId, bounds);
    }

    //Tower button - exact WindowView // update if needed : towerButtons
    for (int i = 0; i < 3; i++) {
        std::string buttonId = "tower_" + std::to_string(i+1);
        sf::FloatRect bounds(890 + i*23, 450, 30, 30);
        registerUIButton(buttonId, bounds);
    }

    //Bottom bar buttons - exact WindowView // bottomButtons
    const std::string bottomIds[4] = {"start", "pause", "play", "quit"};
    for (int i = 0; i < 4; i++) {
        sf::FloatRect bounds(20 + i*242, 650, 100, 30);
        registerUIButton("bottomIds_" + std::to_string(i+1), bounds);
    }

    //Next wave button - exact WindowView // nextWaveBtn
    sf::FloatRect nextWaveBounds(890, 500, 140, 30);
    registerUIButton("next_wave", nextWaveBounds);

    //Mute - exact WindowView // muteBox
    sf::FloatRect MuteToggleBounds(890, 600, 20, 20);
    registerUIButton("mute_toggle", MuteToggleBounds);

    //Volume slider - exact WindowView // VolumeSlider
    registerVolumeSlider(sf::FloatRect(890, 580, 100, 5));
}

// Handles mouse button events, specifically for volume slider adjustments
void EventController::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    switch (event.type) {
        case sf::Event::MouseButtonPressed: {
            mousePosition = sf::Vector2f(
                static_cast<float>(event.mouseButton.x),
                static_cast<float>(event.mouseButton.y)
                );
            //Verify the slider volume
            if (volumeSliderBounds.contains(mousePosition) && event.mouseButton.button == sf::Mouse::Left) {
                isDraggingVolume = true;
                float volume = calculateVolumeFromPosition(mousePosition);
                if (volumeCallback) {
                    volumeCallback(volume);
                }
                return;
            }
            // Retrieves the button ID at the given mouse position and triggers the associated callback if valid.
            std::string buttonId = getButtonAtPosition(mousePosition);
            if (!buttonId.empty() && buttonCallback) {
                buttonCallback(buttonId);
                return;
            }

            // Calls the mouse click callback with the position and button type if the callback is set.
            if (mouseClickCallback) {
                mouseClickCallback(mousePosition, event.mouseButton.button);
            }
            break;
        }
            //Resets dragging state on mouse button release
        case sf::Event::MouseButtonReleased: {
            if (event.mouseButton.button == sf::Mouse::Left) {
                isDraggingVolume = false;
            }
            break;
        }
        // Updates mouse position and handles volume adjustment and mouse movement callback.
        case sf::Event::MouseMoved: {
            mousePosition = sf::Vector2f(
                static_cast<float>(event.mouseMove.x),
                static_cast<float>(event.mouseMove.y)
            );
            if (isDraggingVolume && volumeSliderBounds.contains(mousePosition)) {
                float volume = calculateVolumeFromPosition(mousePosition);
                if (volumeCallback) {
                    volumeCallback(volume);
                }
            }
            if (mouseMoveCallback) {
                mouseMoveCallback(mousePosition);
            }
            break;
        }
        case sf::Event::MouseWheelScrolled: {
            // Handling scroll for scores
            if (scrollCallback) {
                scrollCallback(event.mouseWheelScroll.delta > 0);
            }
            break;
        }
        default:
            break;
    }
}

// Registers a callback for key events.
void EventController::registerKeyCallback(const KeyCallback& callback) {
    keyCallback = callback;
}
// Registers a callback for mouse click events
void EventController::registerMouseClickCallback(const MouseClickCallback& callback) {
    mouseClickCallback = callback;
}
// Registers a callback for button events.
void EventController::registerButtonCallback(const ButtonCallback& callback) {
    buttonCallback = callback;
}
