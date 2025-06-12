#include "../models/ScoreManager.h"

/** creates a scoreEntry struct and places the name and score into it, then places that into the score list
 * @param name(string) the player's name
 * @param score(int) the score to be added
 */
void ScoreManager::addScore(std::string name, int score) {
    scoreEntry scoreToAdd;
    scoreToAdd.name = name;
    scoreToAdd.score = score;
    this->scoreList.push_back(scoreToAdd);
}

/** returns the list of scores
 */
std::vector<scoreEntry> ScoreManager::getHighScores() {
    return this->scoreList;
}

