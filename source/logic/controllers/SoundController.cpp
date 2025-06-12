//
// Created by chris on 12/06/2025.
//

#include "controllers/SoundController.h"
#include <iostream>
#include <algorithm>

SoundController &SoundController::getInstance() {
    static SoundController instance;
    return instance;
}

SoundController::SoundController()
    : masterVolume(100.0f), soundVolume(100.0f), musicVolume(100.0f), muted(false), savedMasterVolume(100.0f) {
        currentMusic = std::make_unique<sf::Music>();
    };

