#include "Controller.h"
#include <grrlib.h>

#include <stdlib.h>
#include <stdio.h>
#include <ogc/pad.h>
#include <ogc/lwp_watchdog.h>  

Controller::Controller(int port)
{
    Port = port;
}

Controller::~Controller()
{
    
}

void Controller::SetDigitalAction(DigitalInput input, void* (*action)())
{
    if (input == DigitalInput::A)
    {
        DA_A[ACount] = reinterpret_cast<void(*)()>(action);
        ACount++;
    }
    else if (input == DigitalInput::B)
    {
        DA_B[BCount] = reinterpret_cast<void(*)()>(action);
        BCount++;
    }
    else if (input == DigitalInput::Y)
    {
        DA_Y[YCount] = reinterpret_cast<void(*)()>(action);
        YCount++;
    }
    else if (input == DigitalInput::Z)
    {
        DA_Z[ZCount] = reinterpret_cast<void(*)()>(action);
        ZCount++;
    }
    else if (input == DigitalInput::UP)
    {
        DA_UP[UpCount] = reinterpret_cast<void(*)()>(action);
        UpCount++;
    }
    else if (input == DigitalInput::DOWN)
    {
        DA_DOWN[DownCount] = reinterpret_cast<void(*)()>(action);
        DownCount++;
    }
    else if (input == DigitalInput::LEFT)
    {
        DA_LEFT[LeftCount] = reinterpret_cast<void(*)()>(action);
        LeftCount++;
    }
    else if (input == DigitalInput::RIGHT)
    {
        DA_RIGHT[RightCount] = reinterpret_cast<void(*)()>(action);
        RightCount++;
    }
}


/*
void Controller::SetAnalogAction(AnalogInput input, void (*action)())
{
    if(input == AnalogInput.RT)
    {
        AA_RT[RTCount] = *action;
        RTCount++;
    }else if (input == AnalogInput.SY)
    {
        AA_SY[SYCount] = *action;
        SYCount++;
    }else if (input == AnalogInput.SX)
    {
        AA_SX[SXCount] = *action;
        SXCount++;
    }else if (input == AnalogInput.CX)
    {
        AA_CX[CXCount] = *action;
        CXCount++;
    }else if (input == AnalogInput.CY)
    {
        AA_CY[CYCount] = *action;
        CYCount++;
    }else if (input == AnalogInput.LT)
    {
        AA_LT[LTCount] = *action;
        LTCount++;
    }
}
*/

void Controller::Update()
{
    ResetPresses();
    UpdateDigitalInput();
    SY = PAD_StickY(Port);
    SX = PAD_StickX(Port);
}

void Controller::UpdateDigitalInput()
{
    if (PAD_ButtonsDown(Port) & PAD_BUTTON_A) {
        RunBuffer(DA_A, ACount);
        A_WasPressedThisFrame = true;
    }
    if (PAD_ButtonsDown(Port) & PAD_BUTTON_B) {
        RunBuffer(DA_B, BCount);
        B_WasPressedThisFrame = true;
    }
    if (PAD_ButtonsDown(Port) & PAD_BUTTON_X) {
        RunBuffer(DA_X, XCount);
        X_WasPressedThisFrame = true;
    }
    if (PAD_ButtonsDown(Port) & PAD_BUTTON_Y) {
        RunBuffer(DA_Y, YCount);
        Y_WasPressedThisFrame = true;
    }
    /*
    if (PAD_ButtonsDown(Port) & PAD_BUTTON_Z) {
        RunBuffer(DA_Z, ZCount);
        Z_WasPressedThisFrame = true;
    }
    */
    if (PAD_ButtonsDown(Port) & PAD_BUTTON_UP) {
        RunBuffer(DA_UP, UpCount);
        Up_WasPressedThisFrame = true;
    }
    if (PAD_ButtonsDown(Port) & PAD_BUTTON_DOWN) {
        RunBuffer(DA_DOWN, DownCount);
        Down_WasPressedThisFrame = true;
    }
    if (PAD_ButtonsDown(Port) & PAD_BUTTON_LEFT) {
        RunBuffer(DA_LEFT, LeftCount);
        Left_WasPressedThisFrame = true;
    }
    if (PAD_ButtonsDown(Port) & PAD_BUTTON_RIGHT) {
        RunBuffer(DA_RIGHT, RightCount);
        Right_WasPressedThisFrame = true;
    }
}

void Controller::ResetPresses()
{
    A_WasPressedThisFrame = false;
    B_WasPressedThisFrame = false;
    X_WasPressedThisFrame = false;
    Y_WasPressedThisFrame = false;
    Up_WasPressedThisFrame = false;
    Down_WasPressedThisFrame = false;
    Left_WasPressedThisFrame = false;
    Right_WasPressedThisFrame = false;
    LT_WasPressedThisFrame = false;
    RT_WasPressedThisFrame = false;
    Start_WasPressedThisFrame = false;
}

void Controller::RunBuffer(void (*buffer[])(), int size) 
{
    for(int i = 0; i < size; i++)
    {
        (*buffer[i])();
    }
}