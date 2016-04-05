#ifndef Mesh_H
#define Mesh_H

// Standard includes
#include <iostream>

// OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Mesh{
public:	
	// Constructor
	Mesh();
	// Destructor
	~Mesh();

	// Init functions
	void initCube();
	void initOBJ(std::string filename);

	// Get functions
	GLuint getVertexArrayID();
	GLuint getVertexbuffer();

private:		
	GLuint vertexArrayID;
	GLuint vertexbuffer;
};

#endif