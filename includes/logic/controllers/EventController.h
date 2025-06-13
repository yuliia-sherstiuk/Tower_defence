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

    //Handling SFML events
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);

    //Register callbacks
    void registerKeyCallback(KeyCallback& callback);
    void registerMouseClickCallback(MouseClickCallback& callback);
    void registerMouseMoveCallback(MouseMoveCallback& callback);
    void registerButtonCallback(ButtonCallback& callback);
    void registerVolumeCallback(VolumeCallback& callback);
    void registerScrollCallback(ScrollCallback& callback);

    //Handling Ui buttons - adapted to WindowView positions
    void registerUIButton(const std::string& buttonId, sf::FloatRect& bounds);
    void registerVolumeSlider(sf::FloatRect sliderBounds);
    void clearButtons();

    //Specific method for the existing Ui
    void setupWindowViewButtons(); //auto configure buttons

    //Entry states
    bool isKeyPressed(sf::Keyboard::Key key) const;
    bool isMouseButtonPressed(sf::Mouse::Button button) const;
    sf::Vector2f getMousePosition() const;


};


#endif //EVENTCONTROLLER_H
