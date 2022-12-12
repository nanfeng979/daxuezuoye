#include "SpriteManager.h"

/*
	代码6- 析构函数，遍历释放精灵所占内存
*/
CSpriteManager::~CSpriteManager(void)
{
	for(int i=0;i<nSize;++i)
	{
		delete pSprites[i];
		pSprites[i] = NULL;
	}
}
CSpriteManager::CSpriteManager(CResourceManager *pResManager)
{
	nZOrder = 0;
	nSize = 0;
	this->pResManager = pResManager;
}
/*
	代码6- 创建CSprite对象
*/
CSprite *CSpriteManager::CreateSprite(const TCHAR *pszResourceName,int x,int y,int w,int h,ResourceType rt)
{
	int nWidth = w;
	int nHeight = h;
	//根据资源名得到创建精灵的纹理资源
	PResDesc pResDesc = pResManager->GetResource(rt,pszResourceName);
	/*如果不设置精灵宽度或高度，则得到纹理位图
	的宽度高度作为精灵的宽度和高度*/
	if (w == 0 || h == 0)
	{
		BITMAP bm;
		GetObject((HBITMAP)pResDesc->dwHandle2,sizeof(bm),&bm);
		nWidth = bm.bmWidth;
		nHeight = bm.bmHeight;
	}
	//new CSprite对象
	CSprite *pSprite = new CSprite((HDC)pResDesc->dwHandle1,x,y,nWidth,nHeight);
	//根据创建的顺序给精灵赋Z-Order值
	pSprite->SetZOrder(nZOrder++);
	//插入创建的精灵
	InsertSprite(pSprite);
	return pSprite;
}
/*
	代码6- 创建CAnimationSprite对象
*/
CAnimationSprite* CSpriteManager::CreateAnimationSprite(const TCHAR *pszResourceName,int nFrames,float nFps,int x,int y,int w,int h,int tx,int ty,ResourceType rt)
{
	BITMAP bm;
	//根据资源名找到创建动画精灵的纹理资源
	PResDesc pResDesc = pResManager->GetResource(rt,pszResourceName);
	//得到纹理的宽度和高度
	GetObject((HBITMAP)pResDesc->dwHandle2,sizeof(bm),&bm); 
	//创建动画精灵
	CAnimationSprite *pAnimationSprite = new CAnimationSprite((HDC)pResDesc->dwHandle1,nFrames,nFps,x,y,w,h,tx,ty,bm.bmWidth,bm.bmHeight);
	//根据创建的顺序给精灵赋Z-Order值
	pAnimationSprite->SetZOrder(nZOrder++);
	InsertSprite(pAnimationSprite);
	//插入创建的精灵
	return pAnimationSprite;
}
/*
	代码6- 删除指定的精灵，参数bFree表明是否需要释放该精灵所占用的内存。
	其主要用途在于有时需要复用所创建的精灵，则不需要释放该精灵，
	该参数的缺省值为true，即缺省情况是要释放内存的
*/
void CSpriteManager::DeleteSprite(CSprite *pSprite,bool bFree)
{
	int pos = -1;
	//遍历精灵数组，找到要删除精灵的位置
	for(int i=0;i<nSize;++i)
	{
		if (pSprites[i] == pSprite)
		{
			pos = i;
			break;
		}
	}
	if (pos <0)
	{//没找到要删除的精灵，则退出
		return;
	}
	if (bFree)
	{//如果bFree为true，则delete该精灵所占用的内存
		delete pSprites[pos];
		pSprites[pos] = NULL;
	}
	//将该位置之后的数组元素顺序前移一位
	for(int j=pos;j<nSize - 1;++j)
	{
		pSprites[j] = pSprites[j+1];
	}
	--nSize;//数组尾部下标减1
}
/*
	代码6- 根据精灵的Z-Order将精灵插入到数组中
*/
void CSpriteManager::InsertSprite(CSprite *pInsert)
{
	if (pInsert == NULL)
	{
		return;
	}
	//如果数组已经满了，则return
	if (nSize >= MAX_SPRITES )
	{
		return;
	}
	int pos = nSize;
	//遍历，根据Z-Order找到合适的插入位置
	for(int i=0;i<nSize;++i)
	{
		if (pSprites[i]->GetZOrder() > pInsert->GetZOrder())
		{
			pos = i;
			break;
		}
	}
	if (pos >= 0)
	{	//如果找到插入的位置，则将该位置后的数组元素顺序后移一位
		for(int j=nSize;j>pos;--j)
		{
			pSprites[j] = pSprites[j-1];
		}
		//在插入的位置上插入精灵
		pSprites[pos] = pInsert;
		++nSize;//数组尾部下标加1
	}
}
/*
	代码6- 渲染 
*/
void CSpriteManager::Render(HDC hdcDest)
{
	for(int i=0;i<nSize;++i)
	{
		if (pSprites[i]->GetVisible())
		{//如果该精灵是可见的，则调用该精灵Render函数渲染精灵
			pSprites[i]->Render(hdcDest);
		}
	}
}

/*
	代码6- 更新，传递的参数是从上一帧到此时系统流逝的时间
*/
void CSpriteManager::Update(float fDeltaTime)
{
	for(int i=0;i<nSize;++i)
	{
		pSprites[i]->Update(fDeltaTime);
	}
}
/*
	代码6- 根据精灵的Z-Order值重排精灵
*/
CSprite *CSpriteManager::ReZOrder(CSprite *pSprite)
{
	//先从数组中删除精灵，但是不要释放该精灵所占内存
	DeleteSprite(pSprite,false);
	//重新插入该精灵
	InsertSprite(pSprite);
	return pSprite;
}

