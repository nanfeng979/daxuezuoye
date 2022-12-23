#pragma comment(lib,"msimg32.lib")
#include "CMyGame.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	CGame *p;
	p = new CMyGame(10);
	if (p)
	{
		p->Run(hInstance);
		delete p;
	}
	return 0;
}