#include "Game.h"

/*
	 CGame�Ĺ��캯��
*/
CGame::CGame(int fps)
{
	nFps=fps;		//��¼����Ҫ��������֡Ƶ
	if (fps > 0)	//���Ҫ������֡Ƶ����0�������֡��֮֡��ļ��ʱ��
	{
		fFixedDeltaTime = 1000.0f / fps;
	}
	else			//���򣬲����٣���ϵͳ����ٶ�����
	{
		fFixedDeltaTime = 0;
	}
}
CGame::~CGame(void)						//�������������ͷ���Դ
{
	if (pSpriteManager)
	{
		delete pSpriteManager;
	}
	if (pResManager)
	{
		delete pResManager;
	}
	if (hWnd && hdc)
	{
		ReleaseDC(hWnd,hdc);
	}
	if (hdcMem)
	{
		DeleteDC(hdcMem);
	}
	if (hbMem)
	{
		DeleteObject(hbMem);
	}


}

bool CGame::Run(HINSTANCE hInstance, int x, int y, int width, int height)
{
	static TCHAR szAppName[]=TEXT("Game");
	WNDCLASS wndclass;        //���崰����ṹ����
	MSG msg;                  //������Ϣ�ṹ����

	/********���崰���������*******/
	wndclass.style=CS_HREDRAW|CS_VREDRAW;       //�ı䴰�ڴ�С���ػ�
	wndclass.lpfnWndProc=CGame::WndProc;               //���ں���Ϊ  WndProc
	wndclass.cbClsExtra=0;                      //����������չ
	wndclass.cbWndExtra=0;                      //����ʵ������չ
	wndclass.hInstance=hInstance;               //ע�ᴰ�����ʵ�����
	wndclass.hIcon=LoadIcon(NULL,IDI_APPLICATION); //������Ĭ��ͼ��
	wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);   //�����ü�ͷ���
	wndclass.hbrBackground=NULL;//(HBRUSH)GetStockObject(WHITE_BRUSH); //����Ϊ��ɫ
	wndclass.lpszMenuName=NULL;                 //����Ĭ���޲˵�
	wndclass.lpszClassName=szAppName;         

	if(!RegisterClass(&wndclass)) {
		MessageBox(NULL,TEXT("ע��ʧ�ܣ�"),szAppName,MB_ICONERROR);
		return false;
	}
	//��������
	unsigned int nShow = SW_SHOW;					//������ʾ����ʽĬ��ΪSW_SHOW
	unsigned int nWindowStyle = WS_OVERLAPPEDWINDOW;//����Ĭ����ʽΪ�ص�������ʽ
	if (x == 0)
	{
		x = CW_USEDEFAULT;
	}
	if (y == 0)
	{
		y = CW_USEDEFAULT;
	}
	if (width == 0)
	{
		width = 1200;
		nShow = SW_SHOWMAXIMIZED;
		nWindowStyle = WS_POPUP;
	}
	if (height == 0)
	{
		height = 800;
		nShow = SW_SHOWMAXIMIZED;
		nWindowStyle = WS_POPUP;
	}
	hWnd = CreateWindow(szAppName,//��������
		szAppName,//����
		nWindowStyle,
		x,y,width,height,//ϵͳȱʡ������Ϳ�ȸ߶�
		NULL,//�����޸�����
		NULL,//���������˵�
		hInstance,//ʵ�����
		NULL//�޴�������
		); 
	DWORD ret = GetLastError();
	ShowWindow(hWnd,nShow);              //��ʾ����
	UpdateWindow(hWnd);                     //���´��ڵĿͻ���
	SetProp(hWnd,TEXT("GameObj"),this);
	ReadyRenderContext();	//׼����Ⱦ��������Ҫ�Ǵ���˫����
	/*
		�����괰�ں��ڽ�����Ϣѭ��֮ǰ������Init����������ض���Ϸ�ĳ�ʼ��������
		����Init����ʽ�麯�����ڶ�̬�������£��˴�����þ���ĳ�������Init������
		�����Դ���صȳ�ʼ���Ĺ�����
	*/
	Init();	
	t0 = GetTickCount();//��¼��ǰʱ�̵�
	t = 0;
	nFrames = 0;
	nCalcFps = 0;
	msg.message   =   WM_NULL;   
	BOOL  bMessage;
	PeekMessage(&msg, NULL, 0, 0,PM_NOREMOVE);
	while(msg.message != WM_QUIT)	//������Ϣѭ��
	{
		bMessage = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		if(bMessage)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if(IsKeyDown(VK_ESCAPE))
			DestroyWindow(hWnd);
		FrameFunc();												//��Ϣѭ���е�ûһ֡������֡����������Ϸ����
	} 
	RemoveProp(hWnd,TEXT("GameObj"));
	return true;
}
void CGame::ReadyRenderContext()
{
	hdc = GetDC(hWnd);	//�õ��豸����
	
	GetClientRect(hWnd,&rectClient);								//�õ��ͻ�������
	//���洴���󱸻���
	hdcMem = CreateCompatibleDC(hdc);
	hbMem = CreateCompatibleBitmap(hdc,rectClient.right-rectClient.left,rectClient.bottom-rectClient.top);
	SelectObject(hdcMem,hbMem);
	SetGraphicsMode(hdcMem, GM_ADVANCED);
	SetStretchBltMode(hdcMem, COLORONCOLOR);
	pResManager =  new CResourceManager(hWnd);						//������Դ�������
	pSpriteManager = new CSpriteManager(pResManager);				//��������������

}


/***************************************************************************
	֡����������ϵͳ���ŵ�ʱ����¾���״̬��������������д��Ϸ����
***************************************************************************/
void CGame::FrameFunc()
{
	DWORD dt = 0;

	do 
	{ 
		dt=GetTickCount() - t0; 
	} while(dt < 1);									//��֤��С���ʱ����ڵ���1����
	if (dt >= fFixedDeltaTime)							//������ڹ̶��ļ��ʱ��
	{
		t0 = GetTickCount();								//��¼��֡���õ�ʱ��
		Update(dt / 1000.0);							//����֡��������
		t += dt / 1000.0;
		Render();										//��Ⱦ

		nFrames++;
	}
	else
	{
		Sleep(1);										//��������1��
	}
}
/***************************************************************************
	���º�����֪ͨSpriteManager��������ÿ�������������
***************************************************************************/
void CGame::Update(float fDeltaTime)
{
	if (pSpriteManager)
	{
		pSpriteManager->Update(fDeltaTime);	
	}
}
/***************************************************************************
	��Ⱦ������֪ͨSpriteManager��������ÿ��������Ⱦ����
	ÿ�������ǽ�������Ⱦ���󱸻�����ģ������о������������������Ⱦ��
	�ú������󱸻��������BitBlt����Ļ�ϣ������ʾ��
***************************************************************************/
void CGame::Render()
{
	FillRect(hdcMem,&rectClient,(HBRUSH)GetStockObject(BLACK_BRUSH));
	if (pSpriteManager)
	{
		pSpriteManager->Render(hdcMem);
	}
	if (t >= 1)
	{
		nCalcFps  =  nFrames / t;

		t = 0;
		nFrames = 0;
	}
	wsprintf(szBuf,TEXT("%d"),nCalcFps);
	TextOut(hdcMem,10,10,szBuf,wcslen(szBuf));

	BitBlt(hdc,0,0,rectClient.right - rectClient.left,rectClient.bottom - rectClient.top,hdcMem,0,0,SRCCOPY);
	
}
bool CGame::IsKeyDown(short vk_code)
{
	return (GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0;
}

bool CGame::IsKeyUp(int vk_code)
{
	static int keyBuf[256] = {0};
	short key = GetAsyncKeyState(vk_code); 
	int curKeyFlag = (key & 0x8000) ? 1:0;
	if (keyBuf[vk_code] == 1 && curKeyFlag == 0){
		keyBuf[vk_code] = 0;
		return true;
	}
	keyBuf[vk_code] = curKeyFlag;
	return 0;
}


//���ں���
LRESULT CALLBACK CGame::WndProc(HWND hwnd,UINT message,WPARAM wParam, LPARAM lParam)
{
	CGame *pGame =(CGame*)GetProp(hwnd,TEXT("GameObj"));

	switch(message)                  //������Ϣֵת��Ӧ����Ϣ����
	{
	case  WM_DESTROY:                //����������Ϣ
		PostQuitMessage(0);          //�����˳�������ϢWM_QUIT
		return 0;
	case WM_LBUTTONDOWN:
		if (pGame)
			pGame->HandleLMouseDown(wParam,lParam);
		return 0;
	case WM_LBUTTONUP:
		if (pGame)
			pGame->HandleLMouseUp(wParam,lParam);
		return 0;
	case WM_LBUTTONDBLCLK:
		if (pGame)
			pGame->HandleLDoubleClick(wParam,lParam);
		return 0;
	case WM_MOUSEMOVE:
		if (pGame)
			pGame->HandleMouseMove(wParam,lParam);
		return 0;
	case WM_RBUTTONDOWN:
		if (pGame)
			pGame->HandleRMouseDown(wParam,lParam);
		return 0;
	case WM_RBUTTONUP:
		if (pGame)
			pGame->HandleRMouseUp(wParam,lParam);
		return 0;
	case WM_RBUTTONDBLCLK:
		if (pGame)
			pGame->HandleRDoubleClick(wParam,lParam);
		return 0;
	case WM_MBUTTONDOWN:
		if (pGame)
			pGame->HandleMMouseDown(wParam,lParam);
		return 0;
	case WM_MBUTTONUP:
		if (pGame)
			pGame->HandleMMouseUp(wParam,lParam);
		return 0;
	case WM_MBUTTONDBLCLK:
		if (pGame)
			pGame->HandleMDoubleClick(wParam,lParam);
		return 0;
	case WM_KEYDOWN:
		if (pGame)
			pGame->HandleKeyDown(wParam,lParam);
		return 0;
	case WM_KEYUP:
		if (pGame)
			pGame->HandleKeyUp(wParam,lParam);
		return 0;
	}
	return DefWindowProc(hwnd,message,wParam,lParam);//����תĬ�ϴ��ں���
}
