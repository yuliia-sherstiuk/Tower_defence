#ifndef SCOREMANAGER_H_
#define SCOREMANAGER_H_

#include <iostream>
#include <vector>
#include <string>
#include "models/scoreEntry.h"

/** class to manage scores of players */
class ScoreManager {
    public:

    std::vector<scoreEntry> scoreList{}; //list of all scores

    void addScore(std::string name,int score);
    std::vector<scoreEntry> getHighScores();
};


#endif
