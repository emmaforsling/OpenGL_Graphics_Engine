#include "../include/Mesh.h"

Mesh::Mesh()
{
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "shaders/vertexshader.glsl", "shaders/fragmentshader.glsl" );

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");

	modelMatrix = glm::mat4(1.0);

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

	//glGenVertexArrays(1, &vertexArrayID);
	//glBindVertexArray(vertexArrayID);
  
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
	
	// Vertices
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	// Normals
	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	
	// UVs
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);	
}

void Mesh::render()
{
	// Use our shader
	glUseProgram(programID);

	// Compute the MVP matrix from keyboard and mouse input
	computeMatricesFromInputs();
	glm::mat4 ProjectionMatrix = getProjectionMatrix();
	glm::mat4 ViewMatrix = getViewMatrix();
	modelViewProjectionMatrix = ProjectionMatrix * ViewMatrix * modelMatrix;

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &modelViewProjectionMatrix[0][0]);

	glUniform1i(Texture, TextureID);

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	
	if(normalBuffer)
	{
		// 2nd attribute buffer : normals
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glVertexAttribPointer(
			1,                  // attribute 1
			3,                  // size
			GL_FLOAT,           // type
			GL_TRUE,            // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
	}

	if(uvbuffer)
	{
		// 3rd attribute buffer : UVs
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			2,                                // attribute 2
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
	}

	// Bind the texture of the object
	glBindTexture(GL_TEXTURE_2D, Texture);

	// Draw the triangles!
	glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

	glDisableVertexAttribArray(0);

	// Unbind the texture so that it is not used for other objects as well.
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::setPosition(float _x, float _y, float _z)
{
	modelMatrix = glm::translate(modelMatrix, glm::vec3(_x, _y, _z));
	modelViewProjectionMatrix = getProjectionMatrix() * getViewMatrix() * modelMatrix;
}

void Mesh::setTexture(std::string _filename)
{
	const char* filename = _filename.c_str();
	int texHeight = 512;
	int texWidth  = 512;
	
	// Load the texture
	Texture = png_texture_load(filename, &texWidth , &texHeight);
	
	// Get a handle for our "myTextureSampler" uniform
	TextureID  = glGetUniformLocation(programID, "myTextureSampler");
}

GLuint Mesh::png_texture_load(const char * file_name, int * width, int * height)
{
    // This function was originally written by David Grayson for
    // https://github.com/DavidEGrayson/ahrs-visualizer

	// Header (to check if it is a png)
    png_byte header[8];

    // Open file as binary
    FILE *fp = fopen(file_name, "rb");
    if (fp == 0)
    {
        std::cout << "Error, file name" << file_name << std::endl;
        return 0;
    }

    // Read the header
    fread(header, 1, 8, fp);

    // Test if it is a png
    if (png_sig_cmp(header, 0, 8))
    {
        std::cout << "error:" << file_name << "is not a PNG." << std::endl;
        fclose(fp);
        return 0;
    }

    // create png struct
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr)
    {
        std::cout <<  "error: png_create_read_struct returned 0." << std::endl;
        fclose(fp);
        return 0;
    }

    // create png info struct
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        std::cout << "error: png_create_info_struct returned 0" << std::endl;
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        fclose(fp);
        return 0;
    }

    // create png info struct
    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info)
    {
        std::cout <<  "error: png_create_info_struct returned 0." << std::endl;
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
        fclose(fp);
        return 0;
    }

    // the code in this if statement gets called if libpng encounters an error
    if (setjmp(png_jmpbuf(png_ptr))) {
        std::cout << "error from libpng" << std::endl;
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return 0;
    }

    // init png reading
    png_init_io(png_ptr, fp);

    // let libpng know you already read the first 8 bytes
    png_set_sig_bytes(png_ptr, 8);

    // read all the info up to the image data
    png_read_info(png_ptr, info_ptr);

    // variables to pass to get info
    int bit_depth, color_type;
    png_uint_32 temp_width, temp_height;

    // get info about png
    png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type,
        NULL, NULL, NULL);

    if (width){ *width = temp_width; }
    if (height){ *height = temp_height; }

    //printf("%s: %lux%lu %d\n", file_name, temp_width, temp_height, color_type);

    if (bit_depth != 8)
    {
        std::cout << file_name << "Unsupported bit depth." << bit_depth << "Must be 8." << std::endl;
        return 0;
    }

    GLint format;
    switch(color_type)
    {
    case PNG_COLOR_TYPE_RGB:
        format = GL_RGB;
        break;
    case PNG_COLOR_TYPE_RGB_ALPHA:
        format = GL_RGBA;
        break;
    default:
        std::cout << file_name << " Unknown libpng color type "<< color_type << std::endl;
        return 0;
    }

    // Update the png info struct.
    png_read_update_info(png_ptr, info_ptr);

    // Row size in bytes.
    int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

    // glTexImage2d requires rows to be 4-byte aligned
    rowbytes += 3 - ((rowbytes-1) % 4);

    // Allocate the image_data as a big block, to be given to opengl
    png_byte * image_data = (png_byte *)malloc(rowbytes * temp_height * sizeof(png_byte)+15);
    if (image_data == NULL)
    {
        std::cout << "error: could not allocate memory for PNG image data" << std::endl;
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return 0;
    }

    // row_pointers is for pointing to image_data for reading the png with libpng
    png_byte ** row_pointers = (png_byte **)malloc(temp_height * sizeof(png_byte *));
    if (row_pointers == NULL)
    {
        std::cout << "error: could not allocate memory for PNG row pointers" << std::endl;
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        free(image_data);
        fclose(fp);
        return 0;
    }

    // set the individual row_pointers to point at the correct offsets of image_data
    for (unsigned int i = 0; i < temp_height; i++)
    {
        row_pointers[temp_height - 1 - i] = image_data + i * rowbytes;
    }

    // read the png into image_data through row_pointers
    png_read_image(png_ptr, row_pointers);

    // Generate the OpenGL texture object
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, format, temp_width, temp_height, 0, format, GL_UNSIGNED_BYTE, image_data);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // clean up
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    free(image_data);
    free(row_pointers);
    fclose(fp);
    
    return texture;
}
