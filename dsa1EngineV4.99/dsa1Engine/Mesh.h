#pragma once
#include "Vertex.h"
#include "VertInd.h"
#include <GL\glew.h>
#include <FreeImage.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
class Mesh
{
public:
	Mesh();
	Mesh(std::vector<Vertex> &v, std::vector<unsigned int> &i);
	Mesh(std::string filename);
	~Mesh();

	void LoadTexture(char* filename);
	GLuint GetTexId();
	void CreateBuffer();

	bool hasTex = false;
	unsigned int texID = 0;

	GLuint vertArr;
	GLuint vertBuf;

	std::vector<Vertex> verts;
	std::vector<unsigned int> ind;

	unsigned int count;
private:

};

