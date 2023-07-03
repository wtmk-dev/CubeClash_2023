#ifndef ANIMATOR_H
#define ANIMATOR_H
#include <grrlib.h>

class Animator
{
    private:
    int _CurrentFrame;
    int _FrameMax;
    GRRLib_texIMg* _Frames[];
    public:
    void SetAnimation();
    void Update();
};

#endif