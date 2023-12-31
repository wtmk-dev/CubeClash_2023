#include "Game.h"
#include "Caster.h"
#include <grrlib.h>
#include <stdlib.h>
#include <stdio.h>

//Assets
#include "Mage1Idle_png.h"
#include "Mage2Idle_png.h"
#include "Mage3Idle_png.h"
#include "Mage4Idle_png.h"
#include "Title_png.h"
#include "Mode_png.h"
#include "m1select_png.h"
#include "m2select_png.h"
#include "m3select_png.h"
#include "m4select_png.h"
#include "m5select_png.h"
#include "MageCasting_png.h"
#include "MageCastingFire_png.h"
#include "MageCastingWater_png.h"
#include "MageCastingLight_png.h"
#include "water_png.h"
#include "fire_png.h"
#include "light_png.h"
#include "shield_png.h"

Game::Game(Controller* controllers[])
{    
    for (int i = 0; i < MAX_CONTROLLERS; i++)
    {
        _Controllers[i] = controllers[i];
    }

    _Casters[0] = new Caster();
    _Casters[1] = new Caster();
    _Casters[2] = new Caster();
    _Casters[3] = new Caster();
}

Game::~Game()
{
    for (int i = 0; i < MAX_CONTROLLERS; i++)
    {
        delete _Casters[i];
        GRRLIB_FreeTexture(_MageSelection[i]);
        GRRLIB_FreeTexture(_MageIdle[i]);
    }

    GRRLIB_FreeTexture(title);
    GRRLIB_FreeTexture(mode);
}

void Game::Start()
{
    screen = start;

    _Casters[0]->Init(_Controllers[0]);
    _Casters[1]->Init(_Controllers[1]);
    _Casters[2]->Init(_Controllers[2]);
    _Casters[3]->Init(_Controllers[3]);

    _MageCasting[0] = GRRLIB_LoadTexturePNG(MageCasting_png);
    _MageCasting[1] = GRRLIB_LoadTexturePNG(MageCastingFire_png);
    _MageCasting[2] = GRRLIB_LoadTexturePNG(MageCastingLight_png);
    _MageCasting[3] = GRRLIB_LoadTexturePNG(MageCastingWater_png);

    _MageSelection[0] = GRRLIB_LoadTexturePNG(m1select_png);
    _MageSelection[1] = GRRLIB_LoadTexturePNG(m2select_png);
    _MageSelection[2] = GRRLIB_LoadTexturePNG(m3select_png);
    _MageSelection[3] = GRRLIB_LoadTexturePNG(m4select_png);
    _MageSelection[4] = GRRLIB_LoadTexturePNG(m5select_png);

    title = GRRLIB_LoadTexturePNG(Title_png);
    mode = GRRLIB_LoadTexturePNG(Mode_png);

    _MageIdle[0] = GRRLIB_LoadTexturePNG(Mage1Idle_png);
    _MageIdle[1] = GRRLIB_LoadTexturePNG(Mage2Idle_png);
    _MageIdle[2] = GRRLIB_LoadTexturePNG(Mage3Idle_png);
    _MageIdle[3] = GRRLIB_LoadTexturePNG(Mage4Idle_png);

    _MageSpell[0] = GRRLIB_LoadTexturePNG(shield_png);
    _MageSpell[1] = GRRLIB_LoadTexturePNG(fire_png);
    _MageSpell[2] = GRRLIB_LoadTexturePNG(light_png);
    _MageSpell[3] = GRRLIB_LoadTexturePNG(water_png);

    for (int i = 0; i < MAX_CONTROLLERS; i++)
    {
        if (_MageIdle[i] != nullptr)
        {
            GRRLIB_InitTileSet(_MageIdle[i], 64, 96, 0);
        }
        if (_MageCasting[i] != nullptr)
        {
            GRRLIB_InitTileSet(_MageCasting[i], 64, 96, 0);
        }
    }
}

void Game::Update()
{
    for (int i = 0; i < MAX_CONTROLLERS; i++)
    {
        if (_Controllers[i] != nullptr)
        {
            _Controllers[i]->Update();

            if(_Controllers[i]->Start_WasPressedThisFrame)
            {
                screen = credits;
            }
        }
    }

    if(screen == 0)
    {
        GRRLIB_SetBackgroundColour(0x0D, 0x37, 0x00, 0xFF);
        GRRLIB_DrawImg(60, 30, title, 0, 1, 1, 0xFFFFFFFF);

        if(!_Controllers[0]->A_WasHeldThisFrame)
        {
            std::string start = "- Hold A -";
            auto cstart = start.c_str();

            GRRLIB_PrintfTTF(300 + 1, 320 + 1, _Font, cstart, 12, 0x000000FF);
            GRRLIB_PrintfTTF(300, 320, _Font, cstart, 12, 0xFFFFFFFF);    
        }else
        {
            GRRLIB_DrawImg(100, 300, mode, 0, 1, 1, 0xFFFFFFFF);

            /*
            std::string noob = "_ Hold LEFT for noob mode";
            auto cnoob = noob.c_str();
            GRRLIB_PrintfTTF(150 + 1, 340 + 1, _Font, cnoob, 12, 0x000000FF);
            */

            std::string pvp = "_ Hold RIGHT for pvp mode";
            auto cpvp = pvp.c_str();
            GRRLIB_PrintfTTF(150 + 1, 360 + 1, _Font, cpvp, 12, 0x000000FF);

            if(_Controllers[0]->Right_WasHeldThisFrame)
            {
                screen = lobby;
            }else if(_Controllers[0]->Right_WasHeldThisFrame)
            {
                screen = tutorial;
            }
        }

    }else if(screen == tutorial)
    {
    }else if(screen == lobby)
    {
        GRRLIB_SetBackgroundColour(0x37, 0x0D, 0x00, 0xFF);
        auto x = 640/4;
        auto holdPos = 30;
                
        auto readyCount = 0;
        auto lobbyCount = 0;

        for (int i = 0; i < MAX_CONTROLLERS; i++)
        {
            auto caster = _Casters[i];
            if(caster->IsLockedIn)
            {
                readyCount++;
            }

            if(caster->IsInLobby)
            {
                lobbyCount++;
            }
        }

        if(lobbyCount >= 1)
        {
            if(readyCount == lobbyCount)
            {
                if(!allReady)
                {
                    transitionDelay = 0;
                }

                allReady = true;
            }else
            {
                allReady = false;
            }
        }

        if(allReady)
        {
            transitionDelay++;
            GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);

            if(transitionDelay >= 60)
            {
                GRRLIB_SetBackgroundColour(0xC0, 0xC0, 0xC0, 0xFF);
            }

            if(transitionDelay >= 120)
            {
                GRRLIB_SetBackgroundColour(0x80, 0x80, 0x80, 0xFF);
            }
            
            if(transitionDelay >= 180)
            {
                GRRLIB_SetBackgroundColour(0x40, 0x40, 0x40, 0xFF);
            }

            if(transitionDelay >= 240)
            {
                for (int i = 0; i < MAX_CONTROLLERS; i++)
                {
                    _Casters[i]->Reset();
                }
                screen = arena;
            }
        }

        for (int i = 0; i < MAX_CONTROLLERS; i++)
        {
            auto caster = _Casters[i];
            auto controller = _Controllers[i];

            if(i > 0)
            {
                holdPos += 160;
            }

            if(!caster->IsInLobby)
            {
                std::string noob = " - Press A -";
                auto cnoob = noob.c_str();

                GRRLIB_PrintfTTF(holdPos, 340 + 1, _Font, cnoob, 12, 0xFFFFFFFF);
            }else
            {
                auto offset = 160;

                if(i > 0)
                {
                    offset *= i;
                }else{
                    offset = 0;
                }

                if(!caster->IsLockedIn)
                {
                    GRRLIB_DrawImg(offset, 0, _MageSelection[caster->MageSelection], 0, 1, 1, 0xFFFFFFFF);

                    if(controller->Left_WasPressedThisFrame)
                    {
                        if(caster->MageSelection > 0)
                        {
                            caster->MageSelection--;
                        }
                    }else if(controller->Right_WasPressedThisFrame)
                    {
                        if(caster->MageSelection < 3)
                        {
                            caster->MageSelection++;
                        }
                    }

                    if(controller->A_WasPressedThisFrame)
                    {
                        caster->IsLockedIn = true;
                    }
                }else
                {
                    GRRLIB_DrawImg(offset, 0, _MageSelection[4], 0, 1, 1, 0xFFFFFFFF);

                    if(controller->B_WasPressedThisFrame)
                    {
                        caster->IsLockedIn = false;
                    }
                }
                
            }

            if(controller->A_WasPressedThisFrame)
            {
                if(!caster->IsInLobby)
                {
                    caster->IsInLobby = true;
                }
            }
        }

        GRRLIB_Line(3,480,3,0, 0x000000FF);
        GRRLIB_Line(2,480,2,0, 0x000000FF);
        GRRLIB_Line(1,480,1,0, 0x000000FF);
        GRRLIB_Line(x,480,x,0, 0x000000FF);
        GRRLIB_Line(x*2,480,x*2,0, 0x000000FF);
        GRRLIB_Line(x*3,480,x*3,0, 0x000000FF);
        GRRLIB_Line(638,480,638,0, 0x000000FF);
        GRRLIB_Line(639,480,639,0, 0x000000FF);
        GRRLIB_Line(640,480,640,0, 0x000000FF);

    }else if(screen == credits)
    {
        GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);

        GRRLIB_PrintfTTF(0, 480/2, _Font, "Thanks for playing!", 32, 0xFFFFFFFF);
        GRRLIB_PrintfTTF(640/3, 480/2-100, _Font, "-WTMK-", 32, 0xFFFFFFFF);
        GRRLIB_PrintfTTF(0, 480/2-160, _Font, "Created by Brandon Khan for cube clash 2023", 24, 0xFFFFFFFF);
        GRRLIB_PrintfTTF(0, 480/2-180, _Font, "Music By: Andrea Baroni - https://andreabaroni.com  ", 12, 0xFFFFFFFF);
    }
    
    for(int i = 0; i < MAX_CONTROLLERS; i++)
    {
        if(_Casters[i] != nullptr)
        {
            _Casters[i]->Update();
        }
    } // update inputs from frame

    if(screen == arena)
    {
        GRRLIB_SetBackgroundColour(0x32, 0x32, 0x32, 0xFF);

        for(int i = 0; i < MAX_CONTROLLERS; i++)
        {
            if(_Casters[i] != nullptr)
            {
                if(_Casters[i]->wasHitThisFrame)
                {
                    _Casters[i]->Combo = 0;
                    _Casters[i]->IsCasting = false;
                    _Casters[i]->wasHitThisFrame = false;

                    if(_Casters[i]->isShieldActive)
                    {
                        _Casters[i]->Charge = 0;
                        _Casters[i]->isShieldActive = false;
                    }
                }
            }
        }

        if(animationFrame > 5)
        {
            animationFrame = 0;
        }

        auto leftX = 30;
        auto rightX = 460;
        auto topY = 80;
        auto botY = 275;

        auto p1posX = leftX;
        auto p2posX = rightX;
        auto p3posX = leftX;
        auto p4posX = rightX;

        if(_Casters[0]->Position > 0)
        {
            p1posX += 32 * _Casters[0]->Position;
        }

        if(_Casters[1]->Position > 0)
        {
            p2posX += 32 * _Casters[1]->Position;
        }

        if(_Casters[2]->Position > 0)
        {
            p3posX += 32 * _Casters[2]->Position;
        }

        if(_Casters[3]->Position > 0)
        {
            p4posX += 32 * _Casters[3]->Position;
        }

        if(_Casters[0]->Life > 0)
        {
            GRRLIB_DrawTile(p1posX, topY, _MageIdle[_Casters[0]->MageSelection], 0, 1, 1, 0xFFFFFFFF, animationFrame);
        }

        if(_Casters[1]->Life > 0)
        {
            GRRLIB_DrawTile(p2posX, topY, _MageIdle[_Casters[1]->MageSelection], 0, -1, 1, 0xFFFFFFFF, animationFrame);
        }

        if(_Casters[2]->Life > 0)
        {
            GRRLIB_DrawTile(p3posX, botY, _MageIdle[_Casters[2]->MageSelection], 0, 1, 1, 0xFFFFFFFF, animationFrame);
        }
        
        if(_Casters[3]->Life > 0)
        {
            GRRLIB_DrawTile(p4posX , botY, _MageIdle[_Casters[3]->MageSelection], 0, -1, 1, 0xFFFFFFFF, animationFrame);
        }
    
        for(int i = 0; i < MAX_CONTROLLERS; i++)
        {
            auto caster =_Casters[i];

            if(_Casters[i]->isShieldActive)
            {
                if(_Casters[i]->Location == 0)
                {
                    GRRLIB_DrawImg(p1posX, topY, _MageSpell[0], 0, 1, 1, 0xFFFFFFFF);
                }

                if(_Casters[i]->Location == 1)
                {
                    GRRLIB_DrawImg(p2posX, topY, _MageSpell[0], 0, 1, 1, 0xFFFFFFFF);
                }

                if(_Casters[i]->Location == 2)
                {
                    GRRLIB_DrawImg(p3posX, botY, _MageSpell[0], 0, 1, 1, 0xFFFFFFFF);
                }

                if(_Casters[i]->Location == 3)
                {
                    GRRLIB_DrawImg(p4posX, botY, _MageSpell[0], 0, 1, 1, 0xFFFFFFFF);
                }
            }

            if(_Casters[i]->IsCasting && _Casters[i]->Spell != 0)
            {
                if(_Casters[_Casters[i]->Target]->Life > 0)
                {
                    if(_Casters[_Casters[i]->Target]->Position == _Casters[i]->TargetPosition)
                    {
                        if(_Casters[i]->Target == 0)
                        {
                            GRRLIB_DrawImg(p1posX, topY, _MageSpell[caster->Spell], 0, 1, 1, 0xFFFFFFFF);
                        }

                        if(_Casters[i]->Target == 1)
                        {
                            GRRLIB_DrawImg(p2posX, topY, _MageSpell[caster->Spell], 0, -1, 1, 0xFFFFFFFF);
                        }

                        if(_Casters[i]->Target == 2)
                        {
                            GRRLIB_DrawImg(p3posX, botY, _MageSpell[caster->Spell], 0, 1, 1, 0xFFFFFFFF);
                        }

                        if(_Casters[i]->Target == 3)
                        {
                            GRRLIB_DrawImg(p4posX, botY, _MageSpell[caster->Spell], 0, -1, 1, 0xFFFFFFFF);
                        }
                    }
                }
            }

            if(_Casters[i] != nullptr)
            {
                ResloveFrame(_Casters[i]);
            }
        } // update game state

        int dead = 0;
        for(int i = 0; i < MAX_CONTROLLERS; i++)
        {
            if(_Casters[i]->Life > 0)
            {
                UpdateCharging(_Casters[i],p1posX,topY,p2posX,topY,p3posX,botY,p4posX,botY);

                UpdateLife(_Casters[i],185+25-10,480-100+15,25,640-255,1);
                UpdateMana(_Casters[i],195+25-10,480-60-25+10,25,640-255,1);
                UpdateCombo(_Casters[i],100,480-185,110+45,640-170+45,1);
                UpdateSpell(_Casters[i],175+25-10,480-110+15,25,640-255,1);
                UpdateTarget(_Casters[i],60,480-195-25,10,640-280,1);
                UpdatePosition(_Casters[i],60-25,480-195-25-25,10,640-280,1);
            }else
            {
                dead++;
            }
        }

        if(dead >= 3)
        {
            GRRLIB_PrintfTTF(640/3, 480/2, _Font, "WINNER!", 32, 0x000000FF);
        }

        animationFrame++;
    } //update visual state
}

void Game::ResloveFrame(Caster* caster)
{
    if(caster->IsCasting)
    {
        caster->IsCasting = false;
        bool hasHit = false;

        for(int i = 0; i < MAX_CONTROLLERS; i++)
        {
            auto target = _Casters[i];
            if(target != nullptr && target->Life > 0)
            {
                if(target->Location == caster->Target)
                {
                    if(target->Position == caster->TargetPosition)
                    {
                        caster->Mana += caster->Charge;
                        caster->Combo++;

                        int damage = 1 + caster->Charge * caster->Combo;

                        if(target->IsCharging)
                        {
                            if(target->Spell == target->isShieldActive)
                            {
                                damage -= target->Charge;
                            }else if(target->Spell == target->_Light && caster->Spell == caster->_Fire)
                            {
                                damage *= 2;
                            }else if(target->Spell == target->_Fire && caster->Spell == caster->_Water)
                            {
                                damage *= 2;
                            }else if(target->Spell == target->_Water && caster->Spell == caster->_Light)
                            {
                                damage *= 2;
                            }
                        }

                        target->wasHitThisFrame = true;
                        hasHit = true;
                        caster->Charge = 0;

                        if(damage > 0)
                        {
                            target->Life -= damage;
                        }
                    }
                }
            }

            if(hasHit)
            {
                break;
            }
        }

        if(!hasHit)
        {
            caster->Combo = 0;
        }
    }
}

void Game::UpdateProperty(int location, int topY, int botY, int leftX, int rightX, int offset, std::string str)
{
    auto cstr = str.c_str();

    if(location == 0)
    {
        GRRLIB_PrintfTTF(leftX + offset, topY + offset, _Font, cstr, 12, 0x000000FF);
        GRRLIB_PrintfTTF(leftX, topY, _Font, cstr, 12, 0xFFFFFFFF);
    }
    else if(location == 1)
    {
        GRRLIB_PrintfTTF(rightX + offset, topY + offset, _Font, cstr, 12, 0x000000FF);
        GRRLIB_PrintfTTF(rightX, topY, _Font, cstr, 12, 0xFFFFFFFF);
    }else if(location == 2)
    {
        GRRLIB_PrintfTTF(leftX + offset, botY + offset, _Font, cstr, 12, 0x000000FF);
        GRRLIB_PrintfTTF(leftX, botY, _Font, cstr, 12, 0xFFFFFFFF);
    }else if(location == 3)
    {
        GRRLIB_PrintfTTF(rightX + offset, botY + offset, _Font, cstr, 12, 0x000000FF);
        GRRLIB_PrintfTTF(rightX, botY, _Font, cstr, 12, 0xFFFFFFFF);
    }
}

void Game::UpdateTarget(Caster* caster, int topY, int botY, int leftX, int rightX, int offset)
{
    std::string str = "Target: " + std::to_string(caster->Target);
    str += " Position " + std::to_string(caster->TargetPosition);

    UpdateProperty(caster->Location,topY,botY,leftX,rightX,offset,str);
}

void Game::UpdateSpell(Caster* caster, int topY, int botY, int leftX, int rightX, int offset)
{
    char str[40];
    
    if(caster->Spell == caster->_Shield)
    {
        sprintf(str, "Shield: %f", caster->Charge);
    }else if(caster->Spell == caster->_Fire)
    {
        sprintf(str, "Fire: %f", caster->Charge);
    }else if(caster->Spell == caster->_Water)
    {
        sprintf(str, "Water: %f", caster->Charge);
    }else if(caster->Spell == caster->_Light)
    {
        sprintf(str, "Light: %f", caster->Charge);
    }

    UpdateProperty(caster->Location,topY,botY,leftX,rightX,offset,str);
}

void Game::UpdateCharging(Caster* caster, int p1x, int p1y, int p2x, int p2y, int p3x, int p3y, int p4x, int p4y)
{
    if(caster->IsCharging)
    {
        if(caster->Location == 0)
        {
            GRRLIB_DrawTile(p1x, p1y, _MageCasting[caster->Spell], 0, 1, 1, 0xFFFFFFFF, animationFrame);
        }

        if(caster->Location == 1)
        {
            GRRLIB_DrawTile(p2x, p2y, _MageCasting[caster->Spell], 0, 1, 1, 0xFFFFFFFF, animationFrame);
        }

        if(caster->Location == 2)
        {
            GRRLIB_DrawTile(p3x, p3y, _MageCasting[caster->Spell], 0, 1, 1, 0xFFFFFFFF, animationFrame);
        }

        if(caster->Location == 3)
        {
            GRRLIB_DrawTile(p4x, p4y, _MageCasting[caster->Spell], 0, 1, 1, 0xFFFFFFFF, animationFrame);
        }
    }
}

void Game::UpdateCombo(Caster* caster, int topY, int botY, int leftX, int rightX, int offset)
{
    char str[20];  
    sprintf(str, "Combo: %d", caster->Combo);
    UpdateProperty(caster->Location,topY,botY,leftX,rightX,offset,str);
}

void Game::UpdateMana(Caster* caster, int topY, int botY, int leftX, int rightX, int offset)
{
    char str[20];  
    sprintf(str, "Mana: %f", caster->Mana);
    UpdateProperty(caster->Location,topY,botY,leftX,rightX,offset,str);
}

void Game::UpdateLife(Caster* caster, int topY, int botY, int leftX, int rightX, int offset)
{
    char str[20];  
    sprintf(str, "Life: %d", caster->Life);
    UpdateProperty(caster->Location,topY,botY,leftX,rightX,offset,str);
}

void Game::UpdatePosition(Caster* caster, int topY, int botY, int leftX, int rightX, int offset)
{
    char str[10];  
    sprintf(str, "%d", caster->Position);
    UpdateProperty(caster->Location,topY,botY,leftX,rightX,offset,str);
}

void Game::SetFont(GRRLIB_ttfFont* font)
{
    _Font = font;
}

