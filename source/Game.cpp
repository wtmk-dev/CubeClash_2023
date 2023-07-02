#include "Game.h"

Game::Game(Controller* controllers[])
{
    for (int i = 0; i < MAX_CONTROLLERS; i++)
    {
        Controllers[i] = controllers[i];
    }
}

Game::~Game()
{
    // Clean up here
}

void Game::Start()
{
    // Start the game
}

void Game::Update()
{
    for (int i = 0; i < MAX_CONTROLLERS; i++)
    {
        if (Controllers[i] != nullptr)
        {
            Controllers[i]->Update();
        }
    }
}
