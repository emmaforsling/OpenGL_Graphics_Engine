#ifndef Mesh_H
#define Mesh_H

// Standard includes
#include <iostream>
#include <vector>
// #include <map>
// #include <algorithm>
#include <png.h>

// OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Source includes
#include "utils/ObjectLoader.h"
#include "../include/utils/ShaderManager.h"
#include "../include/utils/controls.h"

// GLM includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Mesh{
public:	
	// Constructor
	Mesh();
	// Destructor
	~Mesh();

	// Init functions
	void initShaders(const char* vertexShader_filename, const char* fragmentShader_filename);
	void initCube(float size);
	void initOBJ(const char* filename);

	

	void setProgramID(GLuint _programID){
		programID = _programID;
		// Get a handle for our "MVP" uniform
		MatrixID = glGetUniformLocation(programID, "MVP");
	};
	// Get functions
	GLuint getVertexArrayID(){ return vertexArrayID; };
	GLuint getVertexbuffer(){ return vertexbuffer; };
	GLuint getNormalBuffer(){ return normalBuffer; };
	GLuint getUvBuffer(){ return uvbuffer; };
	int getVerticesLength(){ return vertices.size(); };

	float getTessellationScale(){return tessScale;};
	void setTessellationScale(float _tessScale){tessScale = _tessScale;};

	// Operations
	void setPosition(float _x, float _y, float _z);
	void setMaterialProperties(float k_diff, float k_spec, float _specPow);

	// Render functions
	void render();

	// Texture functions
	void setDispMap(std::string _filename);
	void setNormMap(std::string _filename);
	void setColorMap(std::string _filename);
	void setIsTessellationActive(bool _tessellation){tessellation = _tessellation;};
	GLuint png_texture_load(const char * file_name, int * width, int * height);

private:			
	GLuint vertexArrayID;
	GLuint vertexbuffer;
	GLuint normalBuffer;
	GLuint uvbuffer;
	GLuint programID;
	GLuint MatrixID;
	
	// Textures
	GLuint tex_dispMap;
	GLuint tex_normMap;
	GLuint tex_colorMap;
	GLuint handle_dispMap;
	GLuint handle_normMap;
	GLuint handle_colorMap;

	// Matrices
	glm::mat4 modelMatrix;
	glm::mat4 modelViewProjectionMatrix;

	// Data
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	// Material properties
	float k_diff;
	float k_spec;
	float specPow;

	// Tesselation
	float tessScale;

	bool tessellation;
};

#endif