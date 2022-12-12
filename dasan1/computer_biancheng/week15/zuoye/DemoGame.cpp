#include "DemoGame.h"
CDemoGame::CDemoGame(int nFps) :CGame(nFps)
{

}

CDemoGame::~CDemoGame(void)
{

}

void CDemoGame::Init()
{
	// 用资源管理对象加载资源
	pResManager->LoadPictureFromFile(L"Background", L"background.bmp");
	pResManager->LoadPictureFromFile(L"Box", L"box.bmp");
	pResManager->LoadPictureFromFile(L"Apple", L"apple.bmp");
	pResManager->LoadPictureFromFile(L"Monster", L"monster.bmp");
	pResManager->LoadPictureFromFile(L"Player", L"walker.bmp");

	// 背景
	pBackGround = pSpriteManager->CreateSprite(L"Background");
	pBackGround->SetDestRect(0, 0, rectClient.right, rectClient.bottom);

	// 定义矩形
	rt = { 400, 300, 800, 700 };

	// 箱子
	pBox = pSpriteManager->CreateSprite(L"Box", rt.left + (rt.right - rt.left) / 2, rt.top + (rt.bottom - rt.top) / 2);
	// 苹果
	pApple = pSpriteManager->CreateSprite(L"Apple", rt.left + (rt.right - rt.left) / 2, rt.top + (rt.bottom - rt.top) / 2);
	pApple->SetTransparent(true);
	pApple->SetVisible(false);
	// monster
	pMonster = pSpriteManager->CreateAnimationSprite(L"Monster", 4, 5, rt.left, rt.top, 128, 128);
	pMonster->SetTextureStartPos(0, pMonster->GetHeight() * 2);
	pMonster->SetTransparent(true);
	pMonster->Play();
	dir = right;
	// player
	pPlayer = pSpriteManager->CreateAnimationSprite(L"Player", 4, 5, 10, 100, 32, 54);
	pPlayer->SetTransparent(true);
	pPlayer->Play();

}

void CDemoGame::HandleKeyDown(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case VK_LEFT:
		pPlayer->SetTextureStartPos(0, pPlayer->GetHeight());
		pPlayer->SetPos(pPlayer->GetXPos() - STEP, pPlayer->GetYPos());
		break;
	case VK_RIGHT:
		pPlayer->SetTextureStartPos(0, pPlayer->GetHeight() * 2);
		pPlayer->SetPos(pPlayer->GetXPos() + STEP, pPlayer->GetYPos());
		break;
	case VK_UP:
		pPlayer->SetTextureStartPos(0, pPlayer->GetHeight() * 3);
		pPlayer->SetPos(pPlayer->GetXPos(), pPlayer->GetYPos() - STEP);
		break;
	case VK_DOWN:
		pPlayer->SetTextureStartPos(0, 0);
		pPlayer->SetPos(pPlayer->GetXPos(), pPlayer->GetYPos() + STEP);
		break;
	}

	return;
}

// 更新
void CDemoGame::Update(float fDeltaTime)
{
	if (pSpriteManager)
	{
		pSpriteManager->Update(fDeltaTime);
	}

	switch (dir)
	{
	case right:
		if (pMonster->GetXPos() < rt.right)
		{
			pMonster->SetPos(pMonster->GetXPos() + 2, pMonster->GetYPos());
		}
		else {
			pMonster->SetTextureStartPos(0, 0);
			dir = down;
		}
		break;

	case down:
		if (pMonster->GetYPos() < rt.bottom)
		{
			pMonster->SetPos(pMonster->GetXPos(), pMonster->GetYPos() + 2);
		}
		else {
			pMonster->SetTextureStartPos(0, pMonster->GetHeight());
			dir = left;
		}
		break;

	case left:
		if (pMonster->GetXPos() > rt.left)
		{
			pMonster->SetPos(pMonster->GetXPos() - 2, pMonster->GetYPos());
		}
		else {
			pMonster->SetTextureStartPos(0, pMonster->GetHeight() * 3);
			dir = up;
		}
		break;

	case up:
		if (pMonster->GetYPos() > rt.top)
		{
			pMonster->SetPos(pMonster->GetXPos(), pMonster->GetYPos() - 2);
		}
		else {
			pMonster->SetTextureStartPos(0, pMonster->GetHeight() * 2);
			dir = right;
		}
		break;
	}

	// 检测碰撞
	// 获取精灵的包围盒
	RECT rtSprite = *(pPlayer->GetBoundingBox());
	if (pMonster->CollideWith(rtSprite))
	{
		pSpriteManager->DeleteSprite(pPlayer, true);
	}

	if (pBox->CollideWith(rtSprite))
	{
		pSpriteManager->DeleteSprite(pBox, true);
		pApple->SetVisible(true);
	}

	return;
}

