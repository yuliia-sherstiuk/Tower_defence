#ifndef SETTINGS_CONTROLLER_
#define SETTINGS_CONTROLLER_
#include <iostream>

class SettingsController {
    public:

    void changeVolume(int volume);

    void setDifficulty(std::string difficulty);

    void resetSettings();
};



#endif
