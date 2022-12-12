#include "CMySprite.h"
#pragma comment(lib,"msimg32.lib")

// 渲染
void CMySprite::Render(HDC hdc)
{
	// TODO: 输出位置需要随着方向键的改变而改变
	if (GetIsTransparent())
	{
		// 透明渲染
		TransparentBlt(hdc, x, y, w * GetScale(), h * GetScale(),
			hdcSprite, 0, 0, w, h, GetPixel(hdcSprite, 0, 0));
		return;
	}
	// 不透明渲染
	StretchBlt(hdc, x, y, w * GetScale(), h * GetScale(), hdcSprite, 0, 0, w, h, SRCCOPY);
}


// 获取/设置XY轴
int CMySprite::GetXPos()
{
	return x;
}

void CMySprite::SetXPos(int x_pos)
{
	x = x_pos;
}

int CMySprite::GetYPos()
{
	return y;
}

void CMySprite::SetYPos(int y_pos)
{
	y = y_pos;
}


// 获取/设置Scale
float CMySprite::GetScale()
{
	return scale;
}

void CMySprite::SetScale(float scale_num)
{
	scale = scale_num;
}


// 获取/设置isTransparent
bool CMySprite::GetIsTransparent()
{
	return isTransparent;
}

void CMySprite::SetIsTransparent(bool b)
{
	isTransparent = b;
}