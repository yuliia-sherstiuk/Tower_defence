//
// Created by chris on 12/06/2025.
//

#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H

#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <memory>

class SoundController {
public:
    static SoundController& getInstance();

    //Handle sound
    bool loadSound(const std::string& name, const std::string& filepath);
    void playSound(const std::string& name);
    void stopSound(const std::string& name);
    void stopAllSounds();

    //Handle music
    bool loadMusic(const std::string& name, const std::string& filepath);
    void playMusic(const std::string& name, bool loop = true);
    void stopMusic();
    void pauseMusic();
    void resumeMusic();

    //Volume control
    void setMasterVolume(float volume); // 0.0f to 100.0f
    void setSoundVolume(float volume);
    void setMusicVolume(float volume);

    //Getters
    float getMasterVolume() const {return masterVolume; }
    float getSoundVolume() const {return soundVolume; }
    float getMusicVolume() const {return musicVolume; }
    bool isMuted() const {return muted; }

    //Mute/Unmute
    void mute();
    void unmute();
    void toggleMute();

private:
    SoundController();
    ~SoundController() = default;
    SoundController(const SoundController&) = delete;
    SoundController& operator=(const SoundController&) = delete;

    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::map<std::string, std::unique_ptr<sf::Sound>> sounds;
    std::unique_ptr<sf::Music> currentMusic;

    float masterVolume;
    float soundVolume;
    float musicVolume;
    bool muted;

    float savedMasterVolume;

    void updateAllVolumes();

};
#endif //SOUNDCONTROLLER_H
