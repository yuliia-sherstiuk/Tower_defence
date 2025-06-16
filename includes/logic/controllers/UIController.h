
// Created by chris on 14/06/2025.
//

#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <queue>
#include <string>
#include <vector>
#include <functional>
#include "../graphics/views/WindowView.h"
#include "../../../includes/logic/controllers/SoundController.h"
#include "../logic/controllers/EventController.h"
#include "../logic/controllers/WaveManager.h"
#include "../logic/models/Economy.h"
#include "../logic/models/Tower.h"
#include "../logic/models/Enemy.h"

// Forward declaration instead of include
class GameController;

struct ScoreEntry {
    std::string username;
    int score;
    std::string difficulty;
    int level;
};

enum class GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};

class UIController {
public:
    UIController();

    // Method to connect
    void connectWithWindowView(WindowView* windowView);
    void connectWithEventController(const std::shared_ptr<EventController>& eventCtrl);

    //Game state
    GameState getCurrentState() const { return currentState; }
    void setState(GameState state);

    //Ui Getters
    int getBaseHealth() const { return gameData.lives; }
    int getGoldAmount() const { return gameData.money; }
    float getWaveCountdown() const { return gameData.waveCountdown; }
    int getCurrentWaveNumber() const { return gameData.currentWave; }
    std::string getCurrentDifficulty() const { return difficultyToString(gameData.selectedDifficulty); }
    int getCurrentLevel() const { return gameData.selectedLevel; }
    bool isGamePaused() const { return currentState == GameState::PAUSED; }
    bool isGameRunning() const { return currentState == GameState::PLAYING; }
    int getCurrentScore() const { return gameData.score; }
    float getVolume() const { return gameData.volume; }
    bool isMuted() const { return gameData.isMuted; }

    //Game actions
    void startGame();
    void pauseGame();
    void resumeGame();
    void quitGame();
    void restartGame();
    void forceNextWave();

    //Handle difficulty and map
    void setDifficulty(int difficulty);
    void selectLevel(int levelNumber);

    //Handle audio
    void setVolume(float volume);
    void toggleMute();

    //Handle scores
    void addUsername(const std::string& username);
    std::vector<ScoreEntry> getHighScores() const;
    void scrollScoresUp();
    void scrollScoresDown();

    //Handle messages
    void showMessage(const std::string& message, float duration = 3.0f);
    std::string getCurrentMessage() const;
    bool hasActiveMessage() const;

    //Update - MAIN COORDINATION POINT
    void update(float deltaTime);

    //WindowView notification methods
    void notifyClick(sf::Vector2f pos, const std::string& buttonId);
    void notifyUsernameInput(const std::string& input);
    void notifyVolumeChange(float newVolume) { setVolume(newVolume); }
    void notifyMuteToggle() { toggleMute(); }
    void notifyScroll(bool up) { if(up) scrollScoresUp(); else scrollScoresDown(); }

    //Get username methods
    std::vector<std::string> getUsernames() const { return usernames; }
    std::string getUsernameInput() const;
    std::string getCurrentUsernameInput() const { return getUsernameInput(); }

    //Scroll offset
    int getScrollOffset() const { return scrollOffset; }

    //Handle user input registration
    void handleUsernameInput(const std::string& input) { updateUsernameInput(input); }
    void registerUsername() { if (!usernameInput.empty()) addUsername(usernameInput); }

    //Update UI data methods
    void updateScore(int score);
    void updateMoney(int money);
    void updateLives(int lives);
    void updateWaveCountdown(int countdown);
    void setMessage(const std::string& message);

    //Handle user text input
    void updateUsernameInput(const std::string& text);
    void handleTextInput(sf::Uint32 unicode);

    //Handle volume display
    void updateVolumeSliderPosition();

    //Handle scrolling events
    void scrollUp() { scrollScoresUp(); }
    void scrollDown() { scrollScoresDown(); }
    void handleScrollEvent(const sf::Event& event);

    //Handle clicks
    void handleClick(sf::Vector2f mousePos);

    //Handle callbacks registration
    void setRegisterCallback(const std::function<void(const std::string&)>& callback);

    // Callback setters for GameController communication
    void setGameStartCallback(const std::function<void()>& callback) { gameStartCallback = callback; }
    void setGamePauseCallback(const std::function<void()>& callback) { gamePauseCallback = callback; }
    void setGamePlayCallback(const std::function<void()>& callback) { gamePlayCallback = callback; }
    void setGameQuitCallback(const std::function<void()>& callback) { gameQuitCallback = callback; }
    void setNextWaveCallback(const std::function<void()>& callback) { nextWaveCallback = callback; }
    void setTowerSelectionCallback(const std::function<void(int)>& callback) { towerSelectionCallback = callback; }
    void setMapSelectionCallback(const std::function<void(int)>& callback) { mapSelectionCallback = callback; }
    void setDifficultySelectionCallback(const std::function<void(int)>& callback) { difficultySelectionCallback = callback; }
    void setApplicationQuitCallback(const std::function<void()>& callback);

private:
    // Core state management
    GameState currentState;
    GameState previousState;

    // Connected components
    WindowView* windowView;
    std::shared_ptr<EventController> eventController;
    std::shared_ptr<GameController> gameController;
    std::shared_ptr<WaveManager> waveManager;
    std::unique_ptr<Economy> economy;

    // UI state
    int scrollOffset;
    std::string usernameInput;
    std::function<void(const std::string&)> registerCallback;
    std::vector<std::string> usernames;
    std::vector<ScoreEntry> highScores;

    // Message system
    std::string currentMessage;
    float messageTimer;
    std::queue<std::pair<std::string, float>> messageQueue;

    // Callback functions for GameController communication
    std::function<void()> gameStartCallback;
    std::function<void()> gamePauseCallback;
    std::function<void()> gamePlayCallback;
    std::function<void()> gameQuitCallback;
    std::function<void()> nextWaveCallback;
    std::function<void(int)> towerSelectionCallback;
    std::function<void(int)> mapSelectionCallback;
    std::function<void(int)> difficultySelectionCallback;
    std::function<void()> applicationQuitCallback;

    // Game data structure
    struct GameData {
        int score;
        int money;
        int lives;
        int currentWave;
        float waveCountdown;
        int selectedLevel;
        int selectedDifficulty;
        int selectedTower;
        float volume;
        bool isMuted;
        bool isPaused;
        bool isGameOver;
    } gameData;

    // Setup and configuration methods
    void setupGameControllerCallbacks();
    void setupEventCallbacks();

    // Synchronization methods
    void syncUIWithGameData();
    void syncFromGameController();

    // State management
    void onStateChange(GameState oldState, GameState newState);
    void resetGameData();
    void handleGameOver();

    // Event handlers
    void handleKeyPress(sf::Keyboard::Key key);
    void handleMouseClick(sf::Vector2f pos, sf::Mouse::Button button);
    void handleButtonClick(const std::string& buttonId);
    void handleVolumeChange(float volume);
    void handleScroll(bool up);

    // Utility methods
    std::string difficultyToString(int difficulty) const;
    int stringToDifficulty(const std::string& difficulty) const;
    bool canStartGame() const;
    void updateGameLogic(float deltaTime);
    void updateMessageSystem(float deltaTime);
};

#endif // UICONTROLLER_H
