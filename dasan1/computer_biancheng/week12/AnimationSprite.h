#pragma once
#include "sprite.h"
/*
	CAnimationSprite�࣬�̳���CSprite��ʵ�ֶ�������Ĳ���
*/
class CAnimationSprite :public CSprite
{
public:
	virtual ~CAnimationSprite(void);
	//���ι��캯��
	CAnimationSprite(	HDC		tex,						//����ͼƬDC
						int		nFrames,					//��֡��
						int		nFps,						//ÿ�����֡���ٶȣ�
						int		x,							//��ʼ����Ļλ������x
						int		y,							//��ʼ����Ļλ������y
						int		w,							//����Ŀ��
						int		h,							//����ĸ߶�
						int		tx,							//�Ӿ���ͼƬ����ʼ����
						int		ty,
						int		texWidth,					//����ͼƬ�Ŀ��
						int		texHeight);					//����ͼƬ�ĸ߶�
	
	void		Play();										//���Ŷ�������
	void		Stop() { bPlaying=false; }					//ֹͣ����
	void		Resume() { bPlaying=true; }					//�ָ�����
	bool		IsPlaying() const { return bPlaying; }		//�Ƿ��ڲ���

	void		SetFps(int fps);							//����֡��	
	void		SetFrame(int n);							//���õ�ǰ����֡
	void		SetFrames(int n);							//������֡��
	int			GetFps();									//�õ���ǰ֡��
	int			GetFrame();									//���ص�ǰ֡
	int			GetFrames();								//�õ���֡��
	void		Update(float fDeltaTime);				//���¶���
	void        SetTextureStartPos(int tx,int ty);		//���ôӾ���ͼƬ�Ͽ�ʼ�и��λ��
private:
	int			texWidth;								//����ͼƬ�Ŀ��
	int			texHeight;								//����ͼƬ�ĸ߶�
	int         txStart;								//Դx
	int         tyStart;								//Դy
	bool		bPlaying;								//�Ƿ񲥷�
	float		fInterval;								//�ٶ�
	float		fSinceLastFrame;						//����һ֡�����ھ����˶��ٺ���
	int			nDelta;									//ÿ�θ��¶���֡
	int			nFrames;								//��֡��
	int			nFps;									//ÿ�����֡
	int			nCurFrame;								//��ǰ֡
};

	//void		Stop() { bPlaying=false; }					//ֹͣ����
	//void		Resume() { bPlaying=true; }					//�ָ�����
	//bool		IsPlaying() const { return bPlaying; }		//�Ƿ��ڲ���

	//void		SetFps(int fps) 
	//			{ this->nFps = fps;fInterval=1.0f/fps; }	//����֡��	
	//void		SetFrame(int n);							//���õ�ǰ����֡
	//void		SetFrames(int n) { nFrames=n; }				//������֡��
	//int			GetFps() { return  nFps;}				//�õ���ǰ֡��
	//int			GetFrame() { return nCurFrame; }		//���ص�ǰ֡
	//int			GetFrames(){ return nFrames; }			//�õ���֡��

