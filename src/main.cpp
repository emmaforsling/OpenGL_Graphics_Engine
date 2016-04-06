// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM includes
#include <glm/glm.hpp>
using namespace glm;

// AntTweakBar includes
#include <AntTweakBar.h>

// Source includes
#include "../include/Scene.h"

// Functions
bool initOpenGL(void);
bool initScene(void);
void initAntTweakBar(void);

// Controls
void magicTwMouseButtonWrapper(GLFWwindow *, int, int, int);
void magicTwMouseHoverWrapper(GLFWwindow *, double, double);
void myFunction(void *clientData);

// Variables
GLFWwindow* window;
Scene* scene;
TwBar* tweakbar;

// Constants
#define WIDTH 1024
#define HEIGHT 768

int main(void)
{
	if(!initOpenGL())
	{
		return -1;
	}
	
	// Initialize the scene
	initScene();

	// Initialize the AntTweakBar window 
	initAntTweakBar();

	// Render the window
	do
	{
		scene->render(window);
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Remove AntTweakBar
    TwTerminate();

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

bool initOpenGL(void)
{
	// Initialise GLFW
	if(!glfwInit())
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Projekt okänt", NULL, NULL);
	if( window == NULL )
	{
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if(glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return false;
	}
	return true;
}

bool initScene(void)
{
	// Initialize scene
	scene = new Scene();

	// Create and add a mesh to the scene
	Mesh* tempMesh1 = new Mesh();
	tempMesh1->initOBJ("assets/susanne.obj");
	tempMesh1->setTexture("assets/textures/monkey_tex.png");
	tempMesh1->setMaterialProperties(0.85, 0.15);	// diffuse and specular coefficients
	tempMesh1->setPosition(-1.5, 0.0, 0.0);
	scene->addMesh(tempMesh1);

	// Create and add a mesh to the scene
	Mesh* tempMesh2 = new Mesh();
	tempMesh2->initOBJ("assets/bunny.obj");
	tempMesh2->setTexture("assets/textures/bunny_tex.png");
	tempMesh2->setMaterialProperties(0.50, 0.50);	// diffuse and specular coefficients
	tempMesh2->setPosition(1.5, 0.0, 0.0);
	scene->addMesh(tempMesh2);
}

/****************************** <AntTweakBar> *********************************/

float testVariable = 10.0f;
/**
 *   Initialize the AntTweakBar window and add its variables
**/
void initAntTweakBar(void)
{
    // Scale the font, since AntTweakBar doesn't like retina displays
    TwDefine(" GLOBAL fontscaling=2 ");

    // Initialize AntTweakBar
    TwInit(TW_OPENGL_CORE, NULL);       // for core profile

    // Set the size of the graphic window
    TwWindowSize(WIDTH * 1.96, HEIGHT * 1.96);			// for mac retina 13
    // TwWindowSize(WIDTH * 1.99, HEIGHT * 1.99);			// for mac retina 15

    // // Create a new tweak bar (by calling TWNewBar) and set its size
    tweakbar = TwNewBar("Emma");
    TwDefine("Emma size='400 700'");

    /**
    * Add variables to the tweak bar
    **/
    TwAddVarRW( tweakbar,           		// my tweak bar
            	"That's Me",          		// name of my variable
            	TW_TYPE_FLOAT,      		// tweak bar type
            	&testVariable,       		// my variable
           		"min=0 max=2 step=0.05 help=':D'" 
           		);

    TwAddVarRW( tweakbar,           		// my tweak bar
            	"Martin",        			// name of my variable
            	TW_TYPE_FLOAT,      		// tweak bar type
            	&testVariable,       		// my variable
           		" group='Stockholm' label='Martin' min=0 max=2 step=0.05 help='man' "
           		);

    TwAddButton( tweakbar, 
    			 "comment1",
    			 &myFunction,
    			 NULL,
    			 " label='Life is like a box a chocolates' "
    			 ); 
	
	glfwSetMouseButtonCallback(window, magicTwMouseButtonWrapper);
    glfwSetCursorPosCallback(window, magicTwMouseHoverWrapper);

}

void myFunction(void *clientData)
{
	std::cout << "Hej på mig igen " << std::endl;	
}

void magicTwMouseButtonWrapper(GLFWwindow* window, int button, int action, int mods)
{
 	TwEventMouseButtonGLFW(button, action);
}

void magicTwMouseHoverWrapper(GLFWwindow * window, double x, double y)
{
    TwEventMousePosGLFW(x * 2, y * 2);
}

/****************************** </AntTweakBar> *********************************/
