
#include "Game.h"
#include <iostream>


Game::Game() : currentWave(0), isGameOver(false) {

}


void Game::startGame() {

    isGameOver = false;


    }
}


void Game::endGame() {

    isGameOver = true;

    displayFinalScore();

    returnToMainMenu();
}


void Game::updateScore(int points) {

    scoreManager.addScore(points);
}


void Game::setupInitialWaves() {

    Wave wave1;
    wave1.waveNumber = 1;
    wave1.difficulty = "Easy";

    waves.push_back(wave1);


    Wave wave2;
    wave2.waveNumber = 2;
    wave2.difficulty = "Medium";

    waves.push_back(wave2);


}


void Game::displayFinalScore() {

    std::cout << "Game Over! Your final score is: " << scoreManager.score << std::endl;
}


void Game::returnToMainMenu() {

    std::cout << "Returning to the main menu..." << std::endl;
}