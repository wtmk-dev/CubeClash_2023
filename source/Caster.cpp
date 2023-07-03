#include "Caster.h"
#include "Controller.h"

void Caster::Update()
{
    if(_Controller == nullptr)
    {
        return;
    }

    float base = 0.1;

    if (_Controller->A_WasHeldThisFrame ||
        _Controller->B_WasHeldThisFrame ||
        _Controller->Y_WasHeldThisFrame ||
        _Controller->X_WasHeldThisFrame) //is charging
    {
        IsCharging = true;
        if(Mana > 0)
        {
            Charge += base + Combo * ChargeScaler;
            Mana -= Charge * 0.01;
        }    
    }
    else if(_Controller->A_WasReleasedThisFrame ||
            _Controller->B_WasReleasedThisFrame ||
            _Controller->Y_WasReleasedThisFrame ||
            _Controller->X_WasReleasedThisFrame)
        {
            if(IsCharging)
            {
                UpdateSpell();
                IsCharging = false;
                IsCasting = true;
            }
        }

    if(!IsCharging)
    {
        UpdatePosition();
        UpdateTarget();

        if(Mana < 100)
        {
            Mana += base + Combo * ChargeScaler;
        }

        if(Charge > 0)
        {
            Charge -= 1;
        }
    }else
    {
        UpdateTargetPosition();
    }
}

void Caster::UpdateTargetPosition()
{
    if(_Controller->Left_WasHeldThisFrame)
    {
        TargetPosition = 0;
        IsCharging = false;
    }
    else
    if (_Controller->Right_WasHeldThisFrame)
    {
        TargetPosition = 2;
        IsCharging = false;
    }
    else
    if(_Controller->Up_WasHeldThisFrame)
    {
        TargetPosition = 1;
        IsCharging = false;
    }
}

void Caster::UpdateTarget()
{
    if(TargetChangeFrameDelay > 0)
    {
        TargetChangeFrameDelay--;
        return;
    }

    TargetChangeFrameDelay = 6;

    if(_Controller->LT_WasPressedThisFrame)
    {
        if(Target > 0)
        {
            Target--;

            if(Target == Location)
            {
                if(Target > 0)
                {
                    Target--;
                }else
                {
                    Target = 3;
                } 
            }
        }else
        {
            Target = 3;

            if(Target == Location)
            {
                Target = 2;
            }
        }
    }else if(_Controller->RT_WasPressedThisFrame)
    {
        if(Target < 3)
        {
            Target++;

            if(Target == Location)
            {
                if(Target < 3)
                {
                    Target++;
                }else
                {
                    Target = 0;
                } 
            }
        }else
        {
            Target = 0;

            if(Target == Location)
            {
                Target = 1;
            }
        }
    }
}

void Caster::UpdateSpell()
{
    if (_Controller->A_WasReleasedThisFrame)
    {
        Spell = _Shield;
    }
    
    if (_Controller->B_WasReleasedThisFrame)
    {
        Spell = _Light;
    }
    
    if (_Controller->Y_WasReleasedThisFrame)
    {
        Spell = _Fire;
    }
    
    if (_Controller->X_WasReleasedThisFrame)
    {
        Spell = _Water;
    }
}

void Caster::UpdatePosition()
{
    if (_Controller->Left_WasPressedThisFrame)
    {
        if (Position > 0)
        {
            Position--;
        }
    }
    else if (_Controller->Right_WasPressedThisFrame)
    {
        if (Position < 2)
        {
            Position++;
        }
    }
}

void Caster::Init(Controller* controller)
{
    _Controller = controller;

    Location = _Controller->Port;
    Position = 1;
    Target = GetDefaultTarget();

    Life = 100;
    Mana = 100;
}

int Caster::GetDefaultTarget()
{
    if(Position == 0)
    {
        return 3;
    }else if (Position == 1)
    {
        return 2;
    }else if(Position == 2)
    {
        return 0;
    }else if(Position == 3)
    {
        return 1;
    }
    
    return 0;
}

void Caster::SetController(Controller* controller)
{
    _Controller = controller;
}

void Caster::Reset()
{
    Life = 100;
    Mana = 100;

    Location = -1;         // place on screen -1 is not assigned. Set with controller.
    Position = 1;          // space on platform can be 0, 1, 2: 1 is default

    Target = -1;           // the place on screen you are trying to hit -1 is not assigned
    TargetPosition = 1;    // space on platform you are trying to hit: 1 is default

    Spell = 0;             // what spell are you casting this frame:

    Combo = 0;             // how many hits before you have been hit increase damage

    Charge = 0;            // % charged this frame.
}