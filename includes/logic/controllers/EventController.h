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
//#include "../utils/Position.h"

//Check if this is the best solution or use existing Position file ?
//Simple position for compatibility with existing Ui
struct Position {
    float x, y;
    Position(float x, float y) : x(x), y(y) {}
};

class EventController {
public:

    //Callbacks
    using KeyCallback = std::function<void(sf::Keyboard::Key)>;
    using MouseClickCallback = std::function<void(sf::Vector2f,sf::Mouse::Button)>;//sf::Vector2f instead of Position
    using MouseMoveCallback = std::function<void(sf::Vector2f)>;
    using ButtonCallback = std::function<void(const std::string&)>;
    using VolumeCallback = std::function<void(float)>; // for slider volume
    using ScrollCallback = std::function<void(bool)>; // true = up, false = down

    EventController();
};


#endif //EVENTCONTROLLER_H
