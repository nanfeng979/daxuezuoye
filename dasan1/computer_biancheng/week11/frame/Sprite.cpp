#include "Sprite.h"

//CSprite::CSprite(void)
//{
//}

CSprite::~CSprite(void)
{
}
CSprite::CSprite(HDC hdcSprite,int x,int y,int w,int h)
{
	this->hdcSprite = hdcSprite;
	/*this->x = x;
	this->y = y;*/
	width = w;
	height = h;
	//this->rectSprite.left = x;
	//this->rectSprite.top = y;
	//this->rectSprite.right = x + w;
	//this->rectSprite.bottom = y + h;
	//

	tx = 0;
	ty = 0;
	ptHotSpot.x = 0;
	ptHotSpot.y = 0;
	dwColorKey = GetPixel(hdcSprite,0,0);

	bTransparent = false;
	bVisible = true;
	hdcDest = NULL;
	

	InitXFORM(translation);
	InitXFORM(rotation);
	InitXFORM(scale);
	InitXFORM(world);
	
	translation.eDx = x;
	translation.eDy = y;
	CalcBoundingBox();
}

void CSprite::InitXFORM(XFORM &form)
{
	memset(&form,0,sizeof(XFORM));
	form.eM11 = form.eM22 = 1.0f;
}
bool CSprite::IsSelected(int x,int y)
{
	return (x >= rtBoundingBox.left && x <= rtBoundingBox.right &&
		y >= rtBoundingBox.top  && y <= rtBoundingBox.bottom);
}
bool CSprite::CollideWith(RECT &rect)//计算是否和一个矩形发生了碰撞
{
	RECT rtIntersect;
	return IntersectRect(&rtIntersect,&this->rtBoundingBox,&rect);
}
bool CSprite::CollideWith(CSprite &sprite)//计算是否和另外一个精灵发生了碰撞 
{
	RECT rtIntersect;
	return IntersectRect(&rtIntersect,&this->rtBoundingBox,sprite.GetBoundingBox());
}
void CSprite::SetTransparent(bool val)
{
	bTransparent = val;
}
bool CSprite::GetTransparent()
{
	return bTransparent;
}
void CSprite::SetVisible(bool val)
{
	bVisible = val;
}
bool CSprite::GetVisible()
{
	return bVisible;
}

/*
	渲染精灵到目的DC，参数hdcDest通常是准备渲染环境时
	创建的双缓冲的后备缓冲的DC。
*/
void CSprite::Render(HDC hdcDest)
{
	if( !bVisible )
		return ;
	this->hdcDest = hdcDest;	
	if (hdcDest == NULL )
	{
		return ;
	}
	//hdcSprite是加载的精灵位图的DC
	if (hdcSprite == NULL )
	{
		return;
	}
	/*
		组合变换，通常按S.R.T顺序进行变换，其中scale是缩放矩阵
		rotatiao是旋转矩阵，translation是平移矩阵，它们在相应的
		设置缩放系数、设置旋转角度和设置位置等函数中进行计算。
		然后将变换结果存放到world矩阵中。
	*/
	CombineTransform(&world,&world,&scale);
	CombineTransform(&world,&world,&rotation);
	CombineTransform(&world,&world,&translation);
	
	//设置当前变换
	SetWorldTransform(hdcDest, &world); 
	
	if (bTransparent)
	{	//透明渲染，要考虑热点的位置，所以在变换坐标后还要减去热点的坐标
		TransparentBlt(hdcDest,0 - ptHotSpot.x,0 - ptHotSpot.y, width,height,hdcSprite,tx,ty,width,height,dwColorKey);
	}
	else
	{	//正常渲染，要考虑热点的位置，所以在变换坐标后还要减去热点的坐标
		BitBlt(hdcDest,0 - ptHotSpot.x ,0 - ptHotSpot.y,width,height,hdcSprite,tx,ty,SRCCOPY);
	}
	//重设DC的变换矩阵为单位阵
	InitXFORM(world);
	SetWorldTransform(hdcDest, &world); 
	/*SelectObject(hdcDest,::GetStockObject(WHITE_PEN));
	SelectObject(hdcDest,::GetStockObject(NULL_BRUSH));
	Rectangle(hdcDest,rtBoundingBox.left,rtBoundingBox.top,rtBoundingBox.right,rtBoundingBox.bottom);*/
}

//SelectObject(hdcDest,::GetStockObject(WHITE_PEN));
//	SelectObject(hdcDest,::GetStockObject(NULL_BRUSH));
//	Rectangle(hdcDest,rtBoundingBox.left,rtBoundingBox.top,rtBoundingBox.right,rtBoundingBox.bottom);
//void CSprite::Draw(bool bTransparent) 
//{
//
//	this->bTransparent = bTransparent;
//	Draw();
//	
//}



//void CSprite::StretchDraw(HDC hdcDest,int nDestX,int nDestY,int nDestWidth,int nDestHeight)
//{
//	bStretchDraw = true;
//	this->nDestWidth = nDestWidth;
//	this->nDestHeight = nDestHeight;
//	Draw(hdcDest,nDestX,nDestY);
//
//}
POINT CSprite::GetHotSpot() 
{
	return this->ptHotSpot;
}
DWORD CSprite::GetPixelColor(int x,int y)
{
	return GetPixel(hdcSprite,x,y);
}
//const RECT *CSprite::GetSpriteRect()
//{
//	return &rectSprite;
//}

const RECT *CSprite::GetBoundingBox()
{
	return &rtBoundingBox;
}
int CSprite::GetZOrder() 
{
	return this->nZOrder;
}
void CSprite::SetColorKey(DWORD dwColorKey) 
{
	this->dwColorKey = dwColorKey;
}
void CSprite::SetDestDC(HDC hdcDest)
{
	this->hdcDest = hdcDest;
}
void CSprite::SetTexture(HDC hdcTexture)
{
	this->hdcSprite = hdcTexture;
}

void CSprite::SetHotSpot(POINT &pt)
{
	this->ptHotSpot = pt;
	/*translation.eDx += pt.x;
	translation.eDy += pt.y;*/
}
//void CSprite::SetStretchDraw(bool bVal) 
//{
//	this->bStretchDraw = bVal;
//	if (!bVal)
//	{
//		nDestWidth = width;
//		nDestHeight = height;
//	}
//}
void CSprite::SetZOrder(int nZOrder) 
{
	this->nZOrder = nZOrder;
}
HDC CSprite::GetDC()
{
	return hdcSprite;
}

int CSprite::GetWidth()
{
	return width;
}
int CSprite::GetHeight()
{
	return height;
}
float CSprite::GetXPos()
{
	return translation.eDx;
}
float CSprite::GetYPos()
{
	return translation.eDy;
}
void CSprite::SetTexturePos(int x,int y)
{
	this->tx = x;
	this->ty = y;
}

//void  CSprite::SetDestWidth(int nWidth)													//设置目的宽度
//{
//	this->nDestWidth = nWidth;
//}

//void  CSprite::SetDestHeight(int nHeight)												//设置目的高度
//{
//	this->nDestHeight = nHeight;
//}

void CSprite::SetScaleFactor(float xFactor,float yFactor)	//设置缩放系数
{
	InitXFORM(scale);
	scale.eM11 = xFactor;
	scale.eM22 = yFactor;
	CalcBoundingBox();
}

void CSprite::SetRotationAngle(float fAngle)				//设置旋转角度					
{
	rotation.eM11 = (float)cos(fAngle); 
	rotation.eM12 = (float)sin(fAngle);
	rotation.eM21 = (float)-sin(fAngle); 
	rotation.eM22 = (float)cos(fAngle);
	rotation.eDx  = (float)0.0; 
	rotation.eDy  = (float)0.0; 
	CalcBoundingBox();
}
void CSprite::SetPos(float x,float y)						//设置位置
{
	InitXFORM(translation);	
	translation.eDx = x ;
	translation.eDy = y ;
	CalcBoundingBox();
}

void CSprite::SetDestRect(int x,int y,int w,int h)		//设置目的矩形范围
{
	//设置目的矩形范围，可以同时设置精灵的位置及其缩放系数
	translation.eDx = x;
	translation.eDy = y;

	scale.eM11 = (float)w / (float)width;
	scale.eM22 = (float)h / (float)height;
	CalcBoundingBox();
}
/*
	代码 计算按照S.R.T变换后的精灵包围盒矩形
	其中scale是缩放矩阵，rotation是旋转矩阵，
	translation是平移矩阵
*/
void CSprite::CalcBoundingBox()
{
	//变换之前的包围盒矩形的4个顶点坐标
	POINT pt[4];
	pt[0].x = 0;			pt[0].y = 0;
	pt[1].x = 0;			pt[1].y = height;
	pt[2].x = width;		pt[2].y = height;
	pt[3].x = width;		pt[3].y = 0;
	//循环计算变换后包围盒矩形的4个顶点坐标
	for(int i=0;i<4;++i)
	{
		float x =  (pt[i].x - ptHotSpot.x )* scale.eM11;
		float y =  (pt[i].y - ptHotSpot.y )* scale.eM22 ;
		pt[i].x = (x * rotation.eM11 + y * rotation.eM21 )+ translation.eDx;
		pt[i].y = (x * rotation.eM12 + y * rotation.eM22) + translation.eDy;
	}
	//计算最小的x，y坐标及最大的x，y坐标
	float fMinX = pt[0].x;
	float fMaxX = pt[0].x;
	float fMinY = pt[0].y;
	float fMaxY = pt[0].y;
	for(int i=1;i<4;++i)
	{
		if (fMinX > pt[i].x)
		{
			fMinX = pt[i].x;
		}
		if (fMaxX < pt[i].x)
		{
			fMaxX = pt[i].x;
		}
		if (fMinY > pt[i].y)
		{
			fMinY = pt[i].y;
		}
		if (fMaxY < pt[i].y)
		{
			fMaxY = pt[i].y;
		}
	}
	//设置变换后包围盒矩形的值
	rtBoundingBox.left = fMinX;
	rtBoundingBox.top = fMinY;
	rtBoundingBox.right = fMaxX;
	rtBoundingBox.bottom = fMaxY;
}

