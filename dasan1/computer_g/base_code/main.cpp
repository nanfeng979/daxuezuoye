#include "InitD3dApp.h"
#include "RenderApp.h"

InitD3DApp	*pInitApp;
RenderApp	*pRenderApp;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	pRenderApp = new RenderApp(hInstance);

	pRenderApp->initApp();

	return pRenderApp->run();
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	pRenderApp->msgProc(message, wParam, lParam);
	return DefWindowProc(hwnd, message, wParam, lParam);
}