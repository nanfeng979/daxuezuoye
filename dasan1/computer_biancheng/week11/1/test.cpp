#include "Sprite.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

CSprite* mySprite;

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

	// 精灵
	HDC hdcSprite = CreateCompatibleDC(hdc);
	HBITMAP hBmSprite = (HBITMAP)LoadImage(NULL, L"Monster.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(hdcSprite, hBmSprite);
	BITMAP bm;
	GetObject(hBmSprite, sizeof(BITMAP), &bm);
	mySprite = new CSprite(hdcSprite, 100, 100, bm.bmWidth, bm.bmHeight);

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
		//mySprite->SetRotationAngle(45.0f);
		// 设置允许世界转换的高级图形模式
		SetGraphicsMode(hdcMem, GM_ADVANCED);
		// 写进双缓冲
		FillRect(hdcMem, &clientRT, (HBRUSH)GetStockObject(WHITE_BRUSH));
		SetStretchBltMode(hdcMem, COLORONCOLOR);
		mySprite->Render(hdcMem);
		//mySprite->SetDestRect(100, 100, bm.bmWidth, bm.bmHeight);
		SetGraphicsMode(hdc, GM_COMPATIBLE);
		// 输出精灵
		BitBlt(hdc, 100, 100, clientRT.right, clientRT.bottom, hdcMem, 0, 0, SRCCOPY);
	}

	DeleteObject(hBmSprite);
	DeleteDC(hdcSprite);
	ReleaseDC(hwnd, hdc);
	if (mySprite) delete mySprite;

	return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static float scale_x = 1.0, scale_y = 1.0;
	static int current_x, current_y;
	static bool isChecked = false;


	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_LBUTTONDOWN:
		current_x = LOWORD(lParam);
		current_y = HIWORD(lParam);
		if (mySprite->IsSelected(current_x, current_y))
			isChecked = true;
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'I': // 放大
			mySprite->SetScaleFactor(scale_x += 0.3, scale_x += 0.3);
			break;
		case 'D': // 缩小
			if (scale_x <= 0.5 || scale_y <= 0.5) break;
			mySprite->SetScaleFactor(scale_x -= 0.3, scale_x -= 0.3);
			break;
		case 'T': // 透明
			mySprite->SetTransparent(true);
			break;
		case 'O': // 不透明
			mySprite->SetTransparent(false);
			break;
		case 'R':
			mySprite->SetRotationAngle(0.5);
			//R += 5;
			break;
		// 左上右下移动
		case VK_LEFT:
			if (!isChecked) break;
			mySprite->SetPos(mySprite->GetXPos() - 10, mySprite->GetYPos());
			break;
		case VK_UP:
			if (!isChecked) break;
			mySprite->SetPos(mySprite->GetXPos(), mySprite->GetYPos() - 10);
			break;
		case VK_RIGHT:
			if (!isChecked) break;
			mySprite->SetPos(mySprite->GetXPos() + 10, mySprite->GetYPos());
			break;
		case VK_DOWN:
			if (!isChecked) break;
			mySprite->SetPos(mySprite->GetXPos(), mySprite->GetYPos() + 10);
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