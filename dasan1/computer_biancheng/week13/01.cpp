#include "AnimationSprite.h"
#include "ResourceManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

CSprite* pMonster;
CAnimationSprite* pWalker;
CResourceManager* pRes;

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

	// 资源变量
	PResDesc resDes;
	BITMAP bm;

	// monster
	resDes = pRes->GetResource(RES_BMP, L"Monster");
	GetObject((HBITMAP)resDes->dwHandle2, sizeof(BITMAP), &bm);
	pMonster = new CSprite((HDC)resDes->dwHandle1, 10, 10, bm.bmWidth, bm.bmHeight);
	pMonster->SetTransparent(true);

	// walker
	resDes = pRes->GetResource(RES_BMP, L"Walker");
	GetObject((HBITMAP)resDes->dwHandle2, sizeof(BITMAP), &bm);
	pWalker = new CAnimationSprite((HDC)resDes->dwHandle1, 4, 5, 200, 100, bm.bmWidth / 4, bm.bmHeight / 4, 0, 0, bm.bmWidth, bm.bmHeight);
	pWalker->SetTransparent(true);
	pWalker->Play();


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

		pMonster->Render(hdcMem);

		t1 = GetTickCount64();
		pWalker->Update((t1 - t0) / 1000.0f);
		t0 = t1;
		pWalker->Render(hdcMem);

		// 恢复图形模式
		SetGraphicsMode(hdcMem, GM_COMPATIBLE);
		// 输出精灵
		BitBlt(hdc, 0, 0, clientRT.right, clientRT.bottom, hdcMem, 0, 0, SRCCOPY);
	}


	if (pMonster) delete pMonster;
	if (pWalker) delete pWalker;
	if (pRes) delete pRes;
	ReleaseDC(hwnd, hdc);

	return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static float angle = 0;
	static float scale_x = 1, scale_y = 1;
	static float monster_sx = 1, monster_sy = 1;

	switch (message)
	{
	case WM_CREATE:
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
			// monster左上右下移动
		case VK_LEFT:
			pMonster->SetPos(pMonster->GetXPos() - 10, pMonster->GetYPos());
			break;
		case VK_UP:
			pMonster->SetPos(pMonster->GetXPos(), pMonster->GetYPos() - 10);
			break;
		case VK_RIGHT:
			pMonster->SetPos(pMonster->GetXPos() + 10, pMonster->GetYPos());
			break;
		case VK_DOWN:
			pMonster->SetPos(pMonster->GetXPos(), pMonster->GetYPos() + 10);
			break;

			// walker左上右下移动
		case 'A':
		case 'a':
			pWalker->SetPos(pWalker->GetXPos() - 10, pWalker->GetYPos());
			pWalker->SetTextureStartPos(0, pWalker->GetHeight() * 1);
			break;
		case 'W':
		case 'w':
			pWalker->SetPos(pWalker->GetXPos(), pWalker->GetYPos() - 10);
			pWalker->SetTextureStartPos(0, pWalker->GetHeight() * 3);
			break;
		case 'D':
		case 'd':
			pWalker->SetPos(pWalker->GetXPos() + 10, pWalker->GetYPos());
			pWalker->SetTextureStartPos(0, pWalker->GetHeight() * 2);
			break;
		case 'X':
		case 'x':
			pWalker->SetPos(pWalker->GetXPos(), pWalker->GetYPos() + 10);
			pWalker->SetTextureStartPos(0, pWalker->GetHeight() * 0);
			break;

		case 'S': // 停止
		case 's':
			pWalker->Stop();
			break;
		case 'P': // 播放
		case 'p':
			pWalker->Resume();
			break;

		case 'R': // 旋转
		case 'r':
			angle += 30;
			pWalker->SetRotationAngle(angle * PI / 180);
			break;
		case 'I': // 放大
		case 'i':
			pWalker->SetScaleFactor(scale_x += 0.3, scale_x += 0.3);
			break;
		case 'F': // 缩小
		case 'f':
			if (scale_x <= 0.5 || scale_y <= 0.5) break;
			pWalker->SetScaleFactor(scale_x -= 0.3, scale_x -= 0.3);
			break;
		case 'Z': // monster放大
		case 'z':
			pMonster->SetScaleFactor(monster_sx += 0.3, monster_sx += 0.3);
			break;
		case 'C': // monster缩小
		case 'c':
			if (monster_sx <= 0.5 || monster_sy <= 0.5) break;
			pMonster->SetScaleFactor(monster_sx -= 0.3, monster_sx -= 0.3);
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