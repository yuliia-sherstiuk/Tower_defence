// GameController.cpp
#include "GameController.h"

void GameController::startGame() {
    game.startGame();
}

void GameController::updateGame() {
    game.update();
    gameView.update();
}

void GameController::endGame() {
    gameView.showGameOver();
}