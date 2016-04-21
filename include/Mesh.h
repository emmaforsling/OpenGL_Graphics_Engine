#ifndef Mesh_H
#define Mesh_H

// Standard includes
#include <iostream>
#include <vector>
// #include <map>
// #include <algorithm>
#include <png.h>

// OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Source includes
#include "utils/ObjectLoader.h"
#include "../include/utils/ShaderManager.h"
#include "../include/utils/controls.h"

// GLM includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define TYPE_INTEGER 	0
#define TYPE_FLOAT		1
#define TYPE_VEC3		2
#define TYPE_MAT4		3
#define TYPE_TEXTURE	4

class Mesh
{
public:	
	// Constructor
	Mesh();
	// Destructor
	~Mesh();

	// Init functions
	void initShaders(const char* vertexShader_filename, const char* fragmentShader_filename);
	void initCube(float size);
	void initOBJ(const char* filename);



	void setProgramID(GLuint _programID){
		programID = _programID;
		// Get a handle for our "MVP" uniform
		MatrixID = glGetUniformLocation(programID, "MVP");
	};
	// Get functions
	GLuint getVertexArrayID(){ return vertexArrayID; };
	GLuint getVertexbuffer(){ return vertexbuffer; };
	GLuint getNormalBuffer(){ return normalBuffer; };
	GLuint getUvBuffer(){ return uvbuffer; };
	int getVerticesLength(){ return vertices.size(); };

	float getTessellationScale(){return tessScale;};
	void setTessellationScale(float _tessScale){tessScale = _tessScale;};

	// Object operations
	void setPosition(float _x, float _y, float _z);
	void setMaterialProperties(float k_diff, float k_spec, float _specPow);
	void scaleObject(float _size);

	// Uniform tools
	void addIntegerUniform(const char* _name, GLuint _value);
	void addFloatUniform(const char* _name, GLfloat _value);
	void addVec3Uniform(const char* _name, GLfloat* _value);
	void addMat4Uniform(const char* _name, GLfloat* _value);
	void addTextureUniform(GLuint _texUnit, GLuint _texData, const char* _name, GLfloat _value);
	void updateFloatUniform(const char* _name, GLfloat _value);

	// Render functions
	void render();

	// Texture functions
	void setDispMap(std::string _filename);
	void setNormMap(std::string _filename);
	void setColorMap(std::string _filename);
	void setIsTessellationActive(bool _tessellation){tessellation = _tessellation;};
	GLuint png_texture_load(const char * file_name, int * width, int * height);

private:
	GLuint vertexArrayID;
	GLuint vertexbuffer;
	GLuint normalBuffer;
	GLuint uvbuffer;
	GLuint programID;
	GLuint MatrixID;

	struct integerUniform
	{
    	const char* name;
    	GLuint value;
	};
	
	struct floatUniform
	{
    	const char* name;
    	GLfloat value;
	};

	struct vec3Uniform
	{
    	const char* name;
    	GLfloat* value;
	};
	
	struct mat4Uniform
	{
    	const char* name;
    	GLfloat* value;
	};
	
	struct textureUniform
	{
		GLuint texUnit;
		GLuint texData;
		const char* name;
		GLuint value;
	};

	std::vector<integerUniform> integerUniforms;
	std::vector<floatUniform> 	floatUniforms;
	std::vector<vec3Uniform> 	vec3Uniforms;
	std::vector<mat4Uniform> 	mat4Uniforms;
	std::vector<textureUniform> textureUniforms;
	
	// Textures
	GLuint tex_dispMap;
	GLuint tex_normMap;
	GLuint tex_colorMap;
	GLuint handle_dispMap;
	GLuint handle_normMap;
	GLuint handle_colorMap;

	// Matrices
	glm::mat4 modelMatrix;
	glm::mat4 modelViewProjectionMatrix;

	// Data
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	// Material properties
	float k_diff;
	float k_spec;
	float specPow;

	// Tesselation
	float tessScale;

	bool tessellation;

	// Uniform functions
	void uploadIntegerUniform(integerUniform _uniform);
	void uploadFloatUniform(floatUniform _uniform);
	void uploadVec3Uniform(vec3Uniform _uniform);
	void uploadMat4Uniform(mat4Uniform _uniform);
	void uploadTextureUniform(textureUniform _uniform);
};

#endif