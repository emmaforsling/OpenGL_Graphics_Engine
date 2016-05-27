#ifndef CAMERA_H
#define CAMERA_H

// Standard includes
#include <iostream>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.
using namespace glm;

class Camera{
public:
	// Constructor
	Camera();
	// Destructor
	~Camera();

	// Get functions
	glm::mat4 getViewMatrix(){return ViewMatrix;}
	glm::mat4 getProjectionMatrix(){return ProjectionMatrix;}
	glm::vec3 getCameraPosition(){return position;}

	// Update position, viewmatrix and projectionmatrix
	void computeMatricesFromInputs();

private:
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
	glm::vec3 position;
	
	float horizontalAngle;
	float verticalAngle;
	float initialFoV;
	float speed;
	float mouseSpeed;
	double xpos_old;
	double ypos_old;

};

#endif