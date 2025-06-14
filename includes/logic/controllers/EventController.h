//
// Created by chris on 12/06/2025.
//
#ifndef EVENT_CONTROLLER_H
#define EVENT_CONTROLLER_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <unordered_map>
#include <vector>
#include <string>

// Forward declarations and type definitions
struct ButtonInfo {
    sf::FloatRect bounds;
    bool enabled = true;

    ButtonInfo() = default;
    ButtonInfo(const sf::FloatRect& rect) : bounds(rect) {}
};

class EventController {
public:
    // Callback type definitions
    using KeyCallback = std::function<void(sf::Keyboard::Key)>;
    using MouseClickCallback = std::function<void(sf::Vector2f, sf::Mouse::Button)>;
    using MouseMoveCallback = std::function<void(sf::Vector2f)>;
    using ButtonCallback = std::function<void(const std::string&)>;
    using VolumeCallback = std::function<void(float)>;
    using ScrollCallback = std::function<void(bool)>;
    using TextInputCallback = std::function<void(sf::Uint32)>;

private:
    // Member variables
    sf::Vector2f mousePosition;
    bool isDraggingVolume;
    sf::FloatRect volumeSliderBounds;
    std::unordered_map<std::string, ButtonInfo> buttons;

    // Callback members
    KeyCallback keyCallback;
    MouseClickCallback mouseClickCallback;
    MouseMoveCallback mouseMoveCallback;
    ButtonCallback buttonCallback;
    VolumeCallback volumeCallback;
    ScrollCallback scrollCallback;
    TextInputCallback textInputCallback;

public:
    // Constructor
    EventController();

    // Event handling
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);

    // Callback registration methods
    void registerKeyCallback(const KeyCallback& callback);
    void registerMouseClickCallback(const MouseClickCallback& callback);
    void registerMouseMoveCallback(const MouseMoveCallback& callback);
    void registerButtonCallback(const ButtonCallback& callback);
    void registerVolumeCallback(const VolumeCallback& callback);
    void registerScrollCallback(const ScrollCallback& callback);
    void registerTextInputCallback(const TextInputCallback& callback);

    // UI management methods
    void registerUIButton(const std::string& buttonId, const sf::FloatRect& bounds);
    void registerVolumeSlider(const sf::FloatRect& sliderBounds);
    void clearButtons();
    void setupWindowViewButtons();

    // Query methods
    std::string getButtonAtPosition(const sf::Vector2f& pos) const;
    std::vector<std::string> getButtonsAtPosition(const sf::Vector2f& pos) const;
    bool hasButton(const std::string& buttonId) const;
    static bool isPointInButton(const sf::Vector2f& point, const ButtonInfo& button);

    // Input state methods
    static bool isKeyPressed(sf::Keyboard::Key key);
    static bool isMouseButtonPressed(sf::Mouse::Button button);
    sf::Vector2f getMousePosition() const;

    // Volume calculation
    float calculateVolumeFromPosition(const sf::Vector2f& pos) const;
};

#endif // EVENT_CONTROLLER_H