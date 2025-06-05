/ GameController.h
#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Game.h"
#include "GameView.h"

class GameController {
public:
    Game game;
    GameView gameView;

    void startGame();
    void updateGame();
    void endGame();
};

#endif // GAMECONTROLLER_H