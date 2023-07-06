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
    }

    GRRLIB_FreeTexture(title);
    GRRLIB_FreeTexture(mode);

    /*
    GRRLIB_FreeTexture(mage1Idle);
    GRRLIB_FreeTexture(mage2);
    GRRLIB_FreeTexture(mage3);
    GRRLIB_FreeTexture(mage4);
    */
}

void Game::Start()
{
    screen = lobby;
    _Casters[0]->Init(_Controllers[0]);
    _Casters[1]->Init(_Controllers[1]);
    _Casters[2]->Init(_Controllers[2]);
    _Casters[3]->Init(_Controllers[3]);

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

    for (int i = 0; i < MAX_CONTROLLERS; i++)
    {
        if (_MageIdle[i] != nullptr)
        {
            GRRLIB_InitTileSet(_MageIdle[i], 64, 96, 0);
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
        }
    }

    if(screen == start)
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

                std::string noob = "_ Hold LEFT for noob mode";
                auto cnoob = noob.c_str();
                GRRLIB_PrintfTTF(150 + 1, 340 + 1, _Font, cnoob, 12, 0x000000FF);

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

        }else if(screen == arena)
        {
            
            GRRLIB_SetBackgroundColour(0xFF, 0xD7, 0x00, 0xFF);

            //GRRLIB_DrawTile(30,80, mage1Idle, 0, 1, 1, 0xFFFFFFFF, frame);
            //GRRLIB_DrawTile(395, 80, mage2, 0, 1, 1, 0xFFFFFFFF, frame);
            //GRRLIB_DrawTile(30, 275, mage3, 0, 1, 1, 0xFFFFFFFF, frame);
            //GRRLIB_DrawTile(395 , 275, mage4, 0, 1, 1, 0xFFFFFFFF, frame);
        }else if(screen == tutorial)
        {
            

        }else if(screen == lobby)
        {
            GRRLIB_SetBackgroundColour(0x37, 0x0D, 0x00, 0xFF);
            auto x = 640/4;
            auto holdPos = 30;

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
            
        }
    
    for(int i = 0; i < MAX_CONTROLLERS; i++)
    {
        if(_Casters[i] != nullptr)
        {
            _Casters[i]->Update();

            if(screen == arena)
            {
                UpdatePosition(_Casters[i],120,480-160,80,640-200,1);
                UpdateLife(_Casters[i],185+25-10,480-100+15,25,640-255,1);
                UpdateMana(_Casters[i],195+25-10,480-60-25+10,25,640-255,1);
                UpdateCombo(_Casters[i],100,480-185,110,640-170,1);
                UpdateCharging(_Casters[i],160+25-10,480-120+10,30,640-250,1);
                UpdateSpell(_Casters[i],175+25-10,480-110+15,25,640-255,1);
                UpdateTarget(_Casters[i],60,480-195-25,10,640-280,1);
            }
        }
    }

    for(int i = 0; i < MAX_CONTROLLERS; i++)
    {
        if(_Casters[i] != nullptr)
        {
            ResloveFrame(_Casters[i]);
        }
    }
    
}

void Game::ResloveFrame(Caster* caster)
{
    if(caster->IsCasting)
    {
        caster->IsCasting = false;

        for(int i = 0; i < MAX_CONTROLLERS; i++)
        {
            auto target = _Casters[i];
            if(target != nullptr)
            {
                if(target->Location == caster->Target)
                {
                    if(target->Position == caster->TargetPosition)
                    {
                        caster->Mana += caster->Charge;
                        caster->Combo++;
                        target->Combo = 0;

                        int damage = 1 + caster->Charge * caster->Combo;

                        if(target->IsCharging)
                        {
                            if(target->Spell == target->_Shield)
                            {
                                damage -= target->Charge;
                                target->Mana -= target->Charge;
                                target->Charge = 0;
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

                        target->Life -= damage;
                    }
                }
            }
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

void Game::UpdateCharging(Caster* caster, int topY, int botY, int leftX, int rightX, int offset)
{
    char str[20];
    sprintf(str, "====== %d ======", caster->IsCharging);
    UpdateProperty(caster->Location,topY,botY,leftX,rightX,offset,str);
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

