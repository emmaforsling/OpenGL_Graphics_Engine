#ifndef Mesh_H
#define Mesh_H

// Standard includes
#include <iostream>
#include <vector>

// OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
	void initOBJ(std::string filename);

	// Get functions
	GLuint getVertexArrayID();
	GLuint getVertexbuffer();

private:
	// OpenGL handles 		
	GLuint vertexArrayID;
	GLuint vertexbuffer;

	// Data
	std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
};

#endif