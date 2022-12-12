#pragma once

#include <windows.h>

#define MAX_RESOURCES	1000
#define MAXRESCHARS	255
enum ResourceType		//资源类型
{
	RES_BMP
};
typedef struct tagResDesc				//资源节点
{	
	TCHAR		szName[MAXRESCHARS];	//资源名
	DWORD		dwHandle1;				//资源句柄1（DC)
	DWORD		dwHandle2;				//资源句柄2 (hBitmap)
	ResourceType resourceType;			//资源类型
}ResDesc,*PResDesc;


/************************************************
	资源管理器，用数组管理所有的资源
	目前只管理位图
************************************************/

class CResourceManager
{
public:
	//载入位图创建离屏缓冲需要用到窗口句柄，所以构造函数中要传入当前窗口句柄
	CResourceManager(HWND hWnd);
	virtual ~CResourceManager(void);
public:	
	//载入位图资源
	void LoadPictureFromFile(const TCHAR * pszName,const TCHAR *pszFile);	
	//根据资源类型和资源名得到资源节点
	const PResDesc GetResource(ResourceType resType,const TCHAR *pszResName);
	//从数组中删除资源
	void DeleteResource(ResourceType resType,const TCHAR *pszResName);
	//释放指定资源占用的内存
	void ReleaseResource(PResDesc *ppRes);
private:
	ResDesc *res[MAX_RESOURCES];															
	int		nSize;					//可以存储资源的下一个数组下标
	HWND	hWnd;					//窗口句柄
};
