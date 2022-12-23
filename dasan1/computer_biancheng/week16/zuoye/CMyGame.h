#pragma once
#include "Game.h"

class CMyGame : public CGame
{
public:
	CMyGame(int fps = 0);
	~CMyGame(void);

	void Init();
	void Update(float fDeltaTime);

private:
	CSprite* pLeftGear;
	CSprite* pRightGear;
	CSprite* pBackground;

	CAnimationSprite* pWalker;
	BITMAP bmWalker;
	CAnimationSprite* pMonster;
	BITMAP bmMonster;

	bool bPlaying;

	enum {
		right,
		down,
		left,
		up
	} dir;

	const int STEP_walker = 10;
	const int STEP_Monster = 20;
	void HandleKeyDown(WPARAM, LPARAM);
};
