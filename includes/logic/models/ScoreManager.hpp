#ifndef SCOREMANAGER_H_
#define SCOREMANAGER_H_

#include <iostream>
#include <vector>
#include <string>
#include "scoreEntry.h"

class ScoreManager {
    public:
    int score = 0;
    std::vector<scoreEntry> scoreList{};

    void addScore(std::string name,int score);
    std::vector<scoreEntry> getHighScores();
};







#endif
