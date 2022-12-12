#include "SpriteManager.h"
#define STEP 20

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

CSpriteManager* pSpriteManager;
CResourceManager* pRes;
//CSprite* pMonster;
CSprite* pMonster[10];
CAnimationSprite* pWalkers[10];

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

	// 准备环境、后备缓冲
	RECT rt;
	GetClientRect(hwnd, &rt);
	HDC hdc = GetDC(hwnd);
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hBmMem = CreateCompatibleBitmap(hdc, rt.right - rt.left, rt.bottom - rt.top);
	SelectObject(hdcMem, hBmMem);

	// 创建资源管理类对象，加载需要的所有资源
	pRes = new CResourceManager(hwnd);
	pRes->LoadPictureFromFile(L"Monster", L"monster1.bmp");
	pRes->LoadPictureFromFile(L"Walker", L"walker1.bmp");

	// 创建精灵管理类对象
	pSpriteManager = new CSpriteManager(pRes);
	

	// 取得系统时间
	DWORD t0 = GetTickCount(), t1;

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

		// 更新客户区尺寸
		GetClientRect(hwnd, &rt);
		hBmMem = CreateCompatibleBitmap(hdc, rt.right - rt.left, rt.bottom - rt.top);
		SelectObject(hdcMem, hBmMem);
		// 取得系统时间
		t1 = GetTickCount64();
		// 设置图形模式，设置允许世界转换的高级图形模式
		SetGraphicsMode(hdcMem, GM_ADVANCED);
		// 清除背景
		FillRect(hdcMem, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH));

		// 去掉多余的像素
		SetStretchBltMode(hdcMem, COLORONCOLOR);

		// 精灵管理类更新、渲染
		pSpriteManager->Update((t1 - t0) / 1000.0f);
		pSpriteManager->Render(hdcMem);
		t0 = t1;

		// 恢复图形模式
		SetGraphicsMode(hdcMem, GM_COMPATIBLE);
		

		// 屏幕中间界的线
		for (int i = 0; i < rt.right - rt.left; i++)
		{
			SetPixel(hdcMem, i, (rt.bottom - rt.top) / 2, RGB(0, 0, 0));
		}

		// 输出精灵
		BitBlt(hdc, 0, 0, rt.right, rt.bottom, hdcMem, 0, 0, SRCCOPY);
	}


	// 清理、释放
	DeleteDC(hdcMem);
	DeleteObject(hBmMem);
	if (pSpriteManager)
		delete pSpriteManager;
	if (pRes)
		delete pRes;
	ReleaseDC(hwnd, hdc);

	

	return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	// 鼠标点击相关
	static float current_x, current_y;
	static bool isChecked;

	// 渲染精灵
	PResDesc resDes;
	BITMAP bm;

	static int monsterCount = 0;
	static int walkerCount = 0;

	RECT rt;
	GetClientRect(hwnd, &rt);

	CSprite* a;

	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_LBUTTONDOWN:
		current_x = LOWORD(lParam);
		current_y = HIWORD(lParam);

		for (int i = monsterCount - 1; i > 0; i--)
		{
			if (pMonster[i]->IsSelected(current_x, current_y))
			{
				/*auto firstMonster = pMonster[0];
				pMonster[0] = pMonster[i];
				pMonster[i] = firstMonster;*/
				//isChecked = true;
				//a = pMonster[i];
				pSpriteManager->ReZOrder(pMonster[i]);
				pMonster[i]->SetPos(pMonster[i]->GetXPos() + STEP, pMonster[i]->GetYPos());
				break;
				//PostQuitMessage(0);
			}
		}
		

		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		// 创建精灵
		case 'M':
			if (monsterCount > 9) break;

			pMonster[monsterCount] = pSpriteManager->CreateSprite(L"Monster", rand() % (rt.right - rt.left - 128), rand() % ((rt.bottom - rt.top) / 2 - 144));
			pMonster[monsterCount]->SetTransparent(true);
			monsterCount++;

			break;

		case 'W':
		case 'w':
			if (walkerCount > 9) break;

			pWalkers[walkerCount] = pSpriteManager->CreateAnimationSprite(L"Walker", 4, 5, rand() % (rt.right - rt.left - 32), (rt.bottom - rt.top) / 2 + rand() % ((rt.bottom - rt.top) / 2 - 54), 32, 54);
			pWalkers[walkerCount]->SetTransparent(true);
			pWalkers[walkerCount]->Play();
			walkerCount++;
			
			break;

			// monster左上右下移动
		case VK_LEFT:
			//pMonster->SetPos(pMonster->GetXPos() - STEP, pMonster->GetYPos());
			break;
		case VK_UP:
			//pMonster->SetPos(pMonster->GetXPos(), pMonster->GetYPos() - STEP);
			break;
		case VK_RIGHT:
			//pMonster->SetPos(pMonster->GetXPos() + STEP, pMonster->GetYPos());
			break;
		case VK_DOWN:
			//pMonster->SetPos(pMonster->GetXPos(), pMonster->GetYPos() + STEP);
			break;
		}

		// 响应按下方向键后来判断是否碰撞
		for (int i = 0; i < 10; i++)
		{
			if (!pWalkers[i]) break;
			RECT rtSprite = *(pWalkers[i]->GetBoundingBox());
			/*if (pMonster->CollideWith(rtSprite))
			{
				pSpriteManager->DeleteSprite(pWalkers[i], true);
				walkerCount--;
			}*/
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