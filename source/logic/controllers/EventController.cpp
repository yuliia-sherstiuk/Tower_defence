//
// Created by chris on 12/06/2025.
//

#include "../../../includes/logic/controllers/EventController.h"
#include <iostream>
#include <algorithm>

// Constructor for EventController class. Initializes mouse position coordinates to (0,0) and
// sets dragging volume state to false. Sets up all window view buttons upon creation.
EventController::EventController()
    : mousePosition(0,0), isDraggingVolume(false) {
    setupWindowViewButtons();
}

//Sets up and register Ui buttons for the window view : each button is assigned a unique ID and bounds
void EventController::setupWindowViewButtons() {
    //difficulty buttons - exact WindowView //update if needed: difficultyButtons
    for (int i = 0; i <3; i++) {
        std::string buttonId = "difficulty_" + std::to_string(i+1);
        sf::FloatRect bounds(890 + i*35, 350 ,30,30);
        registerUIButton(buttonId, bounds);
    }

    //Map button - exact WindowView //update if needed: mapButtons
    for (int i = 0; i <2; i++) {
        std::string buttonId = "map_" + std::to_string(i+1);
        sf::FloatRect bounds(890 + i*40, 250 ,30,30);
        registerUIButton(buttonId, bounds);
    }

    //Tower button - exact WindowView // update if needed : towerButtons
    for (int i = 0; i <3; i++) {
        std::string buttonId = "tower_" + std::to_string(i+1);
        sf::FloatRect bounds(890 + i*23, 450 ,30,30);
        registerUIButton(buttonId, bounds);
    }

    //Bottom bar buttons - exact WindowView // bottomButtons
    const std::string bottomIds[4] = {"start", "pause", "play", "quit"};
    for (int i = 0; i <4; i++) {
        sf::FloatRect bounds(20 + i*242, 650 ,100,30);
        registerUIButton("bottomIds_" + std::to_string(i+1), bounds);
    }

    //Next wave button - exact WindowView // nextWaveBtn
    sf::FloatRect nextWaveBounds(890, 500, 140, 30);
    registerUIButton("next_wave", nextWaveBounds);

    //Mute - exact WindowView // muteBox
    sf::FloatRect MuteToggleBounds(890, 600,20,20);
    registerUIButton("mute_toggle", MuteToggleBounds);



}

