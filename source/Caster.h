#ifndef CASTER_H
#define CASTER_H
#include "Controller.h"

class Caster
{
    private:
    void UpdateTargetPosition();
    void UpdateTarget();
    void UpdateSpell();
    void UpdatePosition();
    void Update();
    int GetDefaultTarget();
    Controller* _Controller;
    bool IsCharging;
    bool WasChargingLastFrame;
    float ChargeScaler = 0.001f;
    int _Shield = 0, _Fire = 1, _Light = 2, _Water = 3;
    public:
    int Life;
    int Mana;
    int Location;
    int Position;
    int Target;
    int TargetPosition;
    int Spell;
    int Combo;
    float Charge;
    void Init(Controller* controller);
    void SetController(Controller* controller);
    void Reset();
};

#endif