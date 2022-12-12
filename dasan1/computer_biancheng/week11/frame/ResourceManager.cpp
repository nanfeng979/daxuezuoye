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
	����6- �ͷ�ָ������Դ��������Ҫ�ͷŵ���Դ��ָ���ָ��
*/
void CResourceManager::ReleaseResource(PResDesc *ppRes)
{
	if (ppRes != NULL)//�����Դָ�벻ΪNULL
	{
		DeleteDC((HDC)(*ppRes)->dwHandle1);//ɾ��DC
		DeleteObject((HBITMAP)(*ppRes)->dwHandle2);//ɾ��HBITMAP����
		delete *ppRes;	//�ͷ�Ϊ��Դ�ڵ������ڴ�
		*ppRes = NULL;	//��ָ������ΪNULL
	}
}
/*
	����6- ������ָ������Դ���ͼ���Դ��������Դ��
	����ҵ�ƥ����Դ������ָ�����Դ��PResDescָ�룬���򷵻�NULL
*/
const PResDesc CResourceManager::GetResource(ResourceType resType,//��Դ����
		const TCHAR *pszResName				//��Դ��
	)
{
	for(int i=0;i<nSize;++i)
	{
		if (res[i]->resourceType == resType)//�����ָ������Դ����
		{
			if (wcscmp(res[i]->szName,pszResName) == 0) //�������ƥ��
			{
				return res[i];
			}
		}
	}
	return NULL;
}
/*
	����6- ���ݸ�������Դ���ͺ���Դ��ɾ����Դ
*/
void CResourceManager::DeleteResource(ResourceType resType,//��Դ����
		const TCHAR *pszResName)				//��Դ��
{
	int pos = -1;				//��¼�ҵ�����Դ���±꣬��ʼֵΪ-1
	for(int i=0;i<nSize;++i)	//��������
	{
		if (res[i]->resourceType == resType)//�����ָ������Դ����
		{
			if (wcscmp(res[i]->szName,pszResName) == 0)//�������ƥ��
			{
				pos = i;			//��¼�±�
				break;				//����ѭ��
			}
		}
	}
	if (pos >=0)	//�����¼���±���ڵ���0�����ʾ�ҵ���Ҫɾ������Դ
	{
		PResDesc pRes = res[pos];	//��¼���±����Դָ��
		for(int i=pos;i<nSize-1;++i)//�Ӹ��±꿪ʼ�����������Ԫ��˳��ǰ��һ��λ��
		{
			res[i] = res[i+1];
		}
		ReleaseResource(&pRes);		//�ͷ��ҵ��������Դ
	}
}

/*
	����6- ����λͼ������λͼ�ڵ��ŵ���Դ������
*/
void CResourceManager::LoadPictureFromFile(const TCHAR *pszName,const TCHAR *pszFile)
{
	//�Ӵ�������λͼ	
	HBITMAP hBitmap=(HBITMAP)LoadImage(
		NULL,//����λͼʵ���handle��
		pszFile,//λͼ��Դ·�����ļ���
		IMAGE_BITMAP,//����λͼ������
		0,0,//λͼ��Ҫ��ʾ�Ŀ��
		LR_LOADFROMFILE//���ر�־��
	);
	if (!hBitmap)
	{
		return;
	}
	ResDesc *pResDesc = new ResDesc();//newһ��ResDesc�ṹ
	wcscpy_s(pResDesc->szName, pszName);
	HDC hdc=GetDC(hWnd);//��õ�ǰ���ڵ�DC
	 //���ڴ��д���һ���͵�ǰ���ڼ��ݵĻ�ͼ���
	HDC hdcBmp=CreateCompatibleDC(hdc);

	//��Bitmapѡ���ڴ��д����õ�dc
	SelectObject(hdcBmp,hBitmap);
	ReleaseDC(hWnd,hdc);
	pResDesc->dwHandle1 = (DWORD)hdcBmp;//��¼���������HDC
	pResDesc->dwHandle2 = (DWORD)hBitmap;//��¼���������HBITMAP
	pResDesc->resourceType = RES_BMP;	//��ǰ��Դ����
	res[nSize++] = pResDesc;			//��ŵ������β��
}




