//
// Created by chris on 12/06/2025.
//

#include "SoundController.h"
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
    }

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

//Plays a sound by name if not muted
void SoundController::playSound(const std::string& name) {
    auto it = sounds.find(name);
    if (it == sounds.end() && !muted) {
        it->second->play();
    }
}

// Stops a specific sound by name
void SoundController::stopSound(const std::string& name) {
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        it->second->stop();
    }
}

// Stops all currently playing sounds
void SoundController::stopAllSounds() {
    for (auto& pair : sounds) {
        pair.second->stop();
    }
}

//Loads music from a file
bool SoundController::loadMusic(const std::string& name, const std::string& filepath) {
    if (!currentMusic->openFromFile(filepath)) {
        return false;
    }
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

//Set sound effects volume
void SoundController::setSoundVolume(float volume) {
    soundVolume = std::max(0.0f, std::min(100.0f, volume));
    updateAllVolumes();
}

// Set music volume
void SoundController::setMusicVolume(float volume) {
    musicVolume = std::max(0.0f, std::min(100.0f, volume));
    if (!muted) {
        currentMusic->setVolume(musicVolume * (masterVolume / 100.0f));
    }
}

//Mute
void SoundController::mute() {
    if (!muted) {
        savedMasterVolume = masterVolume;
        muted = true;
        stopAllSounds();
        pauseMusic();
    }
}

//Unmute
void SoundController::unmute() {
    if (muted) {
        muted = false;
        masterVolume = savedMasterVolume;
        updateAllVolumes();
    }
}

//Toggle mute
void SoundController::toggleMute() {
    if (muted) {
        unmute();
    } else {
        mute();
    }
}

//Update all volumes
void SoundController::updateAllVolumes() {
    float effectiveVolume = muted ? 0.0f : masterVolume / 100.0f;
    for (auto& pair : sounds) {
        pair.second->setVolume(soundVolume*effectiveVolume);
    }
    currentMusic->setVolume(musicVolume*effectiveVolume);
}