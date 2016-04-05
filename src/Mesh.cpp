#include "../include/Mesh.h"

Mesh::Mesh()
{
		
}

Mesh::~Mesh()
{
	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	if(uvbuffer){
		glDeleteBuffers(1, &uvbuffer);
	}

	glDeleteVertexArrays(1, &vertexArrayID);
}

void Mesh::initCube(float size)
{	
	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	vertices.resize(36);
	vertices[0]  = glm::vec3(-size, -size, -size);
	vertices[1]  = glm::vec3(-size, -size,  size);
	vertices[2]  = glm::vec3(-size,  size,  size);
	vertices[3]  = glm::vec3( size,  size, -size);
	vertices[4]  = glm::vec3(-size, -size, -size);
	vertices[5]  = glm::vec3(-size,  size, -size);
	vertices[6]  = glm::vec3( size, -size,  size);
	vertices[7]  = glm::vec3(-size, -size, -size);
	vertices[8]  = glm::vec3( size, -size, -size);
	vertices[9]  = glm::vec3( size,  size, -size);
	vertices[10] = glm::vec3( size, -size, -size);
	vertices[11] = glm::vec3(-size, -size, -size);
	vertices[12] = glm::vec3(-size, -size, -size);
	vertices[13] = glm::vec3(-size,  size,  size);
	vertices[14] = glm::vec3(-size,  size, -size);
	vertices[15] = glm::vec3( size, -size,  size);
	vertices[16] = glm::vec3(-size, -size,  size);
	vertices[17] = glm::vec3(-size, -size, -size);
	vertices[18] = glm::vec3(-size,  size,  size);
	vertices[19] = glm::vec3(-size, -size,  size);
	vertices[20] = glm::vec3( size, -size,  size);
	vertices[21] = glm::vec3( size,  size,  size);
	vertices[22] = glm::vec3( size, -size, -size);
	vertices[23] = glm::vec3( size,  size, -size);
	vertices[24] = glm::vec3( size, -size, -size);
	vertices[25] = glm::vec3( size,  size,  size);
	vertices[26] = glm::vec3( size, -size,  size);
	vertices[27] = glm::vec3( size,  size,  size);
	vertices[28] = glm::vec3( size,  size, -size);
	vertices[29] = glm::vec3(-size,  size, -size);
	vertices[30] = glm::vec3( size,  size,  size);
	vertices[31] = glm::vec3(-size,  size, -size);
	vertices[32] = glm::vec3(-size,  size,  size);
	vertices[33] = glm::vec3( size,  size,  size);
	vertices[34] = glm::vec3(-size,  size,  size);
	vertices[35] = glm::vec3( size, -size,  size);

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
  
  	glGenBuffers(1, &vertexbuffer);
  	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  	glBufferData(GL_ARRAY_BUFFER,
    			 vertices.size() * sizeof(glm::vec3),
    			 &vertices[0],
    			 GL_STATIC_DRAW);
}

void Mesh::initOBJ(const char* filename)
{
	// Read our .obj file
	bool res = loadObj(filename, vertices, uvs, normals);
	
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);	

}

GLuint Mesh::getVertexArrayID()
{
	return vertexArrayID;
}

GLuint Mesh::getVertexbuffer()
{
	return vertexbuffer;
}