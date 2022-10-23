#pragma once
#include "shapeclass.h"
class Box :
	public ShapeClass
{
public:
	Box(ID3D10Device*);
	~Box(void);

	bool Initialize();
};


