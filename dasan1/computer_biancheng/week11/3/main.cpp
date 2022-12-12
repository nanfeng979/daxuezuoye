#include "Sprite.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//CSprite* mySprite;
CSprite* Monster;
CSprite* Walker;

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

	RECT clientRT;
	GetClientRect(hwnd, &clientRT);

	HDC hdc = GetDC(hwnd);

	// monster
	HDC hdcMonster = CreateCompatibleDC(hdc);
	HBITMAP hBmMonster = (HBITMAP)LoadImage(NULL, L"Monster.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(hdcMonster, hBmMonster);
	BITMAP bmMonster;
	GetObject(hBmMonster, sizeof(BITMAP), &bmMonster);
	Monster = new CSprite(hdcMonster, 100, 100, bmMonster.bmWidth, bmMonster.bmHeight);

	// walker
	HDC hdcWalker = CreateCompatibleDC(hdc);
	HBITMAP hBmWalker = (HBITMAP)LoadImage(NULL, L"Box.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(hdcWalker, hBmWalker);
	BITMAP bmWalker;
	GetObject(hBmWalker, sizeof(BITMAP), &bmWalker);
	Walker = new CSprite(hdcWalker, 500, 100, bmWalker.bmWidth, bmWalker.bmHeight);

	// 双缓冲
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hBmMem = CreateCompatibleBitmap(hdc, clientRT.right - clientRT.left, clientRT.bottom - clientRT.top);
	SelectObject(hdcMem, hBmMem);
		
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
		if (Monster->CollideWith(*Walker)) {
			if(Monster->GetWidth() >= Walker->GetWidth() || Monster->GetHeight() >= Walker->GetHeight())
				Monster->Render(hdcMem);
			else
				Walker->Render(hdcMem);
		}
		else {
			Monster->Render(hdcMem);
			Walker->Render(hdcMem);
		}
		
		// 恢复图形模式
		SetGraphicsMode(hdcMem, GM_COMPATIBLE);
		// 输出精灵
		BitBlt(hdc, 0, 0, clientRT.right, clientRT.bottom, hdcMem, 0, 0, SRCCOPY);
	}

	DeleteObject(hBmMonster);
	DeleteObject(hBmWalker);
	DeleteDC(hdcMonster);
	DeleteDC(hdcWalker);
	ReleaseDC(hwnd, hdc);
	if (Monster) delete Monster;

	return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static float scale_x = 1.0, scale_y = 1.0;
	static float angle = 0;
	static int current_x, current_y;
	static bool isCheckedByMonster = false, isCheckedByWalker = false;

	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_LBUTTONDOWN:
		current_x = LOWORD(lParam);
		current_y = HIWORD(lParam);

		if (Monster->IsSelected(current_x, current_y))
			isCheckedByMonster = true;
		if (Walker->IsSelected(current_x, current_y))
			isCheckedByWalker = true;

		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'I': // 放大
			Monster->SetScaleFactor(scale_x += 0.3, scale_x += 0.3);
			break;
		//case 'D': // 缩小
		//	if (scale_x <= 0.5 || scale_y <= 0.5) break;
		//	Monster->SetScaleFactor(scale_x -= 0.3, scale_x -= 0.3);
		//	break;
		case 'T': // 透明
			Monster->SetTransparent(true);
			break;
		case 'O': // 不透明
			Monster->SetTransparent(false);
			break;
		case 'R': // 旋转
			angle += 30;
			Monster->SetRotationAngle(angle * PI / 180);
			break;
		
		// Monster左上右下移动
		case 'A':
			if (!isCheckedByMonster) break;
			Monster->SetPos(Monster->GetXPos() - 10, Monster->GetYPos());
			break;
		case 'W':
			if (!isCheckedByMonster) break;
			Monster->SetPos(Monster->GetXPos(), Monster->GetYPos() - 10);
			break;
		case 'D':
			if (!isCheckedByMonster) break;
			Monster->SetPos(Monster->GetXPos() + 10, Monster->GetYPos());
			break;
		case 'X':
			if (!isCheckedByMonster) break;
			Monster->SetPos(Monster->GetXPos(), Monster->GetYPos() + 10);
			break;

		// Walker左上右下移动
		case VK_LEFT:
			if (!isCheckedByWalker) break;
			Walker->SetPos(Walker->GetXPos() - 10, Walker->GetYPos());
			break;
		case VK_UP:
			if (!isCheckedByWalker) break;
			Walker->SetPos(Walker->GetXPos(), Walker->GetYPos() - 10);
			break;
		case VK_RIGHT:
			if (!isCheckedByWalker) break;
			Walker->SetPos(Walker->GetXPos() + 10, Walker->GetYPos());
			break;
		case VK_DOWN:
			if (!isCheckedByWalker) break;
			Walker->SetPos(Walker->GetXPos(), Walker->GetYPos() + 10);
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