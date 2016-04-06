#include "../include/Scene.h"

Scene::Scene()
{
	camera = new Camera();

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	meshes = std::vector<Mesh*>();


	// This should not be in the constructor, perhaps... =)
	Mesh* tempMesh1 = new Mesh();
	Mesh* tempMesh2 = new Mesh();
	// Mesh 1
	tempMesh1->initOBJ("assets/susanne.obj");
	tempMesh1->setPosition(-1.5, 0.0, 0.0);
	tempMesh1->setTexture("assets/textures/monkey_tex.png");
	// Mesh 2
	tempMesh2->initOBJ("assets/bunny.obj");
	tempMesh2->setPosition(1.5, 0.0, 0.0);
	tempMesh2->setTexture("assets/textures/bunny_tex.png");

	meshes.push_back(tempMesh1);
	meshes.push_back(tempMesh2);
}

Scene::~Scene()
{
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

std::vector<Mesh*> Scene::getMeshes()
{
	return meshes;
}

void Scene::render(GLFWwindow* window)
{
	do
	{
		// Clear the screen and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for(int i = 0; i < meshes.size(); ++i)
		{
			meshes[i]->render();
		}

		// Render the AntTweakBar
		TwDraw();

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );
}
