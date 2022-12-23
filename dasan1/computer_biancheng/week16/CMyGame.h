#pragma once
#include "Game.h"

class CMyGame:public CGame
{
public:
	CMyGame(int fps=0);
	~CMyGame(void);
public:
	void Init();
	void Update(float fDeltaTime);
private:
	CSprite *pLeftGear;
	CSprite *pRightGear;
	CSprite *pBackground;
	bool bPlaying;//提供接口
};

