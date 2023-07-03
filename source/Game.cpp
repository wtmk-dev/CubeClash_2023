#include "Game.h"
#include "Caster.h"
#include <grrlib.h>
#include <stdlib.h>
#include <stdio.h>

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

}

void Game::Start()
{
    _Casters[0]->Init(_Controllers[0]);
    _Casters[1]->Init(_Controllers[1]);
    _Casters[2]->Init(_Controllers[2]);
    _Casters[3]->Init(_Controllers[3]);
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
    
    for(int i = 0; i < MAX_CONTROLLERS; i++)
    {
        if(_Casters[i] != nullptr)
        {
            _Casters[i]->Update();
            UpdatePosition(_Casters[i],120,480-160,80,640-200,1);
            UpdateLife(_Casters[i],185+25-10,480-100+15,25,640-255,1);
            UpdateMana(_Casters[i],195+25-10,480-60-25+10,25,640-255,1);
            UpdateCombo(_Casters[i],100,480-185,110,640-170,1);
            UpdateCharging(_Casters[i],160+25-10,480-120+10,30,640-250,1);
            UpdateSpell(_Casters[i],175+25-10,480-110+15,25,640-255,1);
            UpdateTarget(_Casters[i],60,480-195-25,10,640-280,1);
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

