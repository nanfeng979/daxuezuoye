#pragma once
#include "shapeclass.h"
class TriPyramid :
	public ShapeClass
{
public:
	TriPyramid(ID3D10Device*);
	~TriPyramid(void);

	bool Initialize();
};

