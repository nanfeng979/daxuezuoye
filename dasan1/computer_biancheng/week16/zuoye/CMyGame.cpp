#include "CMyGame.h"

CMyGame::CMyGame(int fps) :CGame(fps)
{
}

CMyGame::~CMyGame(void)
{
}

void CMyGame::Init()
{
	pResManager->LoadPictureFromFile(L"Background", L"background.bmp");
	pResManager->LoadPictureFromFile(L"Gear", L"gear.bmp");

	pBackground = pSpriteManager->CreateSprite(L"Background");
	pBackground->SetDestRect(0, 0, rectClient.right, rectClient.bottom);

	pLeftGear = pSpriteManager->CreateSprite(L"Gear", 400, 200);
	pLeftGear->SetTransparent(true);
	pRightGear = pSpriteManager->CreateSprite(L"Gear", 515, 200);
	pRightGear->SetTransparent(true);

	POINT pt = { pLeftGear->GetWidth() / 2, pLeftGear->GetHeight() / 2 };
	pLeftGear->SetHotSpot(pt);
	pRightGear->SetHotSpot(pt);

	bPlaying = true;

	pResManager->LoadPictureFromFile(L"Walker", L"walker.bmp");
	pResManager->LoadPictureFromFile(L"Monster", L"monster.bmp");

	PResDesc resWalker = pResManager->GetResource(RES_BMP, L"Walker");
	GetObject((HBITMAP)resWalker->dwHandle2, sizeof(BITMAP), &bmWalker);
	pWalker = pSpriteManager->CreateAnimationSprite(L"Walker", 4, 5, 0, 0, bmWalker.bmWidth / 4, bmWalker.bmHeight / 4);
	pWalker->SetTransparent(true);
	pWalker->Play();
	pWalker->SetTextureStartPos(0, pWalker->GetHeight() * 2);
	dir = right;

	PResDesc resMonster = pResManager->GetResource(RES_BMP, L"Monster");
	GetObject((HBITMAP)resMonster->dwHandle2, sizeof(BITMAP), &bmMonster);
	pMonster = pSpriteManager->CreateAnimationSprite(L"Monster", 4, 5, 100, 100, bmMonster.bmWidth / 4, bmMonster.bmHeight / 4);
	pMonster->SetTransparent(true);
	pMonster->Play();
}

void CMyGame::Update(float fDeltaTime)
{
	CGame::Update(fDeltaTime);
	if (!bPlaying)
	{
		return;
	}
	static float fTime = 0;
	fTime += fDeltaTime;
	pLeftGear->SetRotationAngle(fTime);
	pRightGear->SetRotationAngle(-fTime - ((360 / 8 / 2) * 3.1415 / 180));

	switch (dir)
	{
	case right:
		if (pWalker->GetXPos() < rectClient.right - bmWalker.bmWidth / 4)
		{
			pWalker->SetPos(pWalker->GetXPos() + STEP_walker, pWalker->GetYPos());
		}
		else {
			dir = down;
			pWalker->SetTextureStartPos(0, 0);
		}
		break;

	case down:
		if (pWalker->GetYPos() < rectClient.bottom - bmWalker.bmHeight / 4)
		{
			pWalker->SetPos(pWalker->GetXPos(), pWalker->GetYPos() + STEP_walker);
		}
		else {
			dir = left;
			pWalker->SetTextureStartPos(0, pWalker->GetHeight());
		}
		break;

	case left:
		if (pWalker->GetXPos() > 0)
		{
			pWalker->SetPos(pWalker->GetXPos() - STEP_walker, pWalker->GetYPos());
		}
		else {
			dir = up;
			pWalker->SetTextureStartPos(0, pWalker->GetHeight() * 3);
		}
		break;

	case up:
		if (pWalker->GetYPos() > 0)
		{
			pWalker->SetPos(pWalker->GetXPos(), pWalker->GetYPos() - STEP_walker);
		}
		else {
			dir = right;
			pWalker->SetTextureStartPos(0, pWalker->GetHeight() * 2);
		}
		break;
	}

	// 检测碰撞
	// 获取精灵的包围盒
	RECT rtWalker = *(pWalker->GetBoundingBox());
	if (pMonster->CollideWith(rtWalker))
	{
		pSpriteManager->DeleteSprite(pWalker, true);
	}
}

void CMyGame::HandleKeyDown(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{

		case VK_LEFT:
			pMonster->SetTextureStartPos(0, pMonster->GetHeight());
			pMonster->SetPos(pMonster->GetXPos() - STEP_Monster, pMonster->GetYPos());
			break;
		case VK_RIGHT:
			pMonster->SetTextureStartPos(0, pMonster->GetHeight() * 2);
			pMonster->SetPos(pMonster->GetXPos() + STEP_Monster, pMonster->GetYPos());
			break;
		case VK_UP:
			pMonster->SetTextureStartPos(0, pMonster->GetHeight() * 3);
			pMonster->SetPos(pMonster->GetXPos(), pMonster->GetYPos() - STEP_Monster);
			break;
		case VK_DOWN:
			pMonster->SetTextureStartPos(0, 0);
			pMonster->SetPos(pMonster->GetXPos(), pMonster->GetYPos() + STEP_Monster);
			break;
		return;
	}
}