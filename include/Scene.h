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
#include "../include/Mesh.h"
#include "../include/Camera.h"

class Scene{
public:
	// Constructor
	Scene();
	// Destructor
	~Scene();

	// Scene set-up functions
	void addMesh(Mesh* _mesh);

	// Render
	void render(GLFWwindow*);

private:
	Camera* camera;
	std::vector<Mesh *> meshes;
	GLuint programID;
	GLuint MatrixID;
};

#endif