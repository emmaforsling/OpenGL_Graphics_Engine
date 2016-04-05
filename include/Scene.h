#ifndef SCENE_H
#define SCENE_H

// Standard includes
#include <vector>

// OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// AntTweakBar
#include <AntTweakBar.h>

// Source includes
#include "../include/Camera.h"
#include "../include/Mesh.h"
#include "../include/utils/Shader.h"
#include "../include/utils/controls.h"

class Scene{
public:
	// Constructor
	Scene();
	// Destructor
	~Scene();

	void render(GLFWwindow*);

	// Get functions
	std::vector<Mesh*> getMeshes();

private:
	Camera* camera;
	std::vector<Mesh *> meshes;
	GLuint programID;
	GLuint MatrixID;
};

#endif