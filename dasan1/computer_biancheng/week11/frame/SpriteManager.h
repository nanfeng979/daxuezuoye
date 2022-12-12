/***************************************************************************
	代码6- 精灵管理类，实现精灵创建、删除、遍历等操作
***************************************************************************/
#pragma once

#define MAX_SPRITES	1000
#include "Sprite.h"
#include "AnimationSprite.h"
#include "ResourceManager.h"
class CSpriteManager
{
public:
	CSpriteManager(CResourceManager *pResManager);	//传入一个ResourceManager对象的指针来构造SpriteManager
	virtual ~CSpriteManager(void);
public:
	CSprite* CreateSprite(
							const TCHAR *pszResourceName,//纹理资源名
							int x = 0,		//精灵初始位置		
							int y = 0,
							int w = 0,		//精灵宽度
							int h = 0,		//精灵高度
							ResourceType rt = RES_BMP
	);		//创建精灵
	CAnimationSprite* CreateAnimationSprite(
							const TCHAR *pszResourceName,//纹理资源名
							int			nFrames,//构成动画精灵的帧数
							float		nFps,	//动画播放的帧频
							int			x,		//精灵初始位置
							int			y,
							int			w,		//精灵宽度
							int			h,		//精灵高度
							int			tx = 0,	//纹理起始坐标
							int			ty = 0,
							ResourceType rt = RES_BMP
	);//创建动画精灵节点
	void DeleteSprite(CSprite *pSprite,bool bFree = true);	//删除精灵				
	CSprite *ReZOrder(CSprite *pSprite);					//根据Z-Order重排此精灵
	void Render(HDC hdcDest);								//渲染

	void Update(float fDeltaTime);
protected:
	CResourceManager *pResManager;							//资源管理对象			
	void InsertSprite(CSprite *pSprite);					//插入精灵到数组容器中
	CSprite	*pSprites[MAX_SPRITES];							//数组容器
	int nZOrder;	//下一个插入精灵Z-Order			
	int nSize;		//下一个插入精灵在数组中的下标
};

