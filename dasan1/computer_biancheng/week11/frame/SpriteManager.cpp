#include "SpriteManager.h"

/*
	����6- ���������������ͷž�����ռ�ڴ�
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
	����6- ����CSprite����
*/
CSprite *CSpriteManager::CreateSprite(const TCHAR *pszResourceName,int x,int y,int w,int h,ResourceType rt)
{
	int nWidth = w;
	int nHeight = h;
	//������Դ���õ����������������Դ
	PResDesc pResDesc = pResManager->GetResource(rt,pszResourceName);
	/*��������þ����Ȼ�߶ȣ���õ�����λͼ
	�Ŀ�ȸ߶���Ϊ����Ŀ�Ⱥ͸߶�*/
	if (w == 0 || h == 0)
	{
		BITMAP bm;
		GetObject((HBITMAP)pResDesc->dwHandle2,sizeof(bm),&bm);
		nWidth = bm.bmWidth;
		nHeight = bm.bmHeight;
	}
	//new CSprite����
	CSprite *pSprite = new CSprite((HDC)pResDesc->dwHandle1,x,y,nWidth,nHeight);
	//���ݴ�����˳������鸳Z-Orderֵ
	pSprite->SetZOrder(nZOrder++);
	//���봴���ľ���
	InsertSprite(pSprite);
	return pSprite;
}
/*
	����6- ����CAnimationSprite����
*/
CAnimationSprite* CSpriteManager::CreateAnimationSprite(const TCHAR *pszResourceName,int nFrames,float nFps,int x,int y,int w,int h,int tx,int ty,ResourceType rt)
{
	BITMAP bm;
	//������Դ���ҵ��������������������Դ
	PResDesc pResDesc = pResManager->GetResource(rt,pszResourceName);
	//�õ�����Ŀ�Ⱥ͸߶�
	GetObject((HBITMAP)pResDesc->dwHandle2,sizeof(bm),&bm); 
	//������������
	CAnimationSprite *pAnimationSprite = new CAnimationSprite((HDC)pResDesc->dwHandle1,nFrames,nFps,x,y,w,h,tx,ty,bm.bmWidth,bm.bmHeight);
	//���ݴ�����˳������鸳Z-Orderֵ
	pAnimationSprite->SetZOrder(nZOrder++);
	InsertSprite(pAnimationSprite);
	//���봴���ľ���
	return pAnimationSprite;
}
/*
	����6- ɾ��ָ���ľ��飬����bFree�����Ƿ���Ҫ�ͷŸþ�����ռ�õ��ڴ档
	����Ҫ��;������ʱ��Ҫ�����������ľ��飬����Ҫ�ͷŸþ��飬
	�ò�����ȱʡֵΪtrue����ȱʡ�����Ҫ�ͷ��ڴ��
*/
void CSpriteManager::DeleteSprite(CSprite *pSprite,bool bFree)
{
	int pos = -1;
	//�����������飬�ҵ�Ҫɾ�������λ��
	for(int i=0;i<nSize;++i)
	{
		if (pSprites[i] == pSprite)
		{
			pos = i;
			break;
		}
	}
	if (pos <0)
	{//û�ҵ�Ҫɾ���ľ��飬���˳�
		return;
	}
	if (bFree)
	{//���bFreeΪtrue����delete�þ�����ռ�õ��ڴ�
		delete pSprites[pos];
		pSprites[pos] = NULL;
	}
	//����λ��֮�������Ԫ��˳��ǰ��һλ
	for(int j=pos;j<nSize - 1;++j)
	{
		pSprites[j] = pSprites[j+1];
	}
	--nSize;//����β���±��1
}
/*
	����6- ���ݾ����Z-Order��������뵽������
*/
void CSpriteManager::InsertSprite(CSprite *pInsert)
{
	if (pInsert == NULL)
	{
		return;
	}
	//��������Ѿ����ˣ���return
	if (nSize >= MAX_SPRITES )
	{
		return;
	}
	int pos = nSize;
	//����������Z-Order�ҵ����ʵĲ���λ��
	for(int i=0;i<nSize;++i)
	{
		if (pSprites[i]->GetZOrder() > pInsert->GetZOrder())
		{
			pos = i;
			break;
		}
	}
	if (pos >= 0)
	{	//����ҵ������λ�ã��򽫸�λ�ú������Ԫ��˳�����һλ
		for(int j=nSize;j>pos;--j)
		{
			pSprites[j] = pSprites[j-1];
		}
		//�ڲ����λ���ϲ��뾫��
		pSprites[pos] = pInsert;
		++nSize;//����β���±��1
	}
}
/*
	����6- ��Ⱦ 
*/
void CSpriteManager::Render(HDC hdcDest)
{
	for(int i=0;i<nSize;++i)
	{
		if (pSprites[i]->GetVisible())
		{//����þ����ǿɼ��ģ�����øþ���Render������Ⱦ����
			pSprites[i]->Render(hdcDest);
		}
	}
}

/*
	����6- ���£����ݵĲ����Ǵ���һ֡����ʱϵͳ���ŵ�ʱ��
*/
void CSpriteManager::Update(float fDeltaTime)
{
	for(int i=0;i<nSize;++i)
	{
		pSprites[i]->Update(fDeltaTime);
	}
}
/*
	����6- ���ݾ����Z-Orderֵ���ž���
*/
CSprite *CSpriteManager::ReZOrder(CSprite *pSprite)
{
	//�ȴ�������ɾ�����飬���ǲ�Ҫ�ͷŸþ�����ռ�ڴ�
	DeleteSprite(pSprite,false);
	//���²���þ���
	InsertSprite(pSprite);
	return pSprite;
}

