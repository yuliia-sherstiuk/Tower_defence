#include "ScoreManager.hpp"

void ScoreManager::addScore(std::string name, int score) {
    scoreEntry scoreToAdd;
    scoreToAdd.name = name;
    scoreToAdd.score = score;
    this->scoreList.push_back(scoreToAdd);
}

std::vector<scoreEntry> ScoreManager::getHighScores() {
    return this->scoreList;
}

