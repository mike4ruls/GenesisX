#pragma once
#include <GL\glew.h>
#include <iostream>
#include <fstream>

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	GLuint program;
	GLuint GetProgram() const;

	bool LoadShaders(const char* vFile, const char * fFile);

	GLuint LoadShader(const char* file, GLenum shaderType);

private:

};

