#pragma once
#include "BaseApp.h"
#include <time.h>

class Tetris : public BaseApp
{
private:
	HANDLE mConsole, mConsoleIn;

	CHAR_INFO* mChiBuffer;
	COORD mDwBufferSize, mDwBufferCoord;
	SMALL_RECT mLpWriteRegion;

	COORD P1,P2,P3,P4;

	int Angle, NextFigure;;
	char Symbol;
	bool Flag;

public:
	const int X_SIZE, Y_SIZE;
	Tetris(int xSize = 15, int ySize = 20);
	~Tetris(void);
	virtual void UpdateF(float deltaTime);
	virtual void KeyPressed(int btnCode);
	void Move();
	void MoveL();
	void MoveR(); 
	void MoveD();
	void WinScr();
	void Turn();
	void ClrScr();
	void checkCS(COORD P);
	void RemoveSolidLine();
};
