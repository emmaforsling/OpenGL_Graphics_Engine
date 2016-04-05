#ifndef Mesh_H
#define Mesh_H

// Standard includes
#include <iostream>
#include <vector>

// OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Source includes
#include "utils/ObjectLoader.h"

// GLM includes
#include <glm/glm.hpp>


class Mesh{
public:	
	// Constructor
	Mesh();
	// Destructor
	~Mesh();

	// Init functions
	void initCube(float size);
	void initOBJ(const char* filename);

	// Get functions
	GLuint getVertexArrayID();
	GLuint getVertexbuffer();
	GLuint getNormalBuffer();
	GLuint getUvBuffer(){ return uvbuffer; };
	int getVerticesLength(){ return vertices.size(); };

private:		
	// OpenGL handles 		
	GLuint vertexArrayID;
	GLuint vertexbuffer;
	GLuint normalBuffer;

	// For loaded OBJ's
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	GLuint uvbuffer;
};

#endif