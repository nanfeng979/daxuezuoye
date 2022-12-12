#pragma once
#include <windows.h>

class CMySprite
{
private:
	int x; // 位图输出位置x
	int y; // 位图输出位置y
	int w; // 位图输出宽度
	int h; // 位图输出高度
	HDC hdcSprite; // 纹理HDC
	HDC otherHDC; // 存放其它的HDC

	float scale = 1; // 缩放倍数
	bool isTransparent = false; // 是否透明



public:
	CMySprite(int x, int y, int w, int h, HDC hdc) // 构造函数
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		hdcSprite = hdc;
	}
	~CMySprite(){}; // 析构函数
	

	int GetXPos(); // 获得x轴位置
	void SetXPos(int x_pos); // 设置x轴位置
	int GetYPos(); // 获得y轴位置
	void SetYPos(int y_pos); // 设置y轴位置


	// 获取/设置Scale
	float GetScale();
	void SetScale(float scale_num);

	// 获取/设置isTransparent
	bool GetIsTransparent();
	void SetIsTransparent(bool);


	void Render(HDC hdc); // 渲染函数
};