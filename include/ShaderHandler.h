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
	
	// Geometry Shader Constructor
	ShaderHandler(	const char* _vertex_file_path,
					const char* _fragment_file_path,
					const char* _geometry_file_path);

	// Tessellation Constructor
	ShaderHandler( 	const char * vertex_file_path,
                   	const char * tessellation_control_file_path,
                   	const char * tessellation_evaluation_file_path,
                   	const char * geometry_file_path,
                   	const char * fragment_file_path );

	~ShaderHandler() = default;

	GLuint createProgram();
private:
	// Init shader functions that stores their file_path and shaderID in the variable shaders
	void initShader(const char* _file_path, GLuint _gl_shader_type);
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