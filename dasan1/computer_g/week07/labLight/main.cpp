#include "InitD3dApp.h"
#include "LightApp.h"

InitD3DApp	*pInitApp;
LightApp *pRenderApp;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	pRenderApp = new LightApp(hInstance);

	pRenderApp->initApp();

	return pRenderApp->run();
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	pRenderApp->msgProc(message, wParam, lParam);
	return DefWindowProc(hwnd, message, wParam, lParam);
}