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

//根据播放模式设置动画播放的初始条件
void CAnimationSprite::Play() 
{
	bPlaying=true;
	fSinceLastFrame=0.0f;
	nDelta = 1;
	SetFrame(0);
}
/*
	代码6- 根据系统流逝的时间来更新动画
*/
void CAnimationSprite::Update(float fDeltaTime)
{
	if(!bPlaying) 
	{
		return;
	}
	fSinceLastFrame += fDeltaTime;//累计从上一帧到此时刻流逝的时间
	//如果大于设定帧频表示的时间间隔，则更新纹理坐标
	if (fSinceLastFrame >= fInterval)
	{
		fSinceLastFrame = 0.0f;
		//调用SetFrame函数设置下一帧的纹理坐标
		SetFrame(nCurFrame+nDelta);
	}
}
/*
	代码6- 计算并设置当前帧截取的纹理坐标
*/
void CAnimationSprite::SetFrame(int n)//参数n代表设置第几帧
{
	int tx1, ty1;
	//计算纹理图片分为几列，texWidth是文理图片宽度，width是精灵宽度
	int ncols = texWidth / width; 
	n = n % nFrames;	//将n对总帧数取模
	//如果n<0，则n=n+nFrames，使其取值范围落在[0,nFrames]之间 
	if(n < 0) n = nFrames + n;
	nCurFrame = n;//将当前帧设置为n
	// 下面通过帧n计算纹理坐标
	ty1 = tyStart;
	tx1 = txStart + n*width;
	if(tx1 > texWidth - width) //如果跨行
	{
		n -= (texWidth -tx) / width;//计算n在下一行应该取第几帧
		tx1 = width * (n%ncols);//重新计算纹理坐标 
		ty1 += height * (1 + n/ncols);
	}
	SetTexturePos(tx1,ty1);//调用基类函数设置纹理坐标
}
void CAnimationSprite::SetTextureStartPos(int tx,int ty)
{
	this->txStart = tx;
	this->tyStart = ty;
	SetTexturePos(tx, ty);
}
