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
