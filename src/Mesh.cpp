#include "../include/Mesh.h"

/**
* Default constructor
**/
Mesh::Mesh()
{
	// Default values
	tessellationEnabled = false;
	k_diff = 0.0;
	k_spec = 0.0;
	specPow = 0.0;

	// Initialize model matrix
	modelMatrix = glm::mat4(1.0);
}

/**
* Destructor that cleanups the VBO
**/
Mesh::~Mesh()
{
	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	if(uvbuffer){
		glDeleteBuffers(1, &uvbuffer);
	}

	glDeleteVertexArrays(1, &vertexArrayID);
}

/**************************	Init functions **************************/
/**
*	Function that loads source files and creates a shader program.
*				(vertex and fragment)
**/
void Mesh::initShaders(const char* _vertex_file_path, const char* _fragment_file_path)
{
	// Create and compile our GLSL program from the shaders
	ShaderHandler* shader = new ShaderHandler(_vertex_file_path, _fragment_file_path);
	programID = shader->createProgram();

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");
}

/**
*	Function that loads source files and creates a shader program.
*				(vertex, fragment and geometry)
**/
void Mesh::initShaders(const char* _vertex_file_path, const char* _fragment_file_path, const char* _geometry_file_path)
{
	// Create and compile our GLSL program from the shaders
	ShaderHandler* shader = new ShaderHandler(_vertex_file_path, _fragment_file_path, _geometry_file_path);
	programID = shader->createProgram();

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");
}

/**
*	Function that loads source files and creates a shader program.
*				(tessellation shader)
**/
void Mesh::initShaders( const char* _vertex_file_path,
                   		const char* _tessellation_control_file_path,
                   		const char* _tessellation_evaluation_file_path,
                   		const char* _geometry_file_path,
                   		const char* _fragment_file_path)
{
	// Create and compile our GLSL program from the shaders
	ShaderHandler* shader = new ShaderHandler(	_vertex_file_path, 
												_tessellation_control_file_path, 
												_tessellation_evaluation_file_path,
												_geometry_file_path,
												_fragment_file_path);
	programID = shader->createProgram();

	// 
	tessellationEnabled = true;

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");
}

/**
*	 Funcion that creates a cube
**/
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

/**
*	Function that loads and creates an object
**/
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

/**************************	Object operations **************************/
void Mesh::setMaterialProperties(float _k_diff, float _k_spec, float _specPow)
{
	k_diff = _k_diff;
	k_spec = _k_spec;
	specPow = _specPow;
}

void Mesh::scaleObject(float _scale)
{
	modelMatrix = glm::scale(modelMatrix, glm::vec3(_scale));
}

void Mesh::setPosition(float _x, float _y, float _z)
{
	modelMatrix = glm::translate(modelMatrix, glm::vec3(_x, _y, _z));
	//modelViewProjectionMatrix = getProjectionMatrix() * getViewMatrix() * modelMatrix;
}

/**************************	Uniform tools **************************/
/**
*	Function that adds an integer uniform to the shader
**/
void Mesh::Mesh::addIntegerUniform(const char* _name, GLuint _value)
{
	integerUniform tempUniform = integerUniform();
	tempUniform.name = _name;
	tempUniform.value = _value;
	integerUniforms.push_back(tempUniform);
}

/**
*	Function that adds a float uniform to the shader
**/
void Mesh::addFloatUniform(const char* _name, GLfloat _value)
{
	floatUniform tempUniform = floatUniform();
	tempUniform.name = _name;
	tempUniform.value = _value;
	floatUniforms.push_back(tempUniform);
}

/**
*	Function that adds a vec3 uniform to the shader
**/
void Mesh::addVec3Uniform(const char* _name, GLfloat* _value)
{
	vec3Uniform tempUniform = vec3Uniform();
	tempUniform.name = _name;
	tempUniform.value = _value;
	vec3Uniforms.push_back(tempUniform);
}

/**
*	Function that adds a matrix4x4 uniform to the shader
**/
void Mesh::addMat4Uniform(const char* _name, GLfloat* _value)
{
	mat4Uniform tempUniform = mat4Uniform();
	tempUniform.name = _name;
	tempUniform.value = _value;
	mat4Uniforms.push_back(tempUniform);
}

/**
*	Function that adds a texture uniform to the shader
**/
void Mesh::addTextureUniform(GLuint _texUnit, GLuint _texData, const char* _name, GLfloat _value)
{
	textureUniform tempUniform = textureUniform();
	tempUniform.texUnit = _texUnit;
	tempUniform.texData = _texData;
	tempUniform.name = _name;
	tempUniform.value = _value;
	textureUniforms.push_back(tempUniform);
}

/**
*	Function that updates a float uniform 
**/
void Mesh::updateFloatUniform(const char* _name, GLfloat _value)
{
	for(int i = 0; i < floatUniforms.size(); ++i)
	{
		if(floatUniforms[i].name == _name)
		{
			floatUniforms[i].value = _value;
		}
	}
}

/**
*	Function that updates an integer uniform 
**/
void Mesh::updateIntegerUniform(const char* _name, GLuint _value)
{
	for(int i = 0; i < integerUniforms.size(); ++i)
	{
		if(integerUniforms[i].name == _name)
		{
			integerUniforms[i].value = _value;
		}
	}
}

/**
*	Render function
**/
void Mesh::render(Camera* camera)
{
	// Use our shader
	glUseProgram(programID);

	modelViewProjectionMatrix = camera->getProjectionMatrix() * camera->getViewMatrix() * modelMatrix;

	// Compute the MVP matrix from keyboard and mouse input
	camera->computeMatricesFromInputs();
	glm::mat4 ProjectionMatrix = camera->getProjectionMatrix();
	glm::mat4 ViewMatrix = camera->getViewMatrix();
	modelViewProjectionMatrix = ProjectionMatrix * ViewMatrix * modelMatrix;

	// Upload integer uniforms
	for(int i = 0; i < integerUniforms.size(); ++i)
	{
		uploadIntegerUniform(integerUniforms[i]);
	}

	// Upload float uniforms
	for(int i = 0; i < floatUniforms.size(); ++i)
	{
		uploadFloatUniform(floatUniforms[i]);
	}

	// Upload vec3 uniforms
	for(int i = 0; i < vec3Uniforms.size(); ++i)
	{
		uploadVec3Uniform(vec3Uniforms[i]);
	}
	
	// Upload mat4 uniforms
	for(int i = 0; i < mat4Uniforms.size(); ++i)
	{
		uploadMat4Uniform(mat4Uniforms[i]);
	}

	// Upload texture uniforms
	for(int i = 0; i < textureUniforms.size(); ++i)
	{
		uploadTextureUniform(textureUniforms[i]);
	}

	// Upload float uniforms
	for(int i = 0; i < floatUniforms.size(); ++i)
	{
		uploadFloatUniform(floatUniforms[i]);
	}

	// Transformation matrices
	glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, &modelViewProjectionMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "M"), 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "V"), 1, GL_FALSE, &ViewMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "P"), 1, GL_FALSE, &ProjectionMatrix[0][0]);

	// Upload material properties
	glUniform1f(glGetUniformLocation(programID, "k_diff"), k_diff);
	glUniform1f(glGetUniformLocation(programID, "k_spec"), k_spec);
	glUniform1f(glGetUniformLocation(programID, "specPow"), specPow);
	
	// Upload camera position
	glUniform3fv(glGetUniformLocation(programID, "cameraPos_ws"), 1, glm::value_ptr(camera->getCameraPosition()));

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,						// attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,						// size
		GL_FLOAT,				// type
		GL_FALSE,				// normalized?
		0,						// stride
		(void*)0				// array buffer offset
	);

	
	if(normalBuffer)
	{
		// 2nd attribute buffer : normals
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glVertexAttribPointer(
			1,					// attribute 1
			3,					// size
			GL_FLOAT,			// type
			GL_TRUE,			// normalized?
			0,					// stride
			(void*)0			// array buffer offset
		);
	}

	if(uvbuffer)
	{
		// 3rd attribute buffer : UVs
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			2,					// attribute 2
			2,					// size
			GL_FLOAT,			// type
			GL_FALSE,			// normalized?
			0,					// stride
			(void*)0			// array buffer offset
		);
	}

	if(tessellationEnabled)
	{
		glPatchParameteri(GL_PATCH_VERTICES, 3);
		// Draw the patches!
		glDrawArrays(GL_PATCHES, 0, vertices.size() );
	}
	else
	{
		// Draw the triangles!
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() );	
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//glDisableVertexAttribArray(2);

	// Unbind the texture so that it is not used for other objects as well.
	glBindTexture(GL_TEXTURE_2D, 0);
}

/**************************	Texture functions **************************/
void Mesh::setDispMap(std::string _filename, int _texHeight, int _texWidth)
{
	const char* filename = _filename.c_str();

	// Load the texture
	tex_dispMap = png_texture_load(filename, &_texWidth , &_texHeight);
	
	// Get a handle for our "dispMap" uniform
	handle_dispMap = glGetUniformLocation(programID, "dispMap");

	addTextureUniform(GL_TEXTURE0, tex_dispMap, "dispMap", 0);
}

void Mesh::setNormMap(std::string _filename, int _texHeight, int _texWidth)
{
	const char* filename = _filename.c_str();
	
	// Load the texture
	tex_normMap = png_texture_load(filename, &_texWidth , &_texHeight);
	
	// Get a handle for our "dispMap" uniform
	handle_normMap = glGetUniformLocation(programID, "normMap");

	addTextureUniform(GL_TEXTURE1, tex_normMap, "normMap", 1);
}

void Mesh::setColorMap(std::string _filename, int _texHeight, int _texWidth)
{
	const char* filename = _filename.c_str();
	
	// Load the texture
	tex_colorMap = png_texture_load(filename, &_texWidth , &_texHeight);
	
	// Set the handle for the "dispMap" uniform
	handle_colorMap = glGetUniformLocation(programID, "colorMap");

	addTextureUniform(GL_TEXTURE2, tex_colorMap, "colorMap", 2);
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


/**************************	Private uniform functions **************************/
void Mesh::uploadIntegerUniform(integerUniform _uniform)
{
	glUniform1i(glGetUniformLocation(programID, _uniform.name), _uniform.value);
}

void Mesh::uploadFloatUniform(floatUniform _uniform)
{
	glUniform1f(glGetUniformLocation(programID, _uniform.name), _uniform.value);
}

void Mesh::uploadVec3Uniform(vec3Uniform _uniform)
{
	glUniform3fv(glGetUniformLocation(programID, _uniform.name), 1, _uniform.value);
}

void Mesh::uploadMat4Uniform(mat4Uniform _uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(programID, _uniform.name), 1, GL_FALSE, _uniform.value);
}

void Mesh::uploadTextureUniform(textureUniform _uniform)
{
	glActiveTexture(_uniform.texUnit); 
	glBindTexture(GL_TEXTURE_2D, _uniform.texData);
	glUniform1i(glGetUniformLocation(programID, _uniform.name), _uniform.value);
}
