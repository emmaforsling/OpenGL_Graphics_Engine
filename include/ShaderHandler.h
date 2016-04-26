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

	// Function that links the program and returns its programID
	GLuint createProgram();

private:
	// Functions called from the constructor
	void initShader(const char* _file_path, GLuint _gl_shader_type);
	void loadShader(const char* file_path, GLuint shaderID);
	
	// Delete function that is called in the createProgram() before returning the programID
	void deleteShaders();

	// Struct Shader, consisting of the file_path and the shader_type
	struct Shader
	{
		const char* file_path;
		GLuint shader_type;
	};

	std::vector<Shader> shaders;

	GLint Result = GL_FALSE;
	int InfoLogLength;

};

#endif