#include "../include/ShaderHandler.h"

// OpenGL includes
#include <GL/glew.h>

/**
* Standard constructor
**/
ShaderHandler::ShaderHandler(	const char* _vertex_file_path,
				const char* _fragment_file_path) 
{
	// Add the different shaders to the vector shaders<Shader>
	initVertexShader(_vertex_file_path);
	initFragmentShader(_fragment_file_path);
	
	// Loop through the added shaders and load and compile them.
	for(int i = 0; i < shaders.size(); ++i)
	{
		loadShader(shaders[i].file_path, shaders[i].shaderID);
	}
}

/**
* Tessellation constructor
**/
ShaderHandler::ShaderHandler(	const char* _vertex_file_path,
                   				const char* _tessellation_control_file_path,
                   				const char* _tessellation_evaluation_file_path,
                   				const char* _geometry_file_path,
                   				const char* _fragment_file_path )
{
	// Add the different shaders to the vector shaders<Shader>
	initVertexShader(_vertex_file_path);
	initTessControlShader(_tessellation_control_file_path);
	initTessEvalShader(_tessellation_evaluation_file_path);
	initGeometryShader(_geometry_file_path);
	initFragmentShader(_fragment_file_path);

	// Loop through the added vector, and load and compile them.
	for(int i = 0; i < shaders.size(); ++i)
	{
		loadShader(shaders[i].file_path, shaders[i].shaderID);
	}
}

/**
 *	Initialize the different shaders and add them to the shaders vector.
 **/
void ShaderHandler::initVertexShader(const char* _file_path)
{
	Shader newShader = Shader();
	newShader.file_path = _file_path;
	newShader.shaderID = glCreateShader(GL_VERTEX_SHADER);
	shaders.push_back(newShader);
}

void ShaderHandler::initTessControlShader(const char* _file_path)
{
	Shader newShader = Shader();
	newShader.file_path = _file_path;
	newShader.shaderID = glCreateShader(GL_TESS_CONTROL_SHADER);
	shaders.push_back(newShader);
}

void ShaderHandler::initTessEvalShader(const char* _file_path)
{
	Shader newShader = Shader();
	newShader.file_path = _file_path;
	newShader.shaderID = glCreateShader(GL_TESS_EVALUATION_SHADER);
	shaders.push_back(newShader);
}

void ShaderHandler::initGeometryShader(const char* _file_path)
{
	Shader newShader = Shader();
	newShader.file_path = _file_path;
	newShader.shaderID = glCreateShader(GL_GEOMETRY_SHADER);
	shaders.push_back(newShader);
}

void ShaderHandler::initFragmentShader(const char* _file_path)
{
	Shader newShader = Shader();
	newShader.file_path = _file_path;
	newShader.shaderID = glCreateShader(GL_FRAGMENT_SHADER);
	shaders.push_back(newShader);
}

/**
* Function that loads and compiles a shader
**/
void ShaderHandler::loadShader(const char* _file_path, GLuint _shaderID)
{
	std::string shaderCode;
	std::ifstream shaderStream(_file_path, std::ios::in);
	if(shaderStream.is_open())
	{
		std::string Line = "";
		while(getline(shaderStream, Line))
			shaderCode += "\n" + Line;
		shaderStream.close();
	}
	else
	{
		printf("Impossible to open %s. Are you in the right directory? !\n", _file_path);
		getchar();
	}

	// Compile Shader
	printf("Compiling shader : %s\n", _file_path);
	char const * sourcePointer = shaderCode.c_str();
	glShaderSource(_shaderID, 1, &sourcePointer , NULL);
	glCompileShader(_shaderID);

	// Check Shader
	glGetShaderiv(_shaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(_shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 )
	{
		std::vector<char> shaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(_shaderID, InfoLogLength, NULL, &shaderErrorMessage[0]);
		printf("%s\n", &shaderErrorMessage[0]);
	}
}

void ShaderHandler::deleteShaders()
{
	// Loop through the shaders vector and remove them.
	for(int i = 0; i < shaders.size(); ++i)
	{
		glDeleteShader(shaders[i].shaderID);
	}
}

GLuint ShaderHandler::createProgram()
{
	// Link the program
	printf("Linking program\n");
	GLuint programID = glCreateProgram();
	
	// Loop through the added shaders and attach them to the programID
	for(int i = 0; i < shaders.size(); ++i)
	{
		glAttachShader(programID,shaders[i].shaderID);	
	}
	glLinkProgram(programID);

	// Check the program
	glGetProgramiv(programID, GL_LINK_STATUS, &Result);
    	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    	if ( InfoLogLength > 0 )
    	{
        	std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        	glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        	printf("%s\n", &ProgramErrorMessage[0]);
    	}
	
	// Delete the shaders
    	deleteShaders();
    	
    	return programID;
}



















