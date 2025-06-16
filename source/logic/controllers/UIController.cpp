//
// Created by chris on 14/06/2025.
//
#include "../../../includes/logic/controllers/UIController.h"
#include "../../../includes/logic/controllers/GameController.h"
#include "../../../includes/logic/controllers/EventController.h"
#include "../includes/graphics/views/WindowView.h"
#include "../../includes/utils/LevelLoader.h"
#include <iostream>
#include <algorithm>

UIController::UIController()
    : currentState(GameState::MENU)
    , previousState(GameState::MENU)
    , windowView(nullptr)
    , eventController(nullptr)
    , gameController(std::make_shared<GameController>())
    , waveManager(std::make_shared<WaveManager>())
    , economy(std::make_unique<Economy>())
    , scrollOffset(0)
    , usernameInput("")
    , registerCallback(nullptr)
    , usernames()
    , highScores()
    , currentMessage("")
    , messageTimer(0.0f)
    , messageQueue()

    // Initialize callback functions to nullptr
    , gameStartCallback(nullptr)
    , gamePauseCallback(nullptr)
    , gamePlayCallback(nullptr)
    , gameQuitCallback(nullptr)
    , nextWaveCallback(nullptr)
    , towerSelectionCallback(nullptr)
    , mapSelectionCallback(nullptr)
    , difficultySelectionCallback(nullptr)
    , applicationQuitCallback(nullptr)
{
    std::cout << "[DEBUG] UIController: Constructor called" << std::endl;

    // Init default values
    gameData.score = 0;
    gameData.money = 100;
    gameData.lives = 100;
    gameData.currentWave = 1;
    gameData.waveCountdown = 30.0f;
    gameData.selectedLevel = 1;
    gameData.selectedDifficulty = 1;
    gameData.selectedTower = -1;
    gameData.volume = 1.0f;
    gameData.isMuted = false;
    gameData.isPaused = false;
    gameData.isGameOver = false;

    // Init Economy
    economy->goldAmount = gameData.money;
    economy->profitMultiplier = 1;

    // Connect GameController callbacks
    setupGameControllerCallbacks();

    // Sync init sound and volume
    SoundController::getInstance().initializeGameAudio();
    SoundController::getInstance().setMasterVolume(gameData.volume * 100.0f);
    std::cout << "[DEBUG] UIController: Initialization complete with default game data" << std::endl;
}

// Setup callbacks to communicate with GameController
void UIController::setupGameControllerCallbacks() {
    std::cout << "[DEBUG] UIController::setupGameControllerCallbacks: Setting up GameController communication" << std::endl;

    // Set up callbacks for GameController
    gameStartCallback = [this]() {
        std::cout << "[DEBUG] UIController: GameController start callback triggered" << std::endl;
        gameController->startGame();
        setState(GameState::PLAYING);
    };

    gamePauseCallback = [this]() {
        std::cout << "[DEBUG] UIController: GameController pause callback triggered" << std::endl;
        gameController->pauseGame();
        setState(GameState::PAUSED);
    };

    gamePlayCallback = [this]() {
        std::cout << "[DEBUG] UIController: GameController play callback triggered" << std::endl;
        gameController->playGame();
        setState(GameState::PLAYING);
    };

    gameQuitCallback = [this]() {
        std::cout << "[DEBUG] UIController: GameController quit callback triggered" << std::endl;
        gameController->quitGame();
        setState(GameState::MENU);
    };

    nextWaveCallback = [this]() {
        std::cout << "[DEBUG] UIController: Next wave callback triggered" << std::endl;
        waveManager->forceStartWave();
    };

    towerSelectionCallback = [this](int towerType) {
        std::cout << "[DEBUG] UIController: Tower selection callback - type " << towerType << std::endl;
        gameData.selectedTower = towerType;
    };

    mapSelectionCallback = [this](int levelNumber) {
        std::cout << "[DEBUG] UIController: Map selection callback - level " << levelNumber << std::endl;
        selectLevel(levelNumber);
    };

    difficultySelectionCallback = [this](int difficulty) {
        std::cout << "[DEBUG] UIController: Difficulty selection callback - difficulty " << difficulty << std::endl;
        setDifficulty(difficulty);
    };
}

// To connect with View
void UIController::connectWithWindowView(WindowView* wv) {
    std::cout << "[DEBUG] UIController::connectWithWindowView: Connecting with WindowView" << std::endl;
    windowView = wv;

    // Set up callbacks for the WindowView interface
    if (windowView) {
        windowView->setClickCallback([this](const std::string& buttonId, sf::Vector2f pos) {
            handleButtonClick(buttonId);
        });

        windowView->setVolumeCallback([this](float volume) {
            handleVolumeChange(volume);
        });

        windowView->setTextInputCallback([this](sf::Uint32 unicode) {
            handleTextInput(unicode);
        });

        windowView->setScrollCallback([this](bool up) {
            handleScroll(up);
        });

        //Use the shared WindowView instance
        gameController->setWindowView(windowView);

        std::cout << "[DEBUG] UIController::connectWithWindowView: All callbacks set" << std::endl;
    }
}

// To connect with event controller
void UIController::connectWithEventController(const std::shared_ptr<EventController>& eventCtrl) {
    std::cout << "[DEBUG] UIController::connectWithEventController: Connecting with EventController" << std::endl;
    eventController = eventCtrl;

    // Share the EventController with GameController
    gameController->setEventController(eventController);

    setupEventCallbacks();
}

// To set up event callbacks
void UIController::setupEventCallbacks() {
    std::cout << "[DEBUG] UIController::setupEventCallbacks: Setting up event callbacks" << std::endl;
    if (!eventController) return;

    eventController->registerKeyCallback([this](sf::Keyboard::Key key) {
        handleKeyPress(key);
    });

    eventController->registerMouseClickCallback([this](sf::Vector2f pos, sf::Mouse::Button button) {
        handleMouseClick(pos, button);
    });

    eventController->registerButtonCallback([this](const std::string& buttonId) {
        handleButtonClick(buttonId);
    });

    eventController->registerVolumeCallback([this](float volume) {
        handleVolumeChange(volume);
    });

    eventController->registerScrollCallback([this](bool up) {
        handleScroll(up);
    });
    std::cout << "[DEBUG] UIController::setupEventCallbacks: All event callbacks registered" << std::endl;
}

// Update deltatime - MAIN COORDINATION POINT
void UIController::update(float deltaTime) {
    // Update GameController first
    if (gameController) {
        gameController->update(deltaTime);

        // Sync game state from GameController
        syncFromGameController();
    }

    if (currentState == GameState::PLAYING) {
        updateGameLogic(deltaTime);
    }

    updateMessageSystem(deltaTime);

    if (windowView) {
        syncUIWithGameData();
    }
}

//Sync data from GameController
void UIController::syncFromGameController() {
    if (!gameController) return;

    // Get current scores and update gameData
    auto scores = gameController->getHighScores();
    // Update high scores here

    // Check if game is still running
    if (!gameController->isGameRunning() && currentState == GameState::PLAYING) {
        std::cout << "[DEBUG] UIController::syncFromGameController: Game stopped, transitioning to GAME_OVER" << std::endl;
        setState(GameState::GAME_OVER);
    }

    // Sync other relevant data here
    gameData.score = gameController->getCurrentScore(); // if this method exists
}

// Update game logic
void UIController::updateGameLogic(float deltaTime) {
    if (gameData.isPaused) return;

    // Update WaveManager
    waveManager->update(deltaTime);

    // Update game data from various sources
    gameData.lives = Tower::getInstance().getBaseHealth();
    gameData.money = economy->getGoldAmount();
    gameData.currentWave = waveManager->getCurrentWaveNumber();
    gameData.waveCountdown = waveManager->getWaveTimer();

    // Check if game is over
    if (gameData.lives <= 0 && currentState != GameState::GAME_OVER) {
        std::cout << "[DEBUG] UIController::updateGameLogic: Game over - lives = " << gameData.lives << std::endl;
        setState(GameState::GAME_OVER);
        SoundController::getInstance().GameOverSound();
    }
}

// Handle button clicks with GameController integration
void UIController::handleButtonClick(const std::string& buttonId) {
    std::cout << "[DEBUG] UIController::handleButtonClick: Button clicked = " << buttonId << std::endl;

    if (buttonId == "bottomIds_4" || buttonId == "quit") {
        std::cout << "[DEBUG] UIController::handleButtonClick: Quit button pressed, initiating application shutdown" << std::endl;
        quitGame();
        return;
    }

    if (buttonId == "bottomIds_1" ||  buttonId== "start") {
        startGame();
        setMessage("Game started!");
    } else if (buttonId == "bottomIds_2" || buttonId == "pause") {
        pauseGame();
        setMessage("Game paused.");
    } else if (buttonId == "bottomIds_3" || buttonId == "play") {
        resumeGame();
        setMessage("Game resumed.");
    } else if (buttonId == "quit") {
        quitGame();
        setMessage("Game quit.");
    } else if (buttonId == "next_wave") {
        forceNextWave();
        setMessage("Next wave started!");
    } else if (buttonId.substr(0, 11) == "difficulty_") {
        int difficulty = std::stoi(buttonId.substr(11));
        std::cout << "[DEBUG] UIController::handleButtonClick: Setting difficulty to " << difficulty << std::endl;
        setDifficulty(difficulty);
        setMessage("Difficulty set to " + std::to_string(difficulty) + ".");
    } else if (buttonId.substr(0, 4) == "map_") {
        int level = std::stoi(buttonId.substr(4));
        std::cout << "[DEBUG] UIController::handleButtonClick: Selecting level " << level << std::endl;
        selectLevel(level);
        setMessage("Map " + std::to_string(level) + " selected.");
    } else if (buttonId.substr(0, 6) == "tower_") {
        int towerType = std::stoi(buttonId.substr(6));
        std::cout << "[DEBUG] UIController::handleButtonClick: Selecting tower type " << towerType << std::endl;
        gameData.selectedTower = towerType;
        setMessage("Tower " + std::to_string(towerType) + " selected.");
    } else if (buttonId == "mute_toggle") {
        toggleMute();
        setMessage(gameData.isMuted ? "Sound muted." : "Sound unmuted.");
    }

    // Play button click sound
    SoundController::getInstance().playButtonClickSound();
}

// Handle key press
void UIController::handleKeyPress(sf::Keyboard::Key key) {
    std::cout << "[DEBUG] UIController::handleKeyPress: Key pressed = " << key << std::endl;
    switch (key) {
        case sf::Keyboard::Space:
            if (currentState == GameState::PLAYING) {
                std::cout << "[DEBUG] UIController::handleKeyPress: Space key - forcing next wave" << std::endl;
                waveManager->forceStartWave();
                SoundController::getInstance().playWaveStartSound();
            }
            break;

        case sf::Keyboard::P:
        case sf::Keyboard::Escape:
            if (currentState == GameState::PLAYING) {
                std::cout << "[DEBUG] UIController::handleKeyPress: P/Escape key - pausing game" << std::endl;
                pauseGame();
                SoundController::getInstance().playButtonClickSound();
            } else if (currentState == GameState::PAUSED) {
                std::cout << "[DEBUG] UIController::handleKeyPress: P/Escape key - resuming game" << std::endl;
                resumeGame();
                SoundController::getInstance().playButtonClickSound();
            }
            break;

        case sf::Keyboard::Num1:
        case sf::Keyboard::Num2:
        case sf::Keyboard::Num3:
            std::cout << "[DEBUG] UIController::handleKeyPress: Number key - setting difficulty to " << (key - sf::Keyboard::Num1 + 1) << std::endl;
            setDifficulty(key - sf::Keyboard::Num1 + 1);
            SoundController::getInstance().playButtonClickSound();
            break;

        default:
            break;
    }
}

// Handle Mouse click
void UIController::handleMouseClick(sf::Vector2f pos, sf::Mouse::Button button) {
    std::cout << "[DEBUG] UIController::handleMouseClick: Mouse clicked at (" << pos.x << ", " << pos.y << ") with button " << button << std::endl;
    if (button == sf::Mouse::Left && currentState == GameState::PLAYING) {
        sf::FloatRect gameArea(10, 100, 850, 540);
        if (gameArea.contains(pos)) {
            std::cout << "[DEBUG] UIController::handleMouseClick: Click in game area with selected tower " << gameData.selectedTower << std::endl;
            Tower* selectedTower = nullptr;
            switch(gameData.selectedTower) {
                case 1: selectedTower = Tower::getInstance().createTower("Puncher"); break;
                case 2: selectedTower = Tower::getInstance().createTower("Freezer"); break;
                case 3: selectedTower = Tower::getInstance().createTower("Bomber"); break;
                default: break;
            }

            if (selectedTower && economy->buyTower(selectedTower)) {
                gameData.money = economy->getGoldAmount();
                setMessage("Tower placed!");
                std::cout << "[DEBUG] UIController::handleMouseClick: Tower placed successfully, money = " << gameData.money << std::endl;
                SoundController::getInstance().playTowerPlaceSound();
                if (windowView) {
                    windowView->updateMoney(gameData.money);
                    SoundController::getInstance().playMoneySound();
                }
            } else {
                std::cout << "[DEBUG] UIController::handleMouseClick: Tower placement failed" << std::endl;
                setMessage("Tower placement failed!");
            }
        }
    }
}

// Handle volume change
void UIController::handleVolumeChange(float volume) {
    std::cout << "[DEBUG] UIController::handleVolumeChange: Volume changed to " << volume << std::endl;
    setVolume(volume);
}

// Handle scroll
void UIController::handleScroll(bool up) {
    std::cout << "[DEBUG] UIController::handleScroll: Scroll " << (up ? "up" : "down") << std::endl;
    if (up) {
        scrollScoresUp();
    } else {
        scrollScoresDown();
    }
}

// Start game
void UIController::startGame() {
    std::cout << "[DEBUG] UIController::startGame: Attempting to start game" << std::endl;
    if (canStartGame()) {
        if (gameStartCallback) gameStartCallback();
        waveManager->setDifficulty(difficultyToString(gameData.selectedDifficulty));
        std::cout << "[DEBUG] UIController::startGame: Game started with difficulty " << difficultyToString(gameData.selectedDifficulty) << std::endl;
    } else {
        std::cout << "[DEBUG] UIController::startGame: Cannot start game in current state" << std::endl;
    }
}

// Pause game
void UIController::pauseGame() {
    std::cout << "[DEBUG] UIController::pauseGame: Attempting to pause game" << std::endl;
    if (currentState == GameState::PLAYING) {
        if (gamePauseCallback) gamePauseCallback();
    }
}

// Resume game
void UIController::resumeGame() {
    std::cout << "[DEBUG] UIController::resumeGame: Attempting to resume game" << std::endl;
    if (currentState == GameState::PAUSED) {
        if (gamePlayCallback) gamePlayCallback();
    }
}

// Quit game
void UIController::quitGame() {
    std::cout << "[DEBUG] UIController::quitGame: Quitting game and application" << std::endl;
    if (gameQuitCallback) {
        gameQuitCallback();
    }

    //Call callback to close the app
    if (applicationQuitCallback) {
        std::cout << "[DEBUG] UIController::quitGame: Calling application quit callback" << std::endl;
        applicationQuitCallback();
    }
}

// Restart game
void UIController::restartGame() {
    std::cout << "[DEBUG] UIController::restartGame: Restarting game" << std::endl;
    setState(GameState::MENU);
    startGame();
}

// Set state
void UIController::setState(GameState state) {
    if (currentState != state) {
        GameState oldState = currentState;
        previousState = currentState;
        currentState = state;
        std::cout << "[DEBUG] UIController::setState: State changed from " << static_cast<int>(oldState) << " to " << static_cast<int>(state) << std::endl;
        onStateChange(oldState, state);
    }
}

// Change state
void UIController::onStateChange(GameState oldState, GameState newState) {
    std::cout << "[DEBUG] UIController::onStateChange: Processing state change" << std::endl;
    switch (newState) {
        case GameState::PLAYING:
            std::cout << "[DEBUG] UIController::onStateChange: Entering PLAYING state" << std::endl;
            gameData.isPaused = false;
            break;

        case GameState::PAUSED:
            std::cout << "[DEBUG] UIController::onStateChange: Entering PAUSED state" << std::endl;
            gameData.isPaused = true;
            break;

        case GameState::MENU:
            std::cout << "[DEBUG] UIController::onStateChange: Entering MENU state" << std::endl;
            resetGameData();
            break;

        case GameState::GAME_OVER:
            std::cout << "[DEBUG] UIController::onStateChange: Entering GAME_OVER state" << std::endl;
            handleGameOver();
            break;
    }
}

// Reset game data
void UIController::resetGameData() {
    std::cout << "[DEBUG] UIController::resetGameData: Resetting game data" << std::endl;
    gameData.score = 0;
    gameData.money = 100;
    gameData.lives = 100;
    gameData.currentWave = 1;
    gameData.waveCountdown = 30.0f;
    economy->goldAmount = gameData.money;
}

// Handle game over
void UIController::handleGameOver() {
    std::cout << "[DEBUG] UIController::handleGameOver: Handling game over with score " << gameData.score << std::endl;
    if (gameData.score > 0) {
        ScoreEntry entry;
        entry.username = "Player"; // need to be changed when user class will be done
        entry.score = gameData.score;
        highScores.push_back(entry);

        std::sort(highScores.begin(), highScores.end(),
            [](const ScoreEntry& a, const ScoreEntry& b) {
                return a.score > b.score;
            });
        std::cout << "[DEBUG] UIController::handleGameOver: Score entry added and high scores sorted" << std::endl;
    }
}

// Set difficulty
void UIController::setDifficulty(int difficulty) {
    std::cout << "[DEBUG] UIController::setDifficulty: Setting difficulty to " << difficulty << std::endl;
    if (difficulty >= 1 && difficulty <= 3) {
        gameData.selectedDifficulty = difficulty;
        waveManager->setDifficulty(difficultyToString(difficulty));
    } else {
        std::cout << "[DEBUG] UIController::setDifficulty: Invalid difficulty value " << difficulty << std::endl;
    }
}

// Select level
void UIController::selectLevel(int levelNumber) {
    std::cout << "[DEBUG] UIController::selectLevel: Selecting level " << levelNumber << std::endl;
    gameData.selectedLevel = levelNumber;

    auto level = LevelLoader::loadLevel(levelNumber);
    if (level && windowView) {
        windowView->setLevel(level);
    }

    SoundController::getInstance().playButtonClickSound();
    if (windowView) {
        windowView->setMessage("Level " + std::to_string(levelNumber) + " selected!");
    }
}

// Set volume
void UIController::setVolume(float volume) {
    std::cout << "[DEBUG] UIController::setVolume: Setting volume to " << volume << std::endl;
    gameData.volume = std::max(0.f, std::min(1.f, volume));
    gameData.isMuted = (gameData.volume == 0.f);

    // Sync with SoundController
    SoundController::getInstance().setMasterVolume(gameData.volume * 100.0f);

    if (windowView) {
        windowView->updateVolumeDisplay(gameData.volume, gameData.isMuted);
    }
}

// Toggle mute
void UIController::toggleMute() {
    std::cout << "[DEBUG] UIController::toggleMute: Toggling mute from " << gameData.isMuted << " to " << !gameData.isMuted << std::endl;
    gameData.isMuted = !gameData.isMuted;

    if (gameData.isMuted) {
        SoundController::getInstance().mute();
        gameData.volume = 0.f;
    } else {
        gameData.volume = 1.f;
        SoundController::getInstance().unmute();
        SoundController::getInstance().playButtonClickSound();
    }

    if (windowView) {
        windowView->updateVolumeDisplay(gameData.volume, gameData.isMuted);
    }
}

// Update ui message
void UIController::updateMessageSystem(float deltaTime) {
    if (messageTimer > 0.0f) {
        messageTimer -= deltaTime;
        if (messageTimer <= 0.0f) {
            currentMessage = "";
        }
    }

    if (!messageQueue.empty() && messageTimer <= 0.0f) {
        auto message = messageQueue.front();
        messageQueue.pop();
        currentMessage = message.first;
        messageTimer = message.second;
        std::cout << "[DEBUG] UIController::updateMessageSystem: Displaying message: " << currentMessage << std::endl;
    }
}

// Sync Ui with game data
void UIController::syncUIWithGameData() {
    windowView->updateScore(gameData.score);
    windowView->updateMoney(gameData.money);
    windowView->updateLives(gameData.lives);
    windowView->updateWaveCountdown(static_cast<int>(gameData.waveCountdown));

    if (hasActiveMessage()) {
        windowView->setMessage(currentMessage);
    }
}

// Can start game
bool UIController::canStartGame() const {
    bool canStart = currentState == GameState::MENU;
    std::cout << "[DEBUG] UIController::canStartGame: Can start = " << canStart << " (current state = " << static_cast<int>(currentState) << ")" << std::endl;
    return canStart;
}

// Difficulty to string
std::string UIController::difficultyToString(int difficulty) const {
    std::string result;
    switch (difficulty) {
        case 1: result = "private"; break;
        case 2: result = "corporal"; break;
        case 3: result = "sergeant"; break;
        default: result = "private"; break;
    }
    std::cout << "[DEBUG] UIController::difficultyToString: Difficulty " << difficulty << " converted to " << result << std::endl;
    return result;
}

// String to difficulty
int UIController::stringToDifficulty(const std::string& difficulty) const {
    int result;
    if (difficulty == "private") result = 1;
    else if (difficulty == "corporal") result = 2;
    else if (difficulty == "sergeant") result = 3;
    else result = 1;
    std::cout << "[DEBUG] UIController::stringToDifficulty: Difficulty " << difficulty << " converted to " << result << std::endl;
    return result;
}

// Show message on ui
void UIController::showMessage(const std::string& message, float duration) {
    std::cout << "[DEBUG] UIController::showMessage: Queuing message: " << message << " for " << duration << " seconds" << std::endl;
    messageQueue.push({message, duration});
}

// Get current message
std::string UIController::getCurrentMessage() const {
    return currentMessage;
}

// Active message
bool UIController::hasActiveMessage() const {
    return messageTimer > 0.0f;
}

// Add username
void UIController::addUsername(const std::string& username) {
    std::cout << "[DEBUG] UIController::addUsername: Adding username: " << username << std::endl;
    usernames.push_back(username);
    if (windowView) {
        windowView->addScoreEntry(username + ": " + std::to_string(gameData.score));
    }
}

// Get high score
std::vector<ScoreEntry> UIController::getHighScores() const {
    std::cout << "[DEBUG] UIController::getHighScores: Returning " << highScores.size() << " high scores" << std::endl;
    return highScores;
}

// Scroll up
void UIController::scrollScoresUp() {
    std::cout << "[DEBUG] UIController::scrollScoresUp: Scrolling up from offset " << scrollOffset << std::endl;
    if (scrollOffset > 0) {
        scrollOffset--;
        if (windowView) {
            windowView->updateScrollDisplay(scrollOffset);
        }
    }
}

// Scroll down
void UIController::scrollScoresDown() {
    std::cout << "[DEBUG] UIController::scrollScoresDown: Scrolling down from offset " << scrollOffset << std::endl;
    scrollOffset++;
    if (windowView) {
        windowView->updateScrollDisplay(scrollOffset);
    }
}

// Force next wave
void UIController::forceNextWave() {
    std::cout << "[DEBUG] UIController::forceNextWave: Forcing next wave" << std::endl;
    waveManager->forceStartWave();
}

// Notify click
void UIController::notifyClick(sf::Vector2f pos, const std::string& buttonId) {
    std::cout << "[DEBUG] UIController::notifyClick: Click notification at (" << pos.x << ", " << pos.y << ") for button " << buttonId << std::endl;
    SoundController::getInstance().playButtonClickSound();
    handleButtonClick(buttonId);
}

// Notify username input
void UIController::notifyUsernameInput(const std::string& input) {
    std::cout << "[DEBUG] UIController::notifyUsernameInput: Username input: " << input << std::endl;
    updateUsernameInput(input);
}

// Update score
void UIController::updateScore(int score) {
    std::cout << "[DEBUG] UIController::updateScore: Score updated to " << score << std::endl;
    gameData.score = score;
    syncUIWithGameData();
}

// Update money
void UIController::updateMoney(int money) {
    std::cout << "[DEBUG] UIController::updateMoney: Money updated to " << money << std::endl;
    gameData.money = money;
    syncUIWithGameData();
}

// Update lives
void UIController::updateLives(int lives) {
    std::cout << "[DEBUG] UIController::updateLives: Lives updated to " << lives << std::endl;
    gameData.lives = lives;
    syncUIWithGameData();
}

// Update Wave Countdown
void UIController::updateWaveCountdown(int countdown) {
    gameData.waveCountdown = static_cast<float>(countdown);
    syncUIWithGameData();
}

// Set message show message
void UIController::setMessage(const std::string& message) {
    showMessage(message);
}

// Update username input
void UIController::updateUsernameInput(const std::string& text) {
    std::cout << "[DEBUG] UIController::updateUsernameInput: Username input updated to: " << text << std::endl;
    usernameInput = text;
    if (windowView) {
        windowView->updateUsernameDisplay(text);
    }
}

// Get username input
std::string UIController::getUsernameInput() const {
    return usernameInput;
}

// Handle text input
void UIController::handleTextInput(sf::Uint32 unicode) {
    std::cout << "[DEBUG] UIController::handleTextInput: Text input with unicode " << unicode << std::endl;
    // Handle backspace
    if (unicode == 8 && !usernameInput.empty()) {
        usernameInput.pop_back();
        std::cout << "[DEBUG] UIController::handleTextInput: Backspace - username now: " << usernameInput << std::endl;
    }
    // Handle regular characters (printable ASCII)
    else if (unicode >= 32 && unicode < 127) {
        usernameInput += static_cast<char>(unicode);
        std::cout << "[DEBUG] UIController::handleTextInput: Character added - username now: " << usernameInput << std::endl;
    }

    if (windowView) {
        windowView->updateUsernameDisplay(usernameInput);
    }
}

// Update volume slider position
void UIController::updateVolumeSliderPosition() {
    std::cout << "[DEBUG] UIController::updateVolumeSliderPosition: Updating volume slider position" << std::endl;
    if (windowView) {
        windowView->updateVolumeDisplay(gameData.volume, gameData.isMuted);
    }
}

// Handle scroll event
void UIController::handleScrollEvent(const sf::Event& event) {
    std::cout << "[DEBUG] UIController::handleScrollEvent: Handling scroll event" << std::endl;
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0) {
            scrollScoresUp();
        } else {
            scrollScoresDown();
        }
    }
}

// Handle click
void UIController::handleClick(sf::Vector2f mousePos) {
    std::cout << "[DEBUG] UIController::handleClick: Handling click at (" << mousePos.x << ", " << mousePos.y << ")" << std::endl;
    if (windowView) {
        windowView->handleClick(mousePos);
    }
}

// Set register callback
void UIController::setRegisterCallback(const std::function<void(const std::string&)>& callback) {
    std::cout << "[DEBUG] UIController::setRegisterCallback: Register callback set" << std::endl;
    registerCallback = callback;
}

//Set application Quit callback
void UIController::setApplicationQuitCallback(const std::function<void()>& callback) {
    std::cout << "[DEBUG] UIController::setApplicationQuitCallback: Application quit callback set" << std::endl;
    applicationQuitCallback = callback;
}