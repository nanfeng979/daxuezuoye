#pragma comment(lib,"msimg32.lib")
#include "CMyGame.h"

CGame* pGame;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	pGame = new CMyGame(60);
	if (pGame)
	{
		pGame->Run(hInstance);
		delete pGame;
	}
	return 0;
}