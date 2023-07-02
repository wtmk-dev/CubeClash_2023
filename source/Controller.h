#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "K.h"

class Controller
{
	private:
	void (*DA_A[10])();
	int ACount = 0;
	void (*DA_B[10])();
	int BCount = 0;
	void (*DA_Y[10])();
	int YCount = 0;
	void (*DA_X[10])();
	int XCount = 0;
	void (*DA_Z[10])();
	int ZCount = 0;
	void (*DA_UP[10])();
	int UpCount = 0;
	void (*DA_DOWN[10])();
	int DownCount = 0;
	void (*DA_LEFT[10])();
	int LeftCount = 0;
	void (*DA_RIGHT[10])();
	int RightCount = 0;
	
	void (*AA_SX[10])();
	int SXCount = 0;
	void (*AA_SY[10])();
	int SYCount = 0;
	void (*AA_CX[10])();
	int CXCount = 0;
	void (*AA_CY[10])();
	int CYCount = 0;
	void (*AA_LT[10])();
	int LTCount = 0;
	void (*AA_RT[10])();
	int RTCount = 0;

	void ResetPresses();
	void UpdateDigitalInput();	
	void RunBuffer(void (*buffer[])(), int size);
	public:
	int Port;
	bool A_WasPressedThisFrame;
	bool B_WasPressedThisFrame;
	bool X_WasPressedThisFrame;
	bool Y_WasPressedThisFrame;
	bool Z_WasPressedThisFrame;
	bool Up_WasPressedThisFrame;
	bool Down_WasPressedThisFrame;
	bool Left_WasPressedThisFrame;
	bool Right_WasPressedThisFrame;
	bool LT_WasPressedThisFrame;
	bool RT_WasPressedThisFrame;
	bool Start_WasPressedThisFrame;

	float CX;
	float CY;
	float SX;
	float SY;

	Controller(int port);
	~Controller();

    void SetDigitalAction(DigitalInput input, void* (*action)());
	void Update();
};
#endif