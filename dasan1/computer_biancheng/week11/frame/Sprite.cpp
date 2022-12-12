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
bool CSprite::CollideWith(RECT &rect)//�����Ƿ��һ�����η�������ײ
{
	RECT rtIntersect;
	return IntersectRect(&rtIntersect,&this->rtBoundingBox,&rect);
}
bool CSprite::CollideWith(CSprite &sprite)//�����Ƿ������һ�����鷢������ײ 
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
	��Ⱦ���鵽Ŀ��DC������hdcDestͨ����׼����Ⱦ����ʱ
	������˫����ĺ󱸻����DC��
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
	//hdcSprite�Ǽ��صľ���λͼ��DC
	if (hdcSprite == NULL )
	{
		return;
	}
	/*
		��ϱ任��ͨ����S.R.T˳����б任������scale�����ž���
		rotatiao����ת����translation��ƽ�ƾ�����������Ӧ��
		��������ϵ����������ת�ǶȺ�����λ�õȺ����н��м��㡣
		Ȼ�󽫱任�����ŵ�world�����С�
	*/
	CombineTransform(&world,&world,&scale);
	CombineTransform(&world,&world,&rotation);
	CombineTransform(&world,&world,&translation);
	
	//���õ�ǰ�任
	SetWorldTransform(hdcDest, &world); 
	
	if (bTransparent)
	{	//͸����Ⱦ��Ҫ�����ȵ��λ�ã������ڱ任�����Ҫ��ȥ�ȵ������
		TransparentBlt(hdcDest,0 - ptHotSpot.x,0 - ptHotSpot.y, width,height,hdcSprite,tx,ty,width,height,dwColorKey);
	}
	else
	{	//������Ⱦ��Ҫ�����ȵ��λ�ã������ڱ任�����Ҫ��ȥ�ȵ������
		BitBlt(hdcDest,0 - ptHotSpot.x ,0 - ptHotSpot.y,width,height,hdcSprite,tx,ty,SRCCOPY);
	}
	//����DC�ı任����Ϊ��λ��
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

//void  CSprite::SetDestWidth(int nWidth)													//����Ŀ�Ŀ��
//{
//	this->nDestWidth = nWidth;
//}

//void  CSprite::SetDestHeight(int nHeight)												//����Ŀ�ĸ߶�
//{
//	this->nDestHeight = nHeight;
//}

void CSprite::SetScaleFactor(float xFactor,float yFactor)	//��������ϵ��
{
	InitXFORM(scale);
	scale.eM11 = xFactor;
	scale.eM22 = yFactor;
	CalcBoundingBox();
}

void CSprite::SetRotationAngle(float fAngle)				//������ת�Ƕ�					
{
	rotation.eM11 = (float)cos(fAngle); 
	rotation.eM12 = (float)sin(fAngle);
	rotation.eM21 = (float)-sin(fAngle); 
	rotation.eM22 = (float)cos(fAngle);
	rotation.eDx  = (float)0.0; 
	rotation.eDy  = (float)0.0; 
	CalcBoundingBox();
}
void CSprite::SetPos(float x,float y)						//����λ��
{
	InitXFORM(translation);	
	translation.eDx = x ;
	translation.eDy = y ;
	CalcBoundingBox();
}

void CSprite::SetDestRect(int x,int y,int w,int h)		//����Ŀ�ľ��η�Χ
{
	//����Ŀ�ľ��η�Χ������ͬʱ���þ����λ�ü�������ϵ��
	translation.eDx = x;
	translation.eDy = y;

	scale.eM11 = (float)w / (float)width;
	scale.eM22 = (float)h / (float)height;
	CalcBoundingBox();
}
/*
	���� ���㰴��S.R.T�任��ľ����Χ�о���
	����scale�����ž���rotation����ת����
	translation��ƽ�ƾ���
*/
void CSprite::CalcBoundingBox()
{
	//�任֮ǰ�İ�Χ�о��ε�4����������
	POINT pt[4];
	pt[0].x = 0;			pt[0].y = 0;
	pt[1].x = 0;			pt[1].y = height;
	pt[2].x = width;		pt[2].y = height;
	pt[3].x = width;		pt[3].y = 0;
	//ѭ������任���Χ�о��ε�4����������
	for(int i=0;i<4;++i)
	{
		float x =  (pt[i].x - ptHotSpot.x )* scale.eM11;
		float y =  (pt[i].y - ptHotSpot.y )* scale.eM22 ;
		pt[i].x = (x * rotation.eM11 + y * rotation.eM21 )+ translation.eDx;
		pt[i].y = (x * rotation.eM12 + y * rotation.eM22) + translation.eDy;
	}
	//������С��x��y���꼰����x��y����
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
	//���ñ任���Χ�о��ε�ֵ
	rtBoundingBox.left = fMinX;
	rtBoundingBox.top = fMinY;
	rtBoundingBox.right = fMaxX;
	rtBoundingBox.bottom = fMaxY;
}

