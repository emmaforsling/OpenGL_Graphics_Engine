#ifndef CAMERA_H
#define CAMERA_H

// GLM includes
#include <glm/glm.hpp>

class Camera{
public:
	// Constructor
	Camera(glm::vec3 _cameraPosition = glm::vec3(0.0,0.0,5.0));

	// Destructor
	~Camera() = default;

	// Set functions
	void setPosition(glm::vec3 _cameraPosition){cameraPosition = _cameraPosition;};

	// Get functions
	glm::vec3 getPosition(){ return cameraPosition;};


private:
	glm::vec3 cameraPosition;
};


#endif