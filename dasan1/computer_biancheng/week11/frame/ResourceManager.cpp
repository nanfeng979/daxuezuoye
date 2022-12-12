#include "ResourceManager.h"

CResourceManager::CResourceManager(HWND hWnd)
{
	this->hWnd = hWnd;
	nSize = 0;
}

CResourceManager::~CResourceManager(void)
{
	for(int i=0;i<nSize;++i)
	{
		ReleaseResource(&res[i]);
	}
	
}
/*
	代码6- 释放指定的资源，参数是要释放的资源的指针的指针
*/
void CResourceManager::ReleaseResource(PResDesc *ppRes)
{
	if (ppRes != NULL)//如果资源指针不为NULL
	{
		DeleteDC((HDC)(*ppRes)->dwHandle1);//删除DC
		DeleteObject((HBITMAP)(*ppRes)->dwHandle2);//删除HBITMAP对象
		delete *ppRes;	//释放为资源节点分配的内存
		*ppRes = NULL;	//将指针设置为NULL
	}
}
/*
	代码6- ，根据指定的资源类型及资源名检索资源，
	如果找到匹配资源，返回指向该资源的PResDesc指针，否则返回NULL
*/
const PResDesc CResourceManager::GetResource(ResourceType resType,//资源类型
		const TCHAR *pszResName				//资源名
	)
{
	for(int i=0;i<nSize;++i)
	{
		if (res[i]->resourceType == resType)//如果是指定的资源类型
		{
			if (wcscmp(res[i]->szName,pszResName) == 0) //如果名称匹配
			{
				return res[i];
			}
		}
	}
	return NULL;
}
/*
	代码6- 根据给定的资源类型和资源名删除资源
*/
void CResourceManager::DeleteResource(ResourceType resType,//资源类型
		const TCHAR *pszResName)				//资源名
{
	int pos = -1;				//记录找到的资源的下标，初始值为-1
	for(int i=0;i<nSize;++i)	//遍历数组
	{
		if (res[i]->resourceType == resType)//如果是指定的资源类型
		{
			if (wcscmp(res[i]->szName,pszResName) == 0)//如果名称匹配
			{
				pos = i;			//记录下标
				break;				//跳出循环
			}
		}
	}
	if (pos >=0)	//如果记录的下标大于等于0，则表示找到了要删除的资源
	{
		PResDesc pRes = res[pos];	//记录该下标的资源指针
		for(int i=pos;i<nSize-1;++i)//从该下标开始，后面的数组元素顺序前移一个位置
		{
			res[i] = res[i+1];
		}
		ReleaseResource(&pRes);		//释放找到的这个资源
	}
}

/*
	代码6- 载入位图，生成位图节点存放到资源数组中
*/
void CResourceManager::LoadPictureFromFile(const TCHAR *pszName,const TCHAR *pszFile)
{
	//从磁盘载入位图	
	HBITMAP hBitmap=(HBITMAP)LoadImage(
		NULL,//包含位图实体的handle，
		pszFile,//位图的源路径与文件名
		IMAGE_BITMAP,//加载位图的类型
		0,0,//位图索要显示的宽高
		LR_LOADFROMFILE//加载标志，
	);
	if (!hBitmap)
	{
		return;
	}
	ResDesc *pResDesc = new ResDesc();//new一个ResDesc结构
	wcscpy_s(pResDesc->szName, pszName);
	HDC hdc=GetDC(hWnd);//获得当前窗口的DC
	 //在内存中创建一个和当前窗口兼容的绘图句柄
	HDC hdcBmp=CreateCompatibleDC(hdc);

	//将Bitmap选入内存中创建好的dc
	SelectObject(hdcBmp,hBitmap);
	ReleaseDC(hWnd,hdc);
	pResDesc->dwHandle1 = (DWORD)hdcBmp;//记录离屏缓冲的HDC
	pResDesc->dwHandle2 = (DWORD)hBitmap;//记录离屏缓冲的HBITMAP
	pResDesc->resourceType = RES_BMP;	//当前资源类型
	res[nSize++] = pResDesc;			//存放到数组的尾端
}




