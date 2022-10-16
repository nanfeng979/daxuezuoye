#pragma once
#include "D3DApp.h"
#include "Shape.h"
#include "light.h"

class LightApp :
	public D3DApp
{
public:
	LightApp(HINSTANCE hInstance);
	~LightApp();

	void initApp();
	void drawScene();

private:
	Shape* pTri,*pTriPyramid;

	void buildFX();

	Light lights[3];
	int lightIndex;

	D3DXVECTOR3 mEyePos;
	ID3D10Effect* mFX;
	ID3D10EffectTechnique* mTech;

	ID3D10EffectVariable* mfxLightVar;
	ID3D10EffectScalarVariable* mfxLightTypeVar;
	ID3D10EffectVariable* mfxEyePosVar;

	ID3D10EffectMatrixVariable* mfxWorldVar;
	ID3D10EffectMatrixVariable* mfxWVPVar;

	D3DXMATRIX		mView;
	D3DXMATRIX		mProj;
	D3DXMATRIX		mWVP;


};

