#include "../include/Scene.h"

Scene::Scene()
{
	// Create camera
	camera = new Camera();

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	// Initialize meshes vector
	meshes = std::vector<Mesh*>();
}

Scene::~Scene()
{
	// Loop through all mesh pointers and delete the objects referenced
	for(int i = 0; i < meshes.size(); ++i)
	{
		if(meshes[i])
		{
			delete meshes[i];
		}
	}
	
	std::cout << "meshes deleted" << std::endl;
	
	// Close OpenGL window
	glDeleteProgram(programID);
}

void Scene::addMesh(Mesh* _mesh)
{
	meshes.push_back(_mesh);
}

void Scene::render(GLFWwindow* window)
{
	// Render all meshes
	for(int i = 0; i < meshes.size(); ++i)
	{
		meshes[i]->render(camera);
	}
}
