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
    int GetDefaultTarget();
    Controller* _Controller;
    float ChargeScaler = 0.001f;
    int TargetChangeFrameDelay;
    public:
    int Life;
    float Mana;
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
    void Update();
    bool IsCharging;
    bool IsCasting;
    bool IsInLobby;
    bool IsLockedIn;
    int _Shield = 0, _Fire = 1, _Light = 2, _Water = 3;
    int MageSelection = 0;
};

#endif