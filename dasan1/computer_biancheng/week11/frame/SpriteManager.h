/***************************************************************************
	����6- ��������࣬ʵ�־��鴴����ɾ���������Ȳ���
***************************************************************************/
#pragma once

#define MAX_SPRITES	1000
#include "Sprite.h"
#include "AnimationSprite.h"
#include "ResourceManager.h"
class CSpriteManager
{
public:
	CSpriteManager(CResourceManager *pResManager);	//����һ��ResourceManager�����ָ��������SpriteManager
	virtual ~CSpriteManager(void);
public:
	CSprite* CreateSprite(
							const TCHAR *pszResourceName,//������Դ��
							int x = 0,		//�����ʼλ��		
							int y = 0,
							int w = 0,		//������
							int h = 0,		//����߶�
							ResourceType rt = RES_BMP
	);		//��������
	CAnimationSprite* CreateAnimationSprite(
							const TCHAR *pszResourceName,//������Դ��
							int			nFrames,//���ɶ��������֡��
							float		nFps,	//�������ŵ�֡Ƶ
							int			x,		//�����ʼλ��
							int			y,
							int			w,		//������
							int			h,		//����߶�
							int			tx = 0,	//������ʼ����
							int			ty = 0,
							ResourceType rt = RES_BMP
	);//������������ڵ�
	void DeleteSprite(CSprite *pSprite,bool bFree = true);	//ɾ������				
	CSprite *ReZOrder(CSprite *pSprite);					//����Z-Order���Ŵ˾���
	void Render(HDC hdcDest);								//��Ⱦ

	void Update(float fDeltaTime);
protected:
	CResourceManager *pResManager;							//��Դ�������			
	void InsertSprite(CSprite *pSprite);					//���뾫�鵽����������
	CSprite	*pSprites[MAX_SPRITES];							//��������
	int nZOrder;	//��һ�����뾫��Z-Order			
	int nSize;		//��һ�����뾫���������е��±�
};

