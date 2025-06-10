/ GameController.h
#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Game.h"
#include "GameView.h"
#include "graphics/views/GameView.h"
#include "logic/models/Game.h"
#include <SFML/Graphics.hpp>



class GameController {
public:
    GameController();// Le constructeur initialise le jeu
    void update();
    void render(sf::RenderWindow& window, int playerMoney, int playerLives);

private:
    Game game;
    GameView gameView;
};

#endif // GAME_CONTROLLER_H
