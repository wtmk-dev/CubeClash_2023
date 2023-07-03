/*===========================================
        TrueType Font demo
============================================*/
#include <grrlib.h>

#include <stdlib.h>
#include <stdio.h>
#include <ogc/pad.h>
#include <ogc/lwp_watchdog.h>   // Needed for gettime and ticks_to_millisecs

#include "Game.h"
#include "Caster.h"

// Font
#include "FreeMonoBold_ttf.h"

//RGBA Colors
#define GRRLIB_BLACK   0x000000FF
#define GRRLIB_MAROON  0x800000FF
#define GRRLIB_GREEN   0x008000FF
#define GRRLIB_OLIVE   0x808000FF
#define GRRLIB_NAVY    0x000080FF
#define GRRLIB_PURPLE  0x800080FF
#define GRRLIB_TEAL    0x008080FF
#define GRRLIB_GRAY    0x808080FF
#define GRRLIB_SILVER  0xC0C0C0FF
#define GRRLIB_RED     0xFF0000FF
#define GRRLIB_LIME    0x00FF00FF
#define GRRLIB_YELLOW  0xFFFF00FF
#define GRRLIB_BLUE    0x0000FFFF
#define GRRLIB_FUCHSIA 0xFF00FFFF
#define GRRLIB_AQUA    0x00FFFFFF
#define GRRLIB_WHITE   0xFFFFFFFF

// Prototype
static u8 CalculateFrameRate();

int main(int argc, char **argv)
{
    bool ShowFPS = false;

    //Int GRRLIB
    // Initialise the Graphics & Video subsystem
    GRRLIB_Init();

    // Initialise the controllers
    PAD_Init();

    // Load the font from memory
    GRRLIB_ttfFont* myFont = GRRLIB_LoadTTF(FreeMonoBold_ttf, FreeMonoBold_ttf_size);

    // Seed the random-number generator with current time so that
    // the numbers will be different every time we run.
    srand(time(NULL));

    // To have a cool effect anti-aliasing is turned on
    GRRLIB_Settings.antialias = true;

    // Black background
    GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);

    //Init Game    
    Controller* Controllers[4];
    Controllers[0] = new Controller(0);
    Controllers[1] = new Controller(1);
    Controllers[2] = new Controller(2);
    Controllers[3] = new Controller(3);

    Game* game = new Game(Controllers);
    game->SetFont(myFont);
    game->Start();

    // Loop forever
    while (1)
    {
        if (ShowFPS == true)
        {
            char FPS[255];
            snprintf(FPS, sizeof(FPS), "Current FPS: %d", CalculateFrameRate());
            GRRLIB_PrintfTTF(500 + 1, 25 + 1, myFont, FPS, 12, 0x000000FF);
            GRRLIB_PrintfTTF(500, 25, myFont, FPS, 12, 0xFFFFFFFF);
        }
    
        PAD_ScanPads();  //Scan the GameCube controllers
        game->Update();  //Update game logic
        GRRLIB_Render(); // Render the frame buffer to the TV
    }

    for (int i = 0; i < 4; i++)
    {
        delete Controllers[i];
    }

    delete game;

    GRRLIB_Exit(); // Be a good person, clear the memory allocated by GRRLIB
    return 0;
}

/**
 * This function calculates the number of frames we render each second.
 * @return The number of frames per second.
 */
static u8 CalculateFrameRate()
{
    static u8 frameCount = 0;
    static u32 lastTime;
    static u8 FPS = 0;
    u32 currentTime = ticks_to_millisecs(gettime());

    frameCount++;
    if (currentTime - lastTime > 1000)
    {
        lastTime = currentTime;
        FPS = frameCount;
        frameCount = 0;
    }
    return FPS;
}
