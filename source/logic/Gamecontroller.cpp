// GameController.cpp


#include "logic/controllers/GameController.h"
#include "logic/models/ScoreManager.h" // 🔥 Добавим это
#include <thread>
#include <chrono>
#include <algorithm>

GameController::GameController() {
    game.startGame();

    // Initialiser les configurations de la tour
    auto& scoreManager = ScoreManager::getInstance();
    scoreManager.resetGold(1000);

    scoreManager.setTowerConfig("Archer", 100, 50, 0.6f);
    scoreManager.setTowerConfig("Cannon", 150, 70, 0.5f);
}

// Mettre à jour l'état du jeu
void GameController::update() {
    auto& enemies = game.getCurrentWaveEnemies();

    // S'il n'y a pas d'ennemis, nous faisons apparaître la vague suivante
    if (enemies.empty()) {
        game.spawnWave();
        return;
    }
    game.update();
    gameView.update();

    // Mettre à jour l'état des ennemis
    for (auto& enemy : enemies) {
        enemy.update();

        // Exemple : si un ennemi meurt, le joueur reçoit de l'or
        if (enemy.isDead()) {
            ScoreManager::getInstance().addGold(10); // 💰 Пример награды
        }
    }

    // Supprimez les ennemis qui ont atteint la fin du chemin
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& e) {
            return e.hasReachedEnd() || e.isDead(); // Убираем и мёртвых
        }),
        enemies.end()
    );

    // Mettre à jour la visualisation de l'ennemi
    gameView.update(enemies);

    // FPS ~60
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
}

// Rendu du jeu
void GameController::render(sf::RenderWindow& window, int playerMoney, int playerLives) {
    window.clear();

    // 💵 Nous transmettons la quantité actuelle d'or depuis ScoreManager
    int currentGold = ScoreManager::getInstance().getGold();

    gameView.renderGame(window, currentGold, playerLives);
    window.display();
}



void GameController::endGame() {
    gameView.showGameOver();
}