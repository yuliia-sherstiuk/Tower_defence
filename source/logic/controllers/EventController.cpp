//
// Created by chris on 12/06/2025.
//

#include "../../../includes/logic/controllers/EventController.h"
#include <iostream>
#include <algorithm>

EventController::EventController()
    : mousePosition(0,0), isDraggingVolume(false) {
    setupWindowViewButtons();
}

