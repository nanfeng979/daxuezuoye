#pragma once

#include <windows.h>

#define MAX_RESOURCES	1000
#define MAXRESCHARS	255
enum ResourceType		//��Դ����
{
	RES_BMP
};
typedef struct tagResDesc				//��Դ�ڵ�
{	
	TCHAR		szName[MAXRESCHARS];	//��Դ��
	DWORD		dwHandle1;				//��Դ���1��DC)
	DWORD		dwHandle2;				//��Դ���2 (hBitmap)
	ResourceType resourceType;			//��Դ����
}ResDesc,*PResDesc;


/************************************************
	��Դ��������������������е���Դ
	Ŀǰֻ����λͼ
************************************************/

class CResourceManager
{
public:
	//����λͼ��������������Ҫ�õ����ھ�������Թ��캯����Ҫ���뵱ǰ���ھ��
	CResourceManager(HWND hWnd);
	virtual ~CResourceManager(void);
public:	
	//����λͼ��Դ
	void LoadPictureFromFile(const TCHAR * pszName,const TCHAR *pszFile);	
	//������Դ���ͺ���Դ���õ���Դ�ڵ�
	const PResDesc GetResource(ResourceType resType,const TCHAR *pszResName);
	//��������ɾ����Դ
	void DeleteResource(ResourceType resType,const TCHAR *pszResName);
	//�ͷ�ָ����Դռ�õ��ڴ�
	void ReleaseResource(PResDesc *ppRes);
private:
	ResDesc *res[MAX_RESOURCES];															
	int		nSize;					//���Դ洢��Դ����һ�������±�
	HWND	hWnd;					//���ھ��
};
