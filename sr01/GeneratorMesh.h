#pragma once
#include"Mesh.h"
#include"MathDefine.h"
using easym::real;
class GeneratorMesh
{
public:
	GeneratorMesh();
	~GeneratorMesh();
	static easym::Mesh CreateMesh(real width, real height, real depth);
};

