#ifndef LIGHT_H
#define LIGHT_H

#include "windows.h"
#include <D3D10.h>
#include <D3DX10.h>

struct Light
{
	Light()
	{
		ZeroMemory(this, sizeof(Light));
	}

	D3DXVECTOR3 pos;
	float pad1;      // not used
	D3DXVECTOR3 dir;
	float pad2;      // not used
	D3DXCOLOR ambient;
	D3DXCOLOR diffuse;
	D3DXCOLOR specular;
	D3DXVECTOR3 att;
	float spotPow;
	float range;
};
#endif