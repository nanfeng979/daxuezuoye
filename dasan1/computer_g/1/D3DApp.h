#pragma once

#pragma comment(lib,"d3d10.lib")
#pragma comment(lib,"d3dx10.lib")

#include <D3D10.h>
#include <D3DX10.h>

#include <iostream>
#include <sstream>

#include "GameTimer.h"


LRESULT CALLBACK WndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

class D3DApp
{
public:
	D3DApp(HINSTANCE hInstance);
	virtual ~D3DApp(void);

	HINSTANCE	getAppInst();
	HWND		getMainWnd();

	int			run();

	virtual void initApp();
	virtual void onResize();
	virtual void updateScene(float dt);
	virtual void drawScene();
	virtual LRESULT msgProc(UINT msg,WPARAM wParam,LPARAM lParam);

protected:
	void	initMainWindow();
	void	initDirect3D();

protected:
	HINSTANCE	mhAppInst;
	HWND		mhMainWnd;
	bool		mAppPaused;
	bool		mMinimized;
	bool		mMaximized;
	bool		mResizing;

	
	std::wstring	mFrameStats;

	ID3D10Device*		md3dDevice;
	IDXGISwapChain*		mSwapChain;
	ID3D10Texture2D*	mDepthStencilBuffer;
	ID3D10RenderTargetView*	mRenderTargetView;
	ID3D10DepthStencilView*	mDepthStencilView;
	ID3DX10Font*			mFont;

	D3D10_DRIVER_TYPE	md3dDriverType;

	std::wstring	mMainWndCaption;

	D3DXCOLOR		mClearColor;

	GameTimer mTimer;

	int mClientWidth;
	int mClientHeight;
};

