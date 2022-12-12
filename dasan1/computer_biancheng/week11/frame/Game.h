#pragma once
#include<windows.h>
#include <tchar.h>
#include "SpriteManager.h"
#include "ResourceManager.h"

class CGame
{
public:
	CGame(int fps=0);
	virtual ~CGame(void);
	
	//帧函数
	void FrameFunc();
	//建立Windows窗口程序
	virtual bool Run(HINSTANCE hInstance, int x = 0, int y = 0, int width = 0, int height = 0);
	//初始化函数
	virtual void Init()=0; 
	//窗口函数声明
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM );

public:
	//-----处理相应的鼠标和键盘事件，这里设置为虚函数，其子类可以根据程序需要加以重写---------
	virtual void HandleLMouseUp(WPARAM wParam,LPARAM lParam){}				
	virtual void HandleLMouseDown(WPARAM wParam,LPARAM lParam){}
	virtual void HandleRMouseUp(WPARAM wParam,LPARAM lParam){}				
	virtual void HandleRMouseDown(WPARAM wParam,LPARAM lParam){}
	virtual void HandleMMouseUp(WPARAM wParam,LPARAM lParam){}				
	virtual void HandleMMouseDown(WPARAM wParam,LPARAM lParam){}
	virtual void HandleMouseMove(WPARAM wParam,LPARAM lParam){}
	virtual void HandleLDoubleClick(WPARAM wParam,LPARAM lParam){}
	virtual void HandleRDoubleClick(WPARAM wParam,LPARAM lParam){}
	virtual void HandleMDoubleClick(WPARAM wParam,LPARAM lParam){}
	virtual void HandleKeyUp(WPARAM wParam,LPARAM lParam){}
	virtual void HandleKeyDown(WPARAM wParam,LPARAM lParam){}
	//-----------------------------------------------------------------------------------------
	//键按下的判断函数
	bool IsKeyDown(short vk_code);
	//键抬起的判断函数
	bool IsKeyUp(int vk_code);
	

protected:

	CSpriteManager		*pSpriteManager;			//精灵管理对象指针	
	CResourceManager	*pResManager;				//资源管理对象指针	


	
	virtual void Update(float fDeltaTime);			//状态游戏修改	
	virtual void Render();							//输出画面效果	
	void    ReadyRenderContext();
	
	HDC					hdcMem;						//内存设备环境
	HBITMAP				hbMem;						//内存位图
	HDC					hdc;						//当前设备环境
	RECT				rectClient;					//客户区矩形范围

	int					nFps;						//每秒多少帧
	int                 nFrames;					//总帧数
	int					nCalcFps;					//计算的帧频
	DWORD				t0;                         //前一帧的时刻
	float				t;							//累计秒数
	float				fFixedDeltaTime;			//设定的两帧间的时间间隔，单位是毫秒
			
	HWND				hWnd;						//窗口句柄

	TCHAR               szBuf[255];	
};