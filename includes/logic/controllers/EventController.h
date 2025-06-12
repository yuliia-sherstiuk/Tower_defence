//
// Created by chris on 12/06/2025.
//

#ifndef EVENTCONTROLLER_H
#define EVENTCONTROLLER_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include "../utils/Position.h"

class EventController {
public:

    //Callbacks
    using KeyCallback = std::function<void(sf::Keyboard::Key)>;
    using MouseCallback = std::function<void(Position, sf::Mouse::Button)>;
    using MouseMoveCallback = std::function<void(Position)>;
    using ButtonCallback = std::function<void(const std::string&)>;

    EventController();
};


#endif //EVENTCONTROLLER_H
