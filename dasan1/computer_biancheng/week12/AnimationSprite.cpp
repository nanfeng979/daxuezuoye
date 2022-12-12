#include "AnimationSprite.h"

CAnimationSprite::~CAnimationSprite(void)
{
}
CAnimationSprite::CAnimationSprite(HDC tex, int nFrames, int nFps, int x, int y, int w, int h,int tx,int ty,int texWidth,int texHeight)
	:CSprite(tex,x,y,w,h)
{
	this->nFrames = nFrames;
	this->nFps = nFps;
	this->texWidth = texWidth;
	this->texHeight = texHeight;
	this->tx = tx;
	this->ty = ty;
	txStart = tyStart = 0;
	bPlaying = false;
	this->fInterval = 1.0f/nFps;
}

//���ݲ���ģʽ���ö������ŵĳ�ʼ����
void CAnimationSprite::Play() 
{
	bPlaying=true;
	fSinceLastFrame=0.0f;
	nDelta = 1;
	SetFrame(0);
}
/*
	����6- ����ϵͳ���ŵ�ʱ�������¶���
*/
void CAnimationSprite::Update(float fDeltaTime)
{
	if(!bPlaying) 
	{
		return;
	}
	fSinceLastFrame += fDeltaTime;//�ۼƴ���һ֡����ʱ�����ŵ�ʱ��
	//��������趨֡Ƶ��ʾ��ʱ�������������������
	if (fSinceLastFrame >= fInterval)
	{
		fSinceLastFrame = 0.0f;
		//����SetFrame����������һ֡����������
		SetFrame(nCurFrame+nDelta);
	}
}
/*
	����6- ���㲢���õ�ǰ֡��ȡ����������
*/
void CAnimationSprite::SetFrame(int n)//����n�������õڼ�֡
{
	int tx1, ty1;
	//��������ͼƬ��Ϊ���У�texWidth������ͼƬ��ȣ�width�Ǿ�����
	int ncols = texWidth / width; 
	n = n % nFrames;	//��n����֡��ȡģ
	//���n<0����n=n+nFrames��ʹ��ȡֵ��Χ����[0,nFrames]֮�� 
	if(n < 0) n = nFrames + n;
	nCurFrame = n;//����ǰ֡����Ϊn
	// ����ͨ��֡n������������
	ty1 = tyStart;
	tx1 = txStart + n*width;
	if(tx1 > texWidth - width) //�������
	{
		n -= (texWidth -tx) / width;//����n����һ��Ӧ��ȡ�ڼ�֡
		tx1 = width * (n%ncols);//���¼����������� 
		ty1 += height * (1 + n/ncols);
	}
	SetTexturePos(tx1,ty1);//���û��ຯ��������������
}
void CAnimationSprite::SetTextureStartPos(int tx,int ty)
{
	this->txStart = tx;
	this->tyStart = ty;
	SetTexturePos(tx, ty);
}
