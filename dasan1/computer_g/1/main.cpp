#include "RenderApp.h"

D3DApp	*pApp;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	pApp = new RenderApp(hInstance);

	pApp->initApp();

	return pApp->run();
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	pApp->msgProc(message, wParam, lParam);
	return DefWindowProc(hwnd, message, wParam, lParam);
}