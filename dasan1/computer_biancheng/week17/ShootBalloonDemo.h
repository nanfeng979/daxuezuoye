#pragma once
#include "game.h"//包含框架中的CGame类定义的头文件
#define	MAX_BALLOONS	30
#define	MAX_DIGIT		10
struct Balloon//描述气球的结构
{
	CSprite *pBalloon;	//气球精灵
	float	fSpeed;		//气球的速度
	int		type;		//气球的类型
};
class CShootBalloonDemo :
	public CGame
{
public:
	CShootBalloonDemo(int fps = 0);
	~CShootBalloonDemo(void);
private:
	void Init();					//重写基类的纯虚函数
	void Update(float fDeltaTime);	//重写基类的Update函数
	//重写基类的鼠标左键按下处理函数
	void HandleLMouseDown(WPARAM wParam,LPARAM lParam);
	//重写基类的鼠标移动处理函数
	void HandleMouseMove(WPARAM wParam,LPARAM lParam);
private:
	//检查气球是否飞出了上边界
	void CheckOutOfBound();
	//将一个气球从某个数组中移除
	void DeleteBulloonFromArray(Balloon **pArray,int *pnArraySize,Balloon *pBalloon);
	//添加气球
	void AddBalloons();
	//得到一个随机值作为气球的移动速率
	float GetRandSpeed();
	//创建一个新的气球结构
	Balloon *CreateNewBalloon();
	//更新得分
	void UpdateScore();
private:
	Balloon *pAliveBalloon[MAX_BALLOONS];	//活动的气球数组
	Balloon *pDeadBalloon[MAX_BALLOONS];	//死亡的气球数组
	CSprite *pFrontSight;					//光标精灵
	CSprite *pScore[MAX_DIGIT];				//分数显示精灵
	int		nAliveBalloon;					//当前活动的气球个数
	int		nDeadBalloon;					//当前死亡的气球个数
	int		score;							//得分
	int		nDigit;							//得分的位数
};