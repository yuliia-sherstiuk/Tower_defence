//
// Created by chris on 12/06/2025.
//

#include "controllers/SoundController.h"
#include <iostream>
#include <algorithm>

// Returns the singleton instance of the SoundController.
SoundController &SoundController::getInstance() {
    static SoundController instance;
    return instance;
}

// Initializes the SoundController with default volume levels and sets up the music player.
SoundController::SoundController()
    : masterVolume(100.0f), soundVolume(100.0f), musicVolume(100.0f), muted(false), savedMasterVolume(100.0f) {
        currentMusic = std::make_unique<sf::Music>();
    };

// Loads a sound from a file and associates it with a specified name.
bool SoundController::loadSound(const std::string& name, const std::string& filepath) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filepath)) {
        return false;
    }

    soundBuffers[name] = std::move(buffer);
    sounds[name] = std::make_unique<sf::Sound>();
    sounds[name]->setBuffer(soundBuffers[name]);
    sounds[name]->setVolume(soundVolume*(masterVolume/100.0f));
    return true;
}

// Plays the specified music if not muted
void SoundController::playMusic(const std::string& name, bool loop) {
    if (!muted) {
        currentMusic->setLoop(loop);
        currentMusic->setVolume(musicVolume * (masterVolume / 100.0f));
        currentMusic->play();
    }
}

//Stop the music
void SoundController::stopMusic() {
    currentMusic->stop();
}

//Pause the music
void SoundController::pauseMusic() {
    currentMusic->pause();
}

//Resume music
void SoundController::resumeMusic() {
    if (!muted) {
        currentMusic->play();
    }
}

//Setting Master volume
void SoundController::setMasterVolume(float volume) {
    masterVolume = std::max(0.0f, std::min(100.0f, volume));
    updateAllVolumes();
}