#include "Caster.h"
#include "Controller.h"

void Caster::Update()
{
    IsCharging = false;

    if (_Controller->A_WasPressedThisFrame ||
        _Controller->B_WasPressedThisFrame ||
        _Controller->Y_WasPressedThisFrame ||
        _Controller->X_WasPressedThisFrame) //is charging
    {
        IsCharging = true;
        if (WasChargingLastFrame)
        {
            int base = 1;
            Charge += base + Combo * ChargeScaler;
        }

        WasChargingLastFrame = true;
    }
    else
    {
        if (WasChargingLastFrame)
        {
            UpdateSpell();
            UpdateTarget();
            UpdateTargetPosition();
        }
        else
        {
            UpdatePosition();
        }

        WasChargingLastFrame = false;
    }
}

void Caster::UpdateTargetPosition()
{
    if(_Controller->Left_WasPressedThisFrame)
    {
        TargetPosition = 0;
    }else if (_Controller->Right_WasPressedThisFrame)
    {
        TargetPosition = 2;
    }else
    {
        TargetPosition = 1;
    }
    
}

void Caster::UpdateTarget()
{
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
    }else if(_Controller->LT_WasPressedThisFrame)
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
    if (_Controller->A_WasPressedThisFrame)
    {
        Spell = _Shield;
    }
    else if (_Controller->B_WasPressedThisFrame)
    {
        Spell = _Light;
    }
    else if (_Controller->Y_WasPressedThisFrame)
    {
        Spell = _Fire;
    }
    else if (_Controller->X_WasPressedThisFrame)
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

    Spell = 0;             // what spell are you casting this frame: 0 shield, 1 fire, 2 water, 3 lighting

    Combo = 0;             // how many hits before you have been hit increase damage

    Charge = 0;            // % charged this frame.
}
