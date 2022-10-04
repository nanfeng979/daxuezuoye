#include <Windows.h>

typedef struct {
	float x;
	float y;
} objCenterXY;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
VOID PAINT(HWND hwnd, HDC hdc); // 声明绘画函数
void drawCircular(HDC hdc, objCenterXY obj_center, float obj_radius); // 声明绘制圆形函数
void drawCircularArc(HDC hdc, const objCenterXY obj_center, float obj_radius); //  声明绘制圆形边框函数

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
	wndclass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
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

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

#define init_x 50 // 全局的初始的x轴位置
#define init_y 50 // 全局的初始的y轴位置
#define diameter 200 // 全局的一个直径参考
#define line_width 1 // 画笔样式的默认宽度
#define object_spacing 100 // 两个对象之间的间隙

HDC hdc;
HPEN hOldPen; // 初始时的画笔样式
HPEN hPen1 = CreatePen(PS_NULL, line_width, RGB(255, 255, 255)); // 画笔样式为：无边
HPEN hPen2 = CreatePen(PS_SOLID, line_width, RGB(0, 0, 0)); // 画笔样式为：实线1宽度黑色
HBRUSH hOldBrush; // 初始时的笔刷样式
HBRUSH hBrush1 = CreateSolidBrush(RGB(255, 255, 255)); // 笔刷样式为：白色实心笔刷
HBRUSH hBrush2 = CreateSolidBrush(RGB(0, 0, 0)); // 笔刷样式为：黑色实心笔刷


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
		hdc = GetDC(hwnd); // 获取设备环境
		PAINT(hwnd, hdc); // 绘制
		ReleaseDC(hwnd, hdc); // 释放设备环境
		break;
	case WM_DESTROY:
		DeleteObject(hPen1); // 删除画笔样式hPen1
		DeleteObject(hPen2); // 删除画笔样式hPen2
		DeleteObject(hBrush1); // 删除笔刷样式hBrush1
		DeleteObject(hBrush2); // 删除笔刷样式hBrush2

		SelectObject(hdc, hOldPen); // 恢复初始时的画笔样式
		SelectObject(hdc, hOldBrush); // 恢复初始时的笔刷样式

		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

VOID PAINT(HWND hwnd, HDC hdc)
{
	// 绘制两仪
	#define Liangyi_init_x init_x // 两仪初始的x轴位置
	#define Liangyi_init_y init_y // 两仪初始的y轴位置
	#define Liangyi_radius diameter / 2 // 两仪半径
	#define Liangyi_small_radius Liangyi_radius / 2 // 小两仪的半径
	#define Liangyi_eye_radius 10 // 两仪的小圆半径

	objCenterXY liangyi = {
		Liangyi_init_x + Liangyi_radius,
		Liangyi_init_y + Liangyi_radius,
	}; // 定义两仪的中心位置
	objCenterXY liangyi_up_cir = {
		liangyi.x,
		Liangyi_init_y + Liangyi_radius / 2,
	}; // 定义两仪的上半圆中心位置
	objCenterXY liangyi_down_cir = {
		liangyi.x,
		Liangyi_init_y + Liangyi_radius + Liangyi_radius / 2,
	}; // 定义两仪的下半圆中心位置

	hOldPen = (HPEN)SelectObject(hdc, hPen2); // 保存初始时的画笔样式，并设置画笔为hPen2样式
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush1); // 保存初始时的笔刷样式，并设置笔刷为hBrush1样式
	Pie(hdc, liangyi.x - Liangyi_radius, liangyi.y - Liangyi_radius,
		liangyi.x + Liangyi_radius, liangyi.y + Liangyi_radius,
		liangyi.x, liangyi.y - Liangyi_radius,
		liangyi.x, liangyi.y + Liangyi_radius); // 绘制两仪的左半圆

	SelectObject(hdc, hBrush2); // 设置笔刷为hBrush2样式
	Pie(hdc, liangyi_up_cir.x - Liangyi_small_radius, liangyi_up_cir.y - Liangyi_small_radius,
		liangyi_up_cir.x + Liangyi_small_radius, liangyi_up_cir.y + Liangyi_small_radius,
		liangyi_up_cir.x, liangyi_up_cir.y - Liangyi_small_radius,
		liangyi_up_cir.x, liangyi_up_cir.y + Liangyi_small_radius); // 绘制两仪的上左半圆
	Pie(hdc, liangyi.x - Liangyi_radius, liangyi.y - Liangyi_radius,
		liangyi.x + Liangyi_radius, liangyi.y + Liangyi_radius,
		liangyi.x, liangyi.y + Liangyi_radius,
		liangyi.x, liangyi.y - Liangyi_radius); // 绘制两仪的右半圆

	SelectObject(hdc, hPen1); // 设置画笔为hPen1样式
	SelectObject(hdc, hBrush1); // 设置笔刷为hBrush1样式
	Pie(hdc, liangyi_down_cir.x - Liangyi_small_radius, liangyi_down_cir.y - Liangyi_small_radius,
		liangyi_down_cir.x + Liangyi_small_radius, liangyi_down_cir.y + Liangyi_small_radius,
		liangyi_down_cir.x, liangyi_down_cir.y + Liangyi_small_radius,
		liangyi_down_cir.x, liangyi_down_cir.y - Liangyi_small_radius); // 绘制两仪的下右半圆
	drawCircular(hdc, liangyi_up_cir, Liangyi_eye_radius); // 绘制上半圆的白色小圆

	SelectObject(hdc, hBrush2); // 设置笔刷为hBrush2样式
	drawCircular(hdc, liangyi_down_cir, Liangyi_eye_radius); // 绘制下半圆的黑色小圆


	// 绘制熊猫
	#define panda_init_x Liangyi_init_x + diameter + object_spacing // 熊猫初始的x轴位置
	#define panda_init_y init_y // 熊猫初始的y轴位置
	#define panda_ear_radius 30 // 熊猫的耳朵的半径
	#define panda_Scale_factor 0.6 // 熊猫的脸与耳朵的比例系数
	#define panda_face_radius 80 // 熊猫的脸的半径
	#define panda_eye_distance_hafe 10 // 熊猫的一半眼距
	#define panda_eye_radius 20 // 熊猫的眼睛的半径
	#define panda_mouth_width 15 // 熊猫的嘴巴宽度
	#define panda_mouth_height 6 // 熊猫的嘴巴高度
	#define panda_eyeball_radius 6 // 熊猫眼球的半径
	#define panda_eyeball_to_eyeball_distance 7 // 熊猫眼球中心与眼睛中心的位置

	objCenterXY panda_left_ear = {
		panda_init_x + panda_ear_radius,
		panda_init_y + panda_ear_radius,
	}; // 定义熊猫的左耳中心位置
	objCenterXY panda_right_ear = {
		panda_init_x + (panda_face_radius) * 2 - panda_ear_radius,
		panda_init_y + panda_ear_radius,
	}; // 定义熊猫的右耳中心位置
	objCenterXY pandan_face = {
		panda_init_x + panda_face_radius,
		panda_left_ear.y + panda_face_radius - 10,
	}; // 定义熊猫的脸中心位置
	objCenterXY panda_left_eye = {
		pandan_face.x - panda_eye_distance_hafe - panda_eye_radius,
		pandan_face.y - panda_eye_radius + 14,
	}; // 定义熊猫的左眼中心位置
	objCenterXY panda_right_eye = {
		pandan_face.x + panda_eye_distance_hafe + panda_eye_radius,
		pandan_face.y - panda_eye_radius + 14,
	}; // 定义熊猫的右眼中心位置
	objCenterXY panda_mouth = {
		pandan_face.x,
		pandan_face.y + 40,
	}; // 定义熊猫的嘴巴中心位置
	objCenterXY panda_left_eyeball = {
		panda_left_eye.x + panda_eyeball_to_eyeball_distance,
		panda_left_eye.y - panda_eyeball_to_eyeball_distance,
	}; // 定义熊猫的左眼球中心位置
	objCenterXY panda_right_eyeball = {
		panda_right_eye.x - panda_eyeball_to_eyeball_distance,
		panda_right_eye.y - panda_eyeball_to_eyeball_distance,
	}; // 定义熊猫的右眼球中心位置

	drawCircular(hdc, panda_left_ear, panda_ear_radius); // 绘制熊猫的左耳
	drawCircular(hdc, panda_right_ear, panda_ear_radius); // 绘制熊猫的右耳

	SelectObject(hdc, hBrush1); // 设置笔刷为hBrush1样式
	drawCircular(hdc, pandan_face, panda_face_radius); // 绘制熊猫脸

	SelectObject(hdc, hPen2); // 设置画笔为hPen2样式
	drawCircularArc(hdc, pandan_face, panda_face_radius); // 绘制熊猫脸的边缘

	SelectObject(hdc, hBrush2); // 设置笔刷为hBrush2样式
	drawCircular(hdc, panda_left_eye, panda_eye_radius); // 绘制熊猫的左眼
	drawCircular(hdc, panda_right_eye, panda_eye_radius); // 绘制熊猫的右眼
	Pie(hdc, panda_mouth.x - panda_mouth_width,
		panda_mouth.y - panda_mouth_height,
		panda_mouth.x + panda_mouth_width,
		panda_mouth.y + panda_mouth_height,
		0, 0, 0, 0); // 绘制熊猫的嘴巴

	SelectObject(hdc, hPen1); // 设置画笔为hPen1样式
	SelectObject(hdc, hBrush1); // 设置笔刷为hBrush1样式
	drawCircular(hdc, panda_left_eyeball, panda_eyeball_radius); // 绘制熊猫的左眼球
	drawCircular(hdc, panda_right_eyeball, panda_eyeball_radius); // 绘制熊猫的右眼球


	// 绘制树
	#define height_disparity 15 // 树之间的高度差
	#define Tree1_init_y init_y + height_disparity * 3 // 树1初始的y轴位置
	#define Tree1_height 80 // 树1的高度
	#define Tree2_init_y Tree1_init_y - height_disparity // 树2初始的y轴位置
	#define Tree2_height Tree1_height - height_disparity // 树2的高度
	#define Tree3_init_y Tree2_init_y - height_disparity // 树3初始的y轴位置
	#define Tree3_height Tree2_height - height_disparity // 树3的高度
	#define Tree4_init_y Tree3_init_y - height_disparity // 树4初始的y轴位置
	#define Tree4_height Tree3_height - height_disparity // 树4的高度
	#define Tree_init_x panda_init_x + diameter + object_spacing + Tree1_height / 2 // 树初始的x轴位置
	#define Trunk_init_y Tree1_init_y + Tree1_height // 树干初始的y轴位置
	#define Trunk_width_half 10 // 树干的一半宽度
	#define Trunk_height 40 // 树干的高度

	SelectObject(hdc, hPen2); // 设置画笔为hPen2样式
	POINT lpPt1[3] = { Tree_init_x - (Tree1_height), Tree1_init_y + Tree1_height,
					Tree_init_x , Tree1_init_y,
					Tree_init_x + Tree1_height, Tree1_init_y + Tree1_height }; // 定义第一丛树的三个点坐标
	Polygon(hdc, lpPt1, 3); // 绘制第一丛树，从下往上数
	POINT lpPt2[3] = { Tree_init_x - (Tree2_height), Tree2_init_y + Tree2_height,
					Tree_init_x , Tree2_init_y,
					Tree_init_x + Tree2_height, Tree2_init_y + Tree2_height }; // 定义第二丛树的三个点坐标
	Polygon(hdc, lpPt2, 3); // 绘制第二丛树
	POINT lpPt3[3] = { Tree_init_x - (Tree3_height), Tree3_init_y + Tree3_height,
					Tree_init_x , Tree3_init_y,
					Tree_init_x + Tree3_height, Tree3_init_y + Tree3_height }; // 定义第三丛树的三个点坐标
	Polygon(hdc, lpPt3, 3); // 绘制第三丛树
	POINT lpPt4[3] = { Tree_init_x - (Tree4_height), Tree4_init_y + Tree4_height,
					Tree_init_x , Tree4_init_y,
					Tree_init_x + Tree4_height, Tree4_init_y + Tree4_height }; // 定义第四丛树的三个点坐标
	Polygon(hdc, lpPt4, 3); // 绘制第四丛树
	Rectangle(hdc, Tree_init_x - Trunk_width_half, Trunk_init_y,
		Tree_init_x + Trunk_width_half, Trunk_init_y + Trunk_height); // 绘制树干
}

void drawCircular(HDC hdc, const objCenterXY obj_center, float obj_radius)
{
	Pie(hdc, obj_center.x - obj_radius,
		obj_center.y - obj_radius,
		obj_center.x + obj_radius,
		obj_center.y + obj_radius,
		0, 0, 0, 0);
}

void drawCircularArc(HDC hdc, const objCenterXY obj_center, float obj_radius)
{
	Arc(hdc, obj_center.x - obj_radius,
		obj_center.y - obj_radius,
		obj_center.x + obj_radius,
		obj_center.y + obj_radius,
		0, 0, 0, 0);
}