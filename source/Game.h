#ifndef GAME_H
#define GAME_H

#include "Controller.h"
#include "Caster.h"
#include <grrlib.h>
#include <string>

class Game {
private:
    static const int MAX_CONTROLLERS = 4; // Adjust the maximum number of controllers as needed
    Controller* _Controllers[MAX_CONTROLLERS];
    Caster* _Casters[MAX_CONTROLLERS];
    GRRLIB_ttfFont* _Font;
    GRRLIB_texImg* title; 
    GRRLIB_texImg* mode, mage1Idle, mage2, mage3, mage4;
    int screen = 0; 
    int start = 0;
    int tutorial = 1; 
    int lobby = 2; 
    int arena = 3; 
    int credits = 4;
    void UpdatePosition(Caster* caster, int topY, int botY, int leftX, int rightX, int offset);
    void UpdateLife(Caster* caster, int topY, int botY, int leftX, int rightX, int offset);
    void UpdateMana(Caster* caster, int topY, int botY, int leftX, int rightX, int offset);
    void UpdateCombo(Caster* caster, int topY, int botY, int leftX, int rightX, int offset);
    void UpdateCharging(Caster* caster, int topY, int botY, int leftX, int rightX, int offset);
    void UpdateSpell(Caster* caster, int topY, int botY, int leftX, int rightX, int offset);
    void UpdateTarget(Caster* caster, int topY, int botY, int leftX, int rightX, int offset);
    void UpdateProperty(int location, int topY, int botY, int leftX, int rightX, int offset, std::string str);
    void ResloveFrame(Caster* caster);
public:
    Game(Controller* controllers[]);
    ~Game();
    void Start();
    void Update();
    void SetFont(GRRLIB_ttfFont* font);
};

#endif