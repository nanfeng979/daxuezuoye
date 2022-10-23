#pragma once
#include "shapeclass.h"
class LightTriPyramid :
	public ShapeClass
{
public:
	LightTriPyramid(ID3D10Device*);
	~LightTriPyramid(void);

	bool Initialize();
};

