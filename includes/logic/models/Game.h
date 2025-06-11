#ifndef GAME_H
#define GAME_H

#include <memory>
#include "controllers/WaveManager.h"
#include "utils/Level.h"

class Game {
public:
    Game();                              
    void start();                        
    void update(float deltaTime);       
    void stop();                         
    bool isRunning() const;             

private:
    std::unique_ptr<WaveManager> waveManager; 
    std::shared_ptr<Level> currentLevel;      
    bool running;                             
};
#endif // GAME_H