#pragma once
#include <GL\glew.h>
#include <iostream>
#include <fstream>

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	GLuint regProgram;
	GLuint skyProgram;
	GLuint geoProgram;
	GLuint nulProgram;
	GLuint ambProgram;
	GLuint ligProgram;
	GLuint GetProgram() const;

	bool LoadShaders(const char* vFile, const char * fFile, GLuint &program);
	bool LoadLightShader(const char * fFile, GLuint &program);

	GLuint LoadShader(const char* file, GLenum shaderType);

private:

};
