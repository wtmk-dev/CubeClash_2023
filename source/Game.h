#ifndef GAME_H
#define GAME_H

#include "Controller.h"

class Game {
private:
    static const int MAX_CONTROLLERS = 4; // Adjust the maximum number of controllers as needed
    Controller* Controllers[MAX_CONTROLLERS];

public:
    Game(Controller* controllers[]);
    ~Game();
    void Start();
    void Update();
};

#endif