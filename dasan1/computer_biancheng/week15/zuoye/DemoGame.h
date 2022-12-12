#include "Game.h"
#define STEP 10

enum Dir {
	right,
	left,
	up,
	down
};

class CDemoGame : public CGame
{
public:
	CDemoGame(int nFps = 0);
	~CDemoGame(void);
	void Init();

private:
	CSprite* pBackGround, *pBox, *pApple; // ±³¾°¡¢Ïä×Ó¡¢Æ»¹û
	CAnimationSprite* pMonster, *pPlayer; // ¹ÖÊÞ¡¢Íæ¼Ò
	
	void HandleKeyDown(WPARAM, LPARAM);
	void Update(float);
	RECT rt;
	Dir dir;
};