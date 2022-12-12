#include "AnimationSprite.h"
#include "ResourceManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

CSprite* pMonster[10];
CAnimationSprite* pWalker[10];
CResourceManager* pRes;

// 资源变量
PResDesc resDes;
BITMAP bm;

// 对象数量
static int monsterCount = 0;
static int walkerCount = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG Msg;
	WNDCLASS wndclass;
	TCHAR lpszTitle[] = L"余庆祥设计";

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszMenuName = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = L"xiang";

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, L"注册窗口失败", L"注册窗口失败", MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(L"xiang", lpszTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	if (!hwnd)
	{
		MessageBox(NULL, L"创建窗口失败", L"创建窗口失败", MB_ICONERROR);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// 环境
	RECT clientRT;
	GetClientRect(hwnd, &clientRT);
	HDC hdc = GetDC(hwnd);

	// 资源管理类
	pRes = new CResourceManager(hwnd);
	pRes->LoadPictureFromFile(L"Monster", L"monster1.bmp");
	pRes->LoadPictureFromFile(L"Walker", L"walker1.bmp");

	// 双缓冲
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hBmMem = CreateCompatibleBitmap(hdc, clientRT.right - clientRT.left, clientRT.bottom - clientRT.top);
	SelectObject(hdcMem, hBmMem);

	// Get systemTime
	DWORD t0 = GetTickCount64(), t1;

	// 循环
	BOOL bMessage;
	PeekMessage(&Msg, NULL, 0, 0, PM_NOREMOVE);


	while (Msg.message != WM_QUIT)
	{
		bMessage = PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE);
		if (bMessage)
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}

		// 设置允许世界转换的高级图形模式
		SetGraphicsMode(hdcMem, GM_ADVANCED);
		// 写进双缓冲
		FillRect(hdcMem, &clientRT, (HBRUSH)GetStockObject(WHITE_BRUSH));
		// 去掉多余的像素
		SetStretchBltMode(hdcMem, COLORONCOLOR);

		for (int i = 0; i < monsterCount; i++)
		{
			pMonster[i]->Render(hdcMem);

		}
		t1 = GetTickCount64();
		for (int i = 0; i < walkerCount; i++)
		{
			pWalker[i]->Update((t1 - t0) / 1000.0f);
			pWalker[i]->Render(hdcMem);

		}
		t0 = t1;


		// 恢复图形模式
		SetGraphicsMode(hdcMem, GM_COMPATIBLE);
		// 输出精灵
		BitBlt(hdc, 0, 0, clientRT.right, clientRT.bottom, hdcMem, 0, 0, SRCCOPY);
	}

	for (int i = 0; i < monsterCount; i++)
	{
		if (pMonster[i]) delete pMonster[i];
	}

	for (int i = 0; i < walkerCount; i++)
	{
		if (pWalker[i]) delete pWalker[i];
	}
	
	if (pRes) delete pRes;
	ReleaseDC(hwnd, hdc);

	return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'W':
		case 'w':
			if (walkerCount > 9) break;
			resDes = pRes->GetResource(RES_BMP, L"Walker");
			GetObject((HBITMAP)resDes->dwHandle2, sizeof(BITMAP), &bm);
			pWalker[walkerCount] = new CAnimationSprite((HDC)resDes->dwHandle1, 4, 5, 120 * walkerCount, 200, bm.bmWidth / 4, bm.bmHeight / 4, 0, 0, bm.bmWidth, bm.bmHeight);
			pWalker[walkerCount]->SetTransparent(true);
			pWalker[walkerCount]->Play();
			walkerCount++;
			break;

		case 'M':
		case 'm':
			if (monsterCount > 9) break;
			resDes = pRes->GetResource(RES_BMP, L"Monster");
			GetObject((HBITMAP)resDes->dwHandle2, sizeof(BITMAP), &bm);
			pMonster[monsterCount] = new CSprite((HDC)resDes->dwHandle1, 120 * monsterCount, 10, bm.bmWidth, bm.bmHeight);
			pMonster[monsterCount]->SetTransparent(true);
			monsterCount++;
			
			break;
		}

		break;
	case WM_PAINT:

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}