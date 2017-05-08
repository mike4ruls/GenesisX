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
#include <map>
class Mesh
{
public:
	enum MeshType {
		SingleMesh,
		MultipleMesh,
	}meshType = SingleMesh;

	struct MatLib {
		unsigned int illum;
		glm::vec3 diffuse;
		glm::vec3 ambience;
		glm::vec3 Tf;
		float Ni;
		std::string kdFileName;
		std::string trFileName;
	};
	struct MiniMesh {
		GLuint newVertArr;
		GLuint newVertBuf;
		bool hasTex = false;
		unsigned int texID = 0;
		unsigned int count;
	};

	Mesh();
	Mesh(std::vector<Vertex> &v);
	Mesh(std::vector<Vertex> &v, std::vector<unsigned int> &i);
	Mesh(std::string filename, MeshType m);
	~Mesh();

	void LoadTexture(char* filename);
	GLuint GetTexId();
	void CreateBuffer();
	void CreateModelLoadingBuffer(std::vector<glm::vec3> pos, std::vector<glm::vec2> uv, std::vector<glm::vec3> nor);

	bool hasTex = false;
	unsigned int texID = 0;

	GLuint vertArr;
	GLuint vertBuf;

	std::string kindomHeartsLevel = "models/DestinyIsland/level/";
	//std::string kindomHeartsLevel = "models/TraverseTown/level/";

	std::vector<Vertex> verts;
	std::vector<unsigned int> ind;
	std::vector<VertInd> moreInd;

	std::vector<MiniMesh> myMeshes;
	std::map<std::string, MatLib> matLibs;

	glm::vec4 color;
	glm::vec4 specular;

	unsigned int count;
private:

};

