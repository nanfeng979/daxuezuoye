#pragma once
#include "game.h"//��������е�CGame�ඨ���ͷ�ļ�
#define	MAX_BALLOONS	30
#define	MAX_DIGIT		10
struct Balloon//��������Ľṹ
{
	CSprite *pBalloon;	//������
	float	fSpeed;		//������ٶ�
	int		type;		//���������
};
class CShootBalloonDemo :
	public CGame
{
public:
	CShootBalloonDemo(int fps = 0);
	~CShootBalloonDemo(void);
private:
	void Init();					//��д����Ĵ��麯��
	void Update(float fDeltaTime);	//��д�����Update����
	//��д��������������´�����
	void HandleLMouseDown(WPARAM wParam,LPARAM lParam);
	//��д���������ƶ�������
	void HandleMouseMove(WPARAM wParam,LPARAM lParam);
private:
	//��������Ƿ�ɳ����ϱ߽�
	void CheckOutOfBound();
	//��һ�������ĳ���������Ƴ�
	void DeleteBulloonFromArray(Balloon **pArray,int *pnArraySize,Balloon *pBalloon);
	//�������
	void AddBalloons();
	//�õ�һ�����ֵ��Ϊ������ƶ�����
	float GetRandSpeed();
	//����һ���µ�����ṹ
	Balloon *CreateNewBalloon();
	//���µ÷�
	void UpdateScore();
private:
	Balloon *pAliveBalloon[MAX_BALLOONS];	//�����������
	Balloon *pDeadBalloon[MAX_BALLOONS];	//��������������
	CSprite *pFrontSight;					//��꾫��
	CSprite *pScore[MAX_DIGIT];				//������ʾ����
	int		nAliveBalloon;					//��ǰ����������
	int		nDeadBalloon;					//��ǰ�������������
	int		score;							//�÷�
	int		nDigit;							//�÷ֵ�λ��
};