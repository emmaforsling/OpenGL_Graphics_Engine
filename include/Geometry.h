#ifndef GEOMETRY_H
#define GEOMETRY_H

// Standard includes
#include <iostream>

// OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Geometry{
public:	
	// Constructor
	Geometry();
	// Destructor
	~Geometry();

	GLuint getVertexArrayID();
	GLuint getVertexbuffer();

private:		
	GLuint VertexArrayID;
	GLuint vertexbuffer;
};

#endif