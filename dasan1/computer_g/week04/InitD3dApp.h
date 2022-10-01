#pragma once
#include "D3DApp.h"
class InitD3DApp :
	public D3DApp
{
public:
	InitD3DApp(HINSTANCE hInstance);
	~InitD3DApp();

	void drawScene();
};

