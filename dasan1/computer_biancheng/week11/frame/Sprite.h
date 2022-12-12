#pragma once
#pragma comment(lib, "msimg32.lib")
/*******************************************************************************
   ����6-1	����������,���ڹ������������Ϊ,������ͼƬ��Ⱦ��ָ����DC��ָ���ط�,
	��Ⱦʱ���Խ��������͸����Ⱦ�������ܼ���Ƿ�������������ײ

********************************************************************************/
#include <windows.h>
#include <math.h>
#define PI 3.1415926
class CSprite
{
public:
	CSprite(									//���ι���
			HDC hdcSprite,						//��������ͼ���HDC
			int x,								//���鴴��ʱ��λ��
			int y,
			int w,								//����Ŀ��
			int h								//����ĸ߶�
		);			
	virtual ~CSprite(void);								//����
protected:
	HDC		hdcSprite;									//������ָ���ͼƬ��Դ
	HDC     hdcDest;									//Ŀ��DC
	int     tx;											//Դͼx
	int     ty;											//Դͼy
	int     width;										//������
	int     height;										//����߶�			
	DWORD   dwColorKey;									//�ؼ�ɫ
	POINT   ptHotSpot;									//�ȵ�
	int     nZOrder;									//Z-Order
	bool    bTransparent;								//�Ƿ�͸����Ⱦ
	bool	bVisible;									//�Ƿ�ɼ�
	RECT	rtBoundingBox;								//��Χ��
	XFORM	translation;								//ƽ�ƾ���
	XFORM   rotation;									//��ת����
	XFORM	scale;										//���ž���
	XFORM	world;										//����任����
	void	InitXFORM(XFORM &form);						//���õ�λ��
	void    CalcBoundingBox();							//�����Χ��
public:
	//void Draw();										//��Ⱦ		
	virtual void Render(HDC hdcDest);					//�������õ�x,y��Ⱦ��Ŀ��DC
	//void Draw(int x,int y);							//��Ⱦ��Ŀ��x,y
	//void Draw(HDC hdcDest,int x,int y);				//��Ⱦ��ָ��DC��ָ���ط�	
	bool CollideWith(CSprite & sprite);					//�Ƿ���ײ
	bool CollideWith(RECT &rect);						//�Ƿ��ĳ��������ײ
	bool IsSelected(int x, int y);						//����Ƿ�ѡ��

	void SetColorKey(DWORD dwColorKey);					//���ùؼ�ɫ
	void SetZOrder(int nZOrder);						//����Z��Order
	int GetZOrder();									//�õ�Z-Order
	HDC GetDC();										//�õ������λͼDC
	void SetDestDC(HDC hdcDest);						//���þ�����Ⱦ��Ŀ��DC
	void SetTexture(HDC hdcTexture);					//���þ����λͼ
	void SetPos(float x,float y);						//���þ��������
	void SetTexturePos(int x,int y);					//���þ���Դ�����Ͻ�����	
	float GetXPos();									//�õ�������Ŀ��DC�����Ͻ�x����	
	float GetYPos();									//�õ�������Ŀ��DC�����Ͻ�y����
	int GetWidth();										//�õ�������
	int GetHeight();									//�õ�����߶�
	void SetHotSpot(POINT &pt);							//�����ȵ�			
	POINT GetHotSpot();									//�õ��ȵ�
	const RECT *GetBoundingBox();
	DWORD GetPixelColor(int x,int y);					//�õ�ָ�������ɫ
	
	void  SetDestRect(int x,int y,int width ,int height);//������Ⱦ��Ŀ�ľ���
	void  SetScaleFactor(float xFactor,float yFactor);	//����x��y���������ϵ��
	virtual void Update(float fDeltaTime){}				//����
	void SetRotationAngle(float fAngle)	;				//������ת�Ƕ�					
	void SetTransparent(bool val);						//�����Ƿ�͸����Ⱦ
	bool GetTransparent();
	void SetVisible(bool val);							//���þ���Ŀɼ���
	bool GetVisible();									//�õ�����Ŀɼ���
};
