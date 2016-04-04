#ifndef SCENE_H
#define SCENE_H

#include "../include/Camera.h"

class Scene{
public:
	// Constructor
	Scene();
	// Destructor
	~Scene() = default;

private:
	Camera* camera = nullptr;
};

#endif