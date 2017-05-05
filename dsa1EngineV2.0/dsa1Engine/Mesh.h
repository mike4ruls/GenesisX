#pragma once
#include "Vertex.h"
#include <GL\glew.h>
#include <vector>
class Mesh
{
public:
	Mesh();
	Mesh(std::vector<Vertex> &v, std::vector<unsigned int> &i);
	~Mesh();

	void CreateBuffer();

	GLuint vertArr;
	GLuint vertBuf;

	std::vector<Vertex> verts;
	std::vector<unsigned int> ind;

	unsigned int count;
private:

};

