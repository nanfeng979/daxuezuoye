#include "CMyGame.h"

CMyGame::CMyGame(int fps) :CGame(fps)
{}
CMyGame::~CMyGame(void)
{}

void CMyGame::Init()
{
	pResManager->LoadPictureFromFile(TEXT("BACKGROUND"), TEXT("background.bmp"));
	pResManager->LoadPictureFromFile(TEXT("GEAR"), TEXT("gear.bmp"));

	pBackground = pSpriteManager->CreateSprite(TEXT("BACKGROUND"));
	pBackground->SetDestRect(0, 0, rectClient.right, rectClient.bottom);
	pLeftGear = pSpriteManager->CreateSprite(TEXT("GEAR"),400,200);
	pRightGear = pSpriteManager->CreateSprite(TEXT("GEAR"), 515, 200);

	pLeftGear->SetTransparent(TRUE);
	pRightGear->SetTransparent(TRUE);
	POINT pt = { pLeftGear->GetWidth() / 2,pLeftGear->GetHeight() / 2 };
	pLeftGear->SetHotSpot(pt);
	pRightGear->SetHotSpot(pt);
	bPlaying = true;
}
void CMyGame::Update(float fDeltaTime) {
	CGame::Update(fDeltaTime);
	if (!bPlaying)  return;
	static float fTime = 0;
	fTime += fDeltaTime;
	pLeftGear->SetRotationAngle(fTime);
	pRightGear->SetRotationAngle(-(fTime + 0.35f));
}