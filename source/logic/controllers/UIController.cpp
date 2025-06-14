//
// Created by chris on 14/06/2025.
//
//
// Created by chris on 14/06/2025.
//
#include "../../../includes/logic/controllers/UIController.h"
#include "../../../includes/logic/controllers/EventController.h"
#include "../includes/graphics/views/WindowView.h"
#include <iostream>
#include <algorithm>

UIController::UIController()
    : currentState(GameState::MENU)
    , previousState(GameState::MENU)
    , windowView(nullptr)
    , eventController(nullptr)
    , gameController(std::make_shared<GameController>())
    , waveManager(std::make_shared<WaveManager>())
    , economy(std::unique_ptr<Economy>(new Economy()))
    , scrollOffset(0)
    , usernameInput("")
    , registerCallback(nullptr)
    , usernames()
    , highScores()
    , currentMessage("")
    , messageTimer(0.0f)
    , messageQueue()
{
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

    // Sync init sound and volume
    SoundController::getInstance().initializeGameAudio();
    SoundController::getInstance().setMasterVolume(gameData.volume * 100.0f);
}

//To notify volume change
void UIController::notifyVolumeChange(float newVolume) {
    if (windowView) {
        windowView->updateVolumeDisplay(newVolume, gameData.isMuted);
    }
}

//To notify toggle mute
void UIController::notifyMuteToggle() {
    if (windowView) {
        windowView->updateVolumeDisplay(gameData.volume, gameData.isMuted);
    }
}

//To notify scroll
void UIController::notifyScroll(bool up) {
    if (up) {
        scrollScoresUp();
    } else {
        scrollScoresDown();
    }
}

//To connect with View
void UIController::connectWithWindowView(WindowView* wv) {
    windowView = wv;

    // Set up callbacks for the new WindowView interface
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
    }
}

//To connect with event controller
void UIController::connectWithEventController(const std::shared_ptr<EventController>& eventCtrl) {
    eventController = eventCtrl;
    setupEventCallbacks();
}

//To set up event callbacks
void UIController::setupEventCallbacks() {
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
}

//To handle key press
void UIController::handleKeyPress(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Space:
            if (currentState == GameState::PLAYING) {
                waveManager->forceStartWave();
                SoundController::getInstance().playWaveStartSound();
            }
            break;

        case sf::Keyboard::P:
        case sf::Keyboard::Escape:
            if (currentState == GameState::PLAYING) {
                pauseGame();
                SoundController::getInstance().playButtonClickSound();
            } else if (currentState == GameState::PAUSED) {
                resumeGame();
                SoundController::getInstance().playButtonClickSound();
            }
            break;

        case sf::Keyboard::Num1:
        case sf::Keyboard::Num2:
        case sf::Keyboard::Num3:
            setDifficulty(key - sf::Keyboard::Num1 + 1);
            SoundController::getInstance().playButtonClickSound();
            break;

        default:
            break;
    }
}

//Handle Mouse click
void UIController::handleMouseClick(sf::Vector2f pos, sf::Mouse::Button button) {
    if (button == sf::Mouse::Left && currentState == GameState::PLAYING) {
        sf::FloatRect gameArea(10, 100, 850, 540);
        if (gameArea.contains(pos)) {
            Tower* selectedTower = nullptr;
            switch(gameData.selectedTower) {
                case 1: selectedTower = Tower::createTower("Puncher"); break;
                case 2: selectedTower = Tower::createTower("Freezer"); break;
                case 3: selectedTower = Tower::createTower("Bomber"); break;
                default: break;
            }

            if (selectedTower && economy->buyTower(selectedTower)) {
                gameData.money = economy->getGoldAmount();
                SoundController::getInstance().playTowerPlaceSound();
                if (windowView) {
                    windowView->updateMoney(gameData.money);
                    SoundController::getInstance().playMoneySound();
                }
            }
        }
    }
}

//Handle button click
void UIController::handleButtonClick(const std::string& buttonId) {
    if (buttonId == "start") {
        startGame();
        SoundController::getInstance().playBackgroundMusic();
    } else if (buttonId == "pause") {
        pauseGame();
        SoundController::getInstance().playButtonClickSound();
    } else if (buttonId == "play") {
        resumeGame();
        SoundController::getInstance().playButtonClickSound();
    } else if (buttonId == "quit") {
        quitGame();
        SoundController::getInstance().playButtonClickSound();
    } else if (buttonId == "next_wave") {
        waveManager->forceStartWave();
        SoundController::getInstance().playButtonClickSound();
        SoundController::getInstance().playWaveStartSound();
    } else if (buttonId.substr(0, 11) == "difficulty_") {
        int difficulty = std::stoi(buttonId.substr(11));
        setDifficulty(difficulty);
        SoundController::getInstance().playButtonClickSound();
    } else if (buttonId.substr(0, 4) == "map_") {
        int level = std::stoi(buttonId.substr(4));
        selectLevel(level);
        SoundController::getInstance().playButtonClickSound();
    } else if (buttonId.substr(0, 6) == "tower_") {
        int towerType = std::stoi(buttonId.substr(6));
        gameData.selectedTower = towerType;
        SoundController::getInstance().playButtonClickSound();
    } else if (buttonId == "mute_toggle") {
        toggleMute();
        SoundController::getInstance().playButtonClickSound();
    }
}

//Handle volume change
void UIController::handleVolumeChange(float volume) {
    setVolume(volume);
}

//Handle scroll
void UIController::handleScroll(bool up) {
    if (up) {
        scrollScoresUp();
    } else {
        scrollScoresDown();
    }
}

//Set state
void UIController::setState(GameState state) {
    if (currentState != state) {
        GameState oldState = currentState;
        previousState = currentState;
        currentState = state;
        onStateChange(oldState, state);
    }
}

//change state
void UIController::onStateChange(GameState oldState, GameState newState) {
    switch (newState) {
        case GameState::PLAYING:
            gameData.isPaused = false;
            gameController->startGame();
            break;

        case GameState::PAUSED:
            gameData.isPaused = true;
            gameController->pauseGame();
            break;

        case GameState::MENU:
            resetGameData();
            gameController->quitGame();
            break;

        case GameState::GAME_OVER:
            handleGameOver();
            break;
    }
}

//Reset game data
void UIController::resetGameData() {
    gameData.score = 0;
    gameData.money = 100;
    gameData.lives = 100;
    gameData.currentWave = 1;
    gameData.waveCountdown = 30.0f;
    economy->goldAmount = gameData.money;
}

//Handle game over
void UIController::handleGameOver() {
    if (gameData.score > 0) {
        ScoreEntry entry;
        entry.username = "Player"; // need to be changed when user class will be done
        entry.score = gameData.score;
        highScores.push_back(entry);

        std::sort(highScores.begin(), highScores.end(),
            [](const ScoreEntry& a, const ScoreEntry& b) {
                return a.score > b.score;
            });
    }
}

//Start game
void UIController::startGame() {
    if (canStartGame()) {
        setState(GameState::PLAYING);
        waveManager->setDifficulty(difficultyToString(gameData.selectedDifficulty));
        gameController->loginPlayer("Player"); // need to be changed when user class will be done
    }
}

//Pause game
void UIController::pauseGame() {
    if (currentState == GameState::PLAYING) {
        setState(GameState::PAUSED);
    }
}

//Resume game
void UIController::resumeGame() {
    if (currentState == GameState::PAUSED) {
        setState(GameState::PLAYING);
    }
}

//Quit game
void UIController::quitGame() {
    setState(GameState::MENU);
}

//Restart game
void UIController::restartGame() {
    setState(GameState::MENU);
    startGame();
}

//Set difficulty
void UIController::setDifficulty(int difficulty) {
    if (difficulty >= 1 && difficulty <= 3) {
        gameData.selectedDifficulty = difficulty;
        waveManager->setDifficulty(difficultyToString(difficulty));
    }
}

//Select level
void UIController::selectLevel(int levelNumber) {
    gameData.selectedLevel = levelNumber;
    SoundController::getInstance().playButtonClickSound();
    if (windowView) {
        windowView->setMessage("Level " + std::to_string(levelNumber) + " selected!");
    }
}

//Set volume
void UIController::setVolume(float volume) {
    gameData.volume = std::max(0.f, std::min(1.f, volume));
    gameData.isMuted = (gameData.volume == 0.f);

    // Sync with SoundController
    SoundController::getInstance().setMasterVolume(gameData.volume * 100.0f);

    if (windowView) {
        windowView->updateVolumeDisplay(gameData.volume, gameData.isMuted);
    }
}

//toogle mute
void UIController::toggleMute() {
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

//Update deltatime
void UIController::update(float deltaTime) {
    if (currentState == GameState::PLAYING) {
        updateGameLogic(deltaTime);
    }

    updateMessageSystem(deltaTime);

    if (windowView) {
        syncUIWithGameData();
    }
}

//Update game logic
void UIController::updateGameLogic(float deltaTime) {
    if (gameData.isPaused) return;

    // Update WaveManager
    waveManager->update(deltaTime);

    // Update GameController
    gameController->update(deltaTime);

    //update game data
    gameData.lives = Tower::getInstance().getBaseHealth();
    gameData.money = economy->getGoldAmount();
    gameData.currentWave = waveManager->getCurrentWaveNumber();
    gameData.waveCountdown = waveManager->getWaveTimer();

    // Verify if game is over
    if (gameData.lives <= 0) {
        setState(GameState::GAME_OVER);
        SoundController::getInstance().GameOverSound();
    }
}

//Update ui message
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
    }
}

//Sync Ui with game data
void UIController::syncUIWithGameData() {
    windowView->updateScore(gameData.score);
    windowView->updateMoney(gameData.money);
    windowView->updateLives(gameData.lives);
    windowView->updateWaveCountdown(static_cast<int>(gameData.waveCountdown));

    if (hasActiveMessage()) {
        windowView->setMessage(currentMessage);
    }
}

//Start game
bool UIController::canStartGame() const {
    return currentState == GameState::MENU;
}

//Difficulty to string
std::string UIController::difficultyToString(int difficulty) const {
    switch (difficulty) {
        case 1: return "private";
        case 2: return "corporal";
        case 3: return "sergeant";
        default: return "private";
    }
}

//String to difficulty
int UIController::stringToDifficulty(const std::string& difficulty) const {
    if (difficulty == "private") return 1;
    if (difficulty == "corporal") return 2;
    if (difficulty == "sergeant") return 3;
    return 1;
}

//Show message on ui
void UIController::showMessage(const std::string& message, float duration) {
    messageQueue.push({message, duration});
}

//Get current message
std::string UIController::getCurrentMessage() const {
    return currentMessage;
}

//Active message
bool UIController::hasActiveMessage() const {
    return messageTimer > 0.0f;
}

//Add username
void UIController::addUsername(const std::string& username) {
    usernames.push_back(username);
    if (windowView) {
        windowView->addScoreEntry(username + ": " + std::to_string(gameData.score));
    }
}

//get high score
std::vector<ScoreEntry> UIController::getHighScores() const {
    return highScores;
}

//Scroll up
void UIController::scrollScoresUp() {
    if (scrollOffset > 0) {
        scrollOffset--;
        if (windowView) {
            windowView->updateScrollDisplay(scrollOffset);
        }
    }
}

//Scroll down
void UIController::scrollScoresDown() {
    scrollOffset++;
    if (windowView) {
        windowView->updateScrollDisplay(scrollOffset);
    }
}

//Force next wave
void UIController::forceNextWave() {
    waveManager->forceNextWave();
}

//Notify click
void UIController::notifyClick(sf::Vector2f pos, const std::string& buttonId) {
    SoundController::getInstance().playButtonClickSound();
    handleButtonClick(buttonId);
}

//notify username input
void UIController::notifyUsernameInput(const std::string& input) {
    updateUsernameInput(input);
}

//Update score
void UIController::updateScore(int score) {
    gameData.score = score;
    syncUIWithGameData();
}

//update money
void UIController::updateMoney(int money) {
    gameData.money = money;
    syncUIWithGameData();
}

//Update lives
void UIController::updateLives(int lives) {
    gameData.lives = lives;
    syncUIWithGameData();
}

//update Wave Countdown
void UIController::updateWaveCountdown(int countdown) {
    gameData.waveCountdown = static_cast<float>(countdown);
    syncUIWithGameData();
}

//Set message show message
void UIController::setMessage(const std::string& message) {
    showMessage(message);
}

//Update username input
void UIController::updateUsernameInput(const std::string& text) {
    usernameInput = text;
    if (windowView) {
        windowView->updateUsernameDisplay(text);
    }
}

//Get username input
std::string UIController::getUsernameInput() const {
    return usernameInput;
}

//Handle text input
void UIController::handleTextInput(sf::Uint32 unicode) {
    // Handle backspace
    if (unicode == 8 && !usernameInput.empty()) {
        usernameInput.pop_back();
    }
    // Handle regular characters (printable ASCII)
    else if (unicode >= 32 && unicode < 127) {
        usernameInput += static_cast<char>(unicode);
    }

    if (windowView) {
        windowView->updateUsernameDisplay(usernameInput);
    }
}

//Update volume slider position - REMOVED (handled by updateVolumeDisplay)
void UIController::updateVolumeSliderPosition() {
    if (windowView) {
        windowView->updateVolumeDisplay(gameData.volume, gameData.isMuted);
    }
}

//Scroll up - REMOVED (handled by scrollScoresUp)
void UIController::scrollUp() {
    scrollScoresUp();
}

//Scroll down - REMOVED (handled by scrollScoresDown)
void UIController::scrollDown() {
    scrollScoresDown();
}

//Handle scroll event
void UIController::handleScrollEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0) {
            scrollScoresUp();
        } else {
            scrollScoresDown();
        }
    }
}

//Handle click
void UIController::handleClick(sf::Vector2f mousePos) {
    if (windowView) {
        windowView->handleClick(mousePos);
    }
}

//Set register callback
void UIController::setRegisterCallback(const std::function<void(const std::string&)>& callback) {
    registerCallback = callback;
}
/*
 *Old version without Will depend on Ui ...
 */
/*
#include "../../../includes/logic/controllers/UIController.h"
#include "../../../includes/logic/controllers/EventController.h"
#include "../includes/graphics/views/WindowView.h"
#include <iostream>
#include <algorithm>

UIController::UIController()
    : currentState(GameState::MENU)
    , previousState(GameState::MENU)
    , windowView(nullptr)
    , eventController(nullptr)
    , gameController(std::make_shared<GameController>())
    , waveManager(std::make_shared<WaveManager>())
    , economy(std::unique_ptr<Economy>(new Economy()))
    , scrollOffset(0)
    , usernameInput("")
    , registerCallback(nullptr)
    , usernames()
    , highScores()
    , currentMessage("")
    , messageTimer(0.0f)
    , messageQueue()
{
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

    // Sync init sound and volume
    SoundController::getInstance().initializeGameAudio();
    SoundController::getInstance().setMasterVolume(gameData.volume * 100.0f);
}

//To notify volume change
void UIController::notifyVolumeChange(float newVolume) {
    if (windowView) {
        windowView->updateVolumeSliderPosition();
    }
}

//To notify toggle mute
void UIController::notifyMuteToggle() {
    if (windowView) {
        windowView->updateVolumeSliderPosition();
    }
}

//To notify scroll
void UIController::notifyScroll(bool up) {
    if (windowView) {
        if (up) {
            windowView->scrollUp();
        } else {
            windowView->scrollDown();
        }
    }
}

//To connect with View
void UIController::connectWithWindowView(WindowView* wv) {
    windowView = wv;
}

//To connect with event controller
void UIController::connectWithEventController(const std::shared_ptr<EventController>& eventCtrl) {
    eventController = eventCtrl;
    setupEventCallbacks();
}

//To set up event callbacks
void UIController::setupEventCallbacks() {
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
}

//To handle key press
void UIController::handleKeyPress(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Space:
            if (currentState == GameState::PLAYING) {
                waveManager->forceStartWave();
                SoundController::getInstance().playWaveStartSound();
            }
            break;

        case sf::Keyboard::P:
        case sf::Keyboard::Escape:
            if (currentState == GameState::PLAYING) {
                pauseGame();
                SoundController::getInstance().playButtonClickSound();
            } else if (currentState == GameState::PAUSED) {
                resumeGame();
                SoundController::getInstance().playButtonClickSound();
            }
            break;

        case sf::Keyboard::Num1:
        case sf::Keyboard::Num2:
        case sf::Keyboard::Num3:
            setDifficulty(key - sf::Keyboard::Num1 + 1);
            SoundController::getInstance().playButtonClickSound();
            break;

        default:
            break;
    }
}

//Handle Mouse click
void UIController::handleMouseClick(sf::Vector2f pos, sf::Mouse::Button button) {
    if (button == sf::Mouse::Left && currentState == GameState::PLAYING) {
        sf::FloatRect gameArea(10, 100, 850, 540);
        if (gameArea.contains(pos)) {
            Tower* selectedTower = nullptr;
            switch(gameData.selectedTower) {
                case 1: selectedTower = Tower::createTower("Puncher"); break;
                case 2: selectedTower = Tower::createTower("Freezer"); break;
                case 3: selectedTower = Tower::createTower("Bomber"); break;
                default: break;
            }

            if (selectedTower && economy->buyTower(selectedTower)) {
                gameData.money = economy->getGoldAmount();
                SoundController::getInstance().playTowerPlaceSound();
                if (windowView) {
                    windowView->updateMoney(gameData.money);
                    SoundController::getInstance().playMoneySound();
                }
            }
        }
    }
}

//Handle button click
void UIController::handleButtonClick(const std::string& buttonId) {
    if (buttonId == "start") {
        startGame();
        SoundController::getInstance().playBackgroundMusic();
    } else if (buttonId == "pause") {
        pauseGame();
        SoundController::getInstance().playButtonClickSound();
    } else if (buttonId == "play") {
        resumeGame();
        SoundController::getInstance().playButtonClickSound();
    } else if (buttonId == "quit") {
        quitGame();
        SoundController::getInstance().playButtonClickSound();
    } else if (buttonId == "next_wave") {
        waveManager->forceStartWave();
        SoundController::getInstance().playButtonClickSound();
        SoundController::getInstance().playWaveStartSound();
    } else if (buttonId.substr(0, 11) == "difficulty_") {
        int difficulty = std::stoi(buttonId.substr(11));
        setDifficulty(difficulty);
        SoundController::getInstance().playButtonClickSound();
    } else if (buttonId.substr(0, 4) == "map_") {
        int level = std::stoi(buttonId.substr(4));
        selectLevel(level);
        SoundController::getInstance().playButtonClickSound();
    } else if (buttonId.substr(0, 6) == "tower_") {
        int towerType = std::stoi(buttonId.substr(6));
        gameData.selectedTower = towerType;
        SoundController::getInstance().playButtonClickSound();
    } else if (buttonId == "mute_toggle") {
        toggleMute();
        SoundController::getInstance().playButtonClickSound();
    }
}

//Handle volume change
void UIController::handleVolumeChange(float volume) {
    setVolume(volume);
}

//Handle scroll
void UIController::handleScroll(bool up) {
    if (up) {
        scrollScoresUp();
    } else {
        scrollScoresDown();
    }
}

//Set state
void UIController::setState(GameState state) {
    if (currentState != state) {
        GameState oldState = currentState;
        previousState = currentState;
        currentState = state;
        onStateChange(oldState, state);
    }
}

//change state
void UIController::onStateChange(GameState oldState, GameState newState) {
    switch (newState) {
        case GameState::PLAYING:
            gameData.isPaused = false;
            gameController->startGame();
            break;

        case GameState::PAUSED:
            gameData.isPaused = true;
            gameController->pauseGame();
            break;

        case GameState::MENU:
            resetGameData();
            gameController->quitGame();
            break;

        case GameState::GAME_OVER:
            handleGameOver();
            break;
    }
}

//Reset game data
void UIController::resetGameData() {
    gameData.score = 0;
    gameData.money = 100;
    gameData.lives = 100;
    gameData.currentWave = 1;
    gameData.waveCountdown = 30.0f;
    economy->goldAmount = gameData.money;
}

//Handle game over
void UIController::handleGameOver() {
    if (gameData.score > 0) {
        ScoreEntry entry;
        entry.username = "Player"; // need to be changed when user class will be done
        entry.score = gameData.score;
        highScores.push_back(entry);

        std::sort(highScores.begin(), highScores.end(),
            [](const ScoreEntry& a, const ScoreEntry& b) {
                return a.score > b.score;
            });
    }
}

//Start game
void UIController::startGame() {
    if (canStartGame()) {
        setState(GameState::PLAYING);
        waveManager->setDifficulty(difficultyToString(gameData.selectedDifficulty));
        gameController->loginPlayer("Player"); // need to be changed when user class will be done
    }
}

//Pause game
void UIController::pauseGame() {
    if (currentState == GameState::PLAYING) {
        setState(GameState::PAUSED);
    }
}

//Resume game
void UIController::resumeGame() {
    if (currentState == GameState::PAUSED) {
        setState(GameState::PLAYING);
    }
}

//Quit game
void UIController::quitGame() {
    setState(GameState::MENU);
}

//Restart game
void UIController::restartGame() {
    setState(GameState::MENU);
    startGame();
}

//Set difficulty
void UIController::setDifficulty(int difficulty) {
    if (difficulty >= 1 && difficulty <= 3) {
        gameData.selectedDifficulty = difficulty;
        waveManager->setDifficulty(difficultyToString(difficulty));
    }
}

//Select level
void UIController::selectLevel(int levelNumber) {
    gameData.selectedLevel = levelNumber;
    SoundController::getInstance().playButtonClickSound();
    if (windowView) {
        windowView->setMessage("Level " + std::to_string(levelNumber) + " selected!");
    }
}

//Set volume
void UIController::setVolume(float volume) {
    gameData.volume = std::max(0.f, std::min(1.f, volume));
    gameData.isMuted = (gameData.volume == 0.f);

    // Sync with SoundController
    SoundController::getInstance().setMasterVolume(gameData.volume * 100.0f);

    if (windowView) {
        windowView->updateVolumeSliderPosition();
    }
}

//toogle mute
void UIController::toggleMute() {
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
        windowView->updateVolumeSliderPosition();
    }
}

//Update deltatime
void UIController::update(float deltaTime) {
    if (currentState == GameState::PLAYING) {
        updateGameLogic(deltaTime);
    }

    updateMessageSystem(deltaTime);

    if (windowView) {
        syncUIWithGameData();
    }
}

//Update game logic
void UIController::updateGameLogic(float deltaTime) {
    if (gameData.isPaused) return;

    // Update WaveManager
    waveManager->update(deltaTime);

    // Update GameController
    gameController->update(deltaTime);

    //update game data
    gameData.lives = Tower::getInstance().getBaseHealth();
    gameData.money = economy->getGoldAmount();
    gameData.currentWave = waveManager->getCurrentWaveNumber();
    gameData.waveCountdown = waveManager->getWaveTimer();

    // Verify if game is over
    if (gameData.lives <= 0) {
        setState(GameState::GAME_OVER);
        SoundController::getInstance().GameOverSound();
    }
}

//Update ui message
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
    }
}

//Sync Ui with game data
void UIController::syncUIWithGameData() {
    windowView->updateScore(gameData.score);
    windowView->updateMoney(gameData.money);
    windowView->updateLives(gameData.lives);
    windowView->updateWaveCountdown(static_cast<int>(gameData.waveCountdown));

    if (hasActiveMessage()) {
        windowView->setMessage(currentMessage);
    }
}

//Start game
bool UIController::canStartGame() const {
    return currentState == GameState::MENU;
}

//Difficulty to string
std::string UIController::difficultyToString(int difficulty) const {
    switch (difficulty) {
        case 1: return "private";
        case 2: return "corporal";
        case 3: return "sergeant";
        default: return "private";
    }
}

//String to difficulty
int UIController::stringToDifficulty(const std::string& difficulty) const {
    if (difficulty == "private") return 1;
    if (difficulty == "corporal") return 2;
    if (difficulty == "sergeant") return 3;
    return 1;
}

//Show message on ui
void UIController::showMessage(const std::string& message, float duration) {
    messageQueue.push({message, duration});
}

//Get current message
std::string UIController::getCurrentMessage() const {
    return currentMessage;
}

//Active message
bool UIController::hasActiveMessage() const {
    return messageTimer > 0.0f;
}

//Add username
void UIController::addUsername(const std::string& username) {
    usernames.push_back(username);
    if (windowView) {
        windowView->addUsername(username);
    }
}

//get high score
std::vector<ScoreEntry> UIController::getHighScores() const {
    return highScores;
}

//Scroll up
void UIController::scrollScoresUp() {
    if (windowView) {
        windowView->scrollUp();
    }
}

//Scroll down
void UIController::scrollScoresDown() {
    if (windowView) {
        windowView->scrollDown();
    }
}

//Force next wave
void UIController::forceNextWave() {
    waveManager->forceNextWave();
}

//Notify click
void UIController::notifyClick(sf::Vector2f pos, const std::string& buttonId) {
    SoundController::getInstance().playButtonClickSound();
    handleButtonClick(buttonId);
}

//notify username input
void UIController::notifyUsernameInput(const std::string& input) {
    updateUsernameInput(input);
}

//Update score
void UIController::updateScore(int score) {
    gameData.score = score;
    syncUIWithGameData();
}

//update money
void UIController::updateMoney(int money) {
    gameData.money = money;
    syncUIWithGameData();
}

//Update lives
void UIController::updateLives(int lives) {
    gameData.lives = lives;
    syncUIWithGameData();
}

//update Wave Countdown
void UIController::updateWaveCountdown(int countdown) {
    gameData.waveCountdown = static_cast<float>(countdown);
    syncUIWithGameData();
}

//Set message show message
void UIController::setMessage(const std::string& message) {
    showMessage(message);
}

//Update username input
void UIController::updateUsernameInput(const std::string& text) {
    usernameInput = text;
}

//Get username input
std::string UIController::getUsernameInput() const {
    return usernameInput;
}

//Handle text input
void UIController::handleTextInput(sf::Uint32 unicode) {
    // update this method need to be created
}

//Update volume slider position
void UIController::updateVolumeSliderPosition() {
    if (windowView) {
        windowView->updateVolumeSliderPosition();
    }
}

//Scroll up
void UIController::scrollUp() {
    if (windowView) {
        windowView->scrollUp();
    }
}

//Scroll down
void UIController::scrollDown() {
    if (windowView) {
        windowView->scrollDown();
    }
}

//Handle scroll event
void UIController::handleScrollEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0) {
            scrollUp();
        } else {
            scrollDown();
        }
    }
}

//Handle click
void UIController::handleClick(sf::Vector2f mousePos) {
    if (windowView) {
        windowView->handleClick(mousePos);
    }
}

//Set register callback
void UIController::setRegisterCallback(const std::function<void(const std::string&)>& callback) {
    registerCallback = callback;
}