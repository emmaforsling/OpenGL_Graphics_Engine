#include "../include/Scene.h"

Scene::Scene()
{
	camera = new Camera();

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	geometries = std::vector<Geometry*>();

	Geometry* tempGeom = new Geometry();
	geometries.push_back(tempGeom);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "shaders/vertexshader.glsl", "shaders/fragmentshader.glsl" );
}

Scene::~Scene()
{
	for(int i = 0; i < geometries.size(); ++i)
	{
		if(geometries[i])
		{
			delete geometries[i];
		}
	}
	std::cout << "Geometries deleted" << std::endl;
	
	glDeleteProgram(programID);
}

std::vector<Geometry*> Scene::getGeometries()
{
	return geometries;
}

void Scene::render(GLFWwindow* window)
{
	do
	{
		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );

		// Render the AntTweakBar
		TwDraw();

		// Use our shader
		glUseProgram(programID);

		// 1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, geometries.at(0)->getVertexbuffer());
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );
}