#ifndef SCENE_H
#define SCENE_H

// Standard includes
#include <vector>

// OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Source includes
#include "../include/Camera.h"
#include "../include/Geometry.h"
#include "../include/utils/Shader.h"

class Scene{
public:
	// Constructor
	Scene();
	// Destructor
	~Scene();

	void render(GLFWwindow*);

	// Get functions
	std::vector<Geometry*> getGeometries();

private:
	Camera* camera;
	std::vector<Geometry *> geometries;
	GLuint programID;
};

#endif