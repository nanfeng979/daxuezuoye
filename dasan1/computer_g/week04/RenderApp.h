#pragma once
#include "D3DApp.h"

#include "Shape.h"

class RenderApp :
	public D3DApp
{
public:
	RenderApp(HINSTANCE hInstance);
	~RenderApp();

	void initApp();
	void drawScene();

private:
	Shape *pTri;

	void buildFX();
	

	ID3D10Effect*	mFX;
	ID3D10EffectTechnique*	mTech;
	
	ID3D10EffectMatrixVariable*	mfxWVPVar;

	D3DXMATRIX		mView;
	D3DXMATRIX		mProj;
	D3DXMATRIX		mWVP;

	
};

