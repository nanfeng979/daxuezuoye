#pragma comment(lib,"msimg32.lib")
#include "DemoGame.h"

CGame* pGame;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	pGame = new CDemoGame(60);
	if (pGame)
	{
		pGame->Run(hInstance);
		delete pGame;
	}
	return 0;
}