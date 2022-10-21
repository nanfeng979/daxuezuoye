#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// 全局变量
int n = 3; // 初始化控制位图大小倍率的变量
HDC hdc, hdcMem;
HBITMAP hBitmap;
BITMAP bm;
HPEN hPen, hOldPen;

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

	hdc = GetDC(hwnd); // 获取·整个屏幕·的工作区的设备句柄
	hdcMem = CreateCompatibleDC(hdc); // 创建与指定设备兼容的·内存·设备句柄
	hBitmap = (HBITMAP)LoadImage(NULL, L"Monster.bmp", IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE);
	SelectObject(hdcMem, hBitmap); // 选中指定位图到·内存设备·
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255)); // 控制输出的矩形的边框为白色(此处为背景色，更好的写法是捕获背景色)
	hOldPen = (HPEN)SelectObject(hdc, hPen);

	GetObject(hBitmap, sizeof(BITMAP), &bm);
	SetStretchBltMode(hdc, COLORONCOLOR);

	while (GetMessage(&Msg, NULL, 0, 0))
	{

		StretchBlt(hdc, 50, 50, bm.bmWidth * n, bm.bmHeight * n, hdcMem,
			0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY); // 输出位图，实际大小由n决定

		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN: // 接收鼠标左键按下消息
		if (n == 5) return 0;
		//Rectangle(hdc, 50, 50, bm.bmWidth * n + 50 + 1, bm.bmHeight * n + 50 + 1);
		n++; // 增大控制位图大小倍率的变量
		break;
	case WM_KEYDOWN: // 接收任意键盘按键消息
		if (n == 1) return 0;
		Rectangle(hdc, 50, 50, bm.bmWidth * n + 50, bm.bmHeight * n + 50); // 输出白色矩形用来清除由大变小时未被覆盖的区域
		n--; // 减小控制位图大小倍率的变量
		break;
	case WM_PAINT:
		break;
	case WM_DESTROY:
		// 清理缓存，恢复默认环境
		DeleteDC(hdcMem);
		DeleteObject(hBitmap);
		DeleteObject(hPen);
		SelectObject(hdc, hOldPen);
		ReleaseDC(hwnd, hdc);

		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

// 运行程序时，系统发送WM_CREATE消息，被GetMessage接收，输出初始时的位图；
// 每次鼠标左键点击或者键盘按下时，被 WndProc 的 switch 的 WM_LBUTTONDOWN or WM_KEYDOWN 接收，
// 如果没有对应的case则不会接收，接收到后会发送消息给GetMessage，使得里面的 StretchBlt 函数执行，
// 根据鼠标左键点击或者键盘按下的不同而改变的n值，输出不一样大小的位图。