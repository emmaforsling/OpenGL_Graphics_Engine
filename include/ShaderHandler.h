#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H

// Standard includes
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>

// OpenGL includes
#include <GL/glew.h>

using namespace std;

class ShaderHandler{
public:
	// Standard Constructor
	ShaderHandler(	const char* vertex_file_path, 
					const char* fragment_file_path);
	
	// Tessellation Constructor
	ShaderHandler( 	const char * vertex_file_path,
                   	const char * tessellation_control_file_path,
                   	const char * tessellation_evaluation_file_path,
                   	const char * geometry_file_path,
                   	const char * fragment_file_path );

	~ShaderHandler() = default;

	// Init shader functions that stores their file_path and shaderID in the variable shaders
	void initVertexShader(const char* _file_path);
	void initTessControlShader(const char* _file_path);
	void initTessEvalShader(const char* _file_path);
	void initGeometryShader(const char* _file_path);
	void initFragmentShader(const char* _file_path);

	GLuint createProgram();
private:
	// function called from the constructor
	void loadShader(const char* file_path, GLuint shaderID);
	void deleteShaders();

	struct Shader
	{
		const char* file_path;
		GLuint shaderID;
	};

	std::vector<Shader> shaders;

	GLint Result = GL_FALSE;
	int InfoLogLength;

};

#endif