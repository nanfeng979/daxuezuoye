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
	
	//֡����
	void FrameFunc();
	//����Windows���ڳ���
	virtual bool Run(HINSTANCE hInstance, int x = 0, int y = 0, int width = 0, int height = 0);
	//��ʼ������
	virtual void Init()=0; 
	//���ں�������
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM );

public:
	//-----������Ӧ�����ͼ����¼�����������Ϊ�麯������������Ը��ݳ�����Ҫ������д---------
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
	//�����µ��жϺ���
	bool IsKeyDown(short vk_code);
	//��̧����жϺ���
	bool IsKeyUp(int vk_code);
	

protected:

	CSpriteManager		*pSpriteManager;			//����������ָ��	
	CResourceManager	*pResManager;				//��Դ�������ָ��	


	
	virtual void Update(float fDeltaTime);			//״̬��Ϸ�޸�	
	virtual void Render();							//�������Ч��	
	void    ReadyRenderContext();
	
	HDC					hdcMem;						//�ڴ��豸����
	HBITMAP				hbMem;						//�ڴ�λͼ
	HDC					hdc;						//��ǰ�豸����
	RECT				rectClient;					//�ͻ������η�Χ

	int					nFps;						//ÿ�����֡
	int                 nFrames;					//��֡��
	int					nCalcFps;					//�����֡Ƶ
	DWORD				t0;                         //ǰһ֡��ʱ��
	float				t;							//�ۼ�����
	float				fFixedDeltaTime;			//�趨����֡���ʱ��������λ�Ǻ���
			
	HWND				hWnd;						//���ھ��

	TCHAR               szBuf[255];	
};