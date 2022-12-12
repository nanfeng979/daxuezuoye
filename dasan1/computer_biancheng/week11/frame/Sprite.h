#pragma once
#pragma comment(lib, "msimg32.lib")
/*******************************************************************************
   代码6-1	建立精灵类,用于管理精灵自身的行为,包括将图片渲染到指定的DC的指定地方,
	渲染时可以进行拉伸和透明渲染。并且能检查是否与其它精灵碰撞

********************************************************************************/
#include <windows.h>
#include <math.h>
#define PI 3.1415926
class CSprite
{
public:
	CSprite(									//带参构造
			HDC hdcSprite,						//精灵纹理图像的HDC
			int x,								//精灵创建时的位置
			int y,
			int w,								//精灵的宽度
			int h								//精灵的高度
		);			
	virtual ~CSprite(void);								//析构
protected:
	HDC		hdcSprite;									//精灵所指向的图片资源
	HDC     hdcDest;									//目的DC
	int     tx;											//源图x
	int     ty;											//源图y
	int     width;										//精灵宽度
	int     height;										//精灵高度			
	DWORD   dwColorKey;									//关键色
	POINT   ptHotSpot;									//热点
	int     nZOrder;									//Z-Order
	bool    bTransparent;								//是否透明渲染
	bool	bVisible;									//是否可见
	RECT	rtBoundingBox;								//包围盒
	XFORM	translation;								//平移矩阵
	XFORM   rotation;									//旋转矩阵
	XFORM	scale;										//缩放矩阵
	XFORM	world;										//世界变换矩阵
	void	InitXFORM(XFORM &form);						//设置单位阵
	void    CalcBoundingBox();							//计算包围盒
public:
	//void Draw();										//渲染		
	virtual void Render(HDC hdcDest);					//根据设置的x,y渲染到目的DC
	//void Draw(int x,int y);							//渲染到目的x,y
	//void Draw(HDC hdcDest,int x,int y);				//渲染到指定DC的指定地方	
	bool CollideWith(CSprite & sprite);					//是否碰撞
	bool CollideWith(RECT &rect);						//是否和某个矩形碰撞
	bool IsSelected(int x, int y);						//鼠标是否选中

	void SetColorKey(DWORD dwColorKey);					//设置关键色
	void SetZOrder(int nZOrder);						//设置Z—Order
	int GetZOrder();									//得到Z-Order
	HDC GetDC();										//得到精灵的位图DC
	void SetDestDC(HDC hdcDest);						//设置精灵渲染的目的DC
	void SetTexture(HDC hdcTexture);					//设置精灵的位图
	void SetPos(float x,float y);						//设置精灵的坐标
	void SetTexturePos(int x,int y);					//设置精灵源的左上角坐标	
	float GetXPos();									//得到精灵在目的DC的左上角x坐标	
	float GetYPos();									//得到精灵在目的DC的左上角y坐标
	int GetWidth();										//得到精灵宽度
	int GetHeight();									//得到精灵高度
	void SetHotSpot(POINT &pt);							//设置热点			
	POINT GetHotSpot();									//得到热点
	const RECT *GetBoundingBox();
	DWORD GetPixelColor(int x,int y);					//得到指定点的颜色
	
	void  SetDestRect(int x,int y,int width ,int height);//设置渲染的目的矩形
	void  SetScaleFactor(float xFactor,float yFactor);	//设置x，y方向的缩放系数
	virtual void Update(float fDeltaTime){}				//更新
	void SetRotationAngle(float fAngle)	;				//设置旋转角度					
	void SetTransparent(bool val);						//设置是否透明渲染
	bool GetTransparent();
	void SetVisible(bool val);							//设置精灵的可见性
	bool GetVisible();									//得到精灵的可见性
};
