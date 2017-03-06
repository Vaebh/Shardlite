#include "ShaderCache.h"
#include <fstream>

#include <iostream>

using std::string;

int ShaderCache::_latestId = -1;

const string DEFAULT_VERT_SHADER = "Assets/Shaders/VertexShader.txt";
const string DEFAULT_FRAG_SHADER = "Assets/Shaders/FragShader.txt";
const string DEFAULT_TESSELATION_CONTROL_SHADER = "Assets/Shaders/TessControl.txt";
const string DEFAULT_TESSELATION_EVALUATION_SHADER = "Assets/Shaders/TessEval.txt";
const string DEFAULT_GEOMETRY_SHADER = "Assets/Shaders/GeometryShader.txt";

const GLuint _posAttrLoc = 0;
const GLuint _texCoordsAttrLoc = 1;
const GLuint _colAttrLoc = 2;
const GLuint _normalAttrLoc = 3;

namespace
{
	const string AllowedAttributes[] = 
	{
		"vec3 position",
		"vec3 colour",
		"vec3 texCoords",
		"vec3 normal"
	};

	const string AllowedUniforms[] =
	{
		"Model",
		"View",
		"Projection"
	};


	std::string LoadShaderFromFile(const std::string& in_path)
	{
		std::string shaderSrc = "";
		std::ifstream myFile;

		myFile.open(in_path);
		if (myFile.is_open() && !myFile.bad())
		{
			return shaderSrc.assign(std::istreambuf_iterator<char>(myFile), std::istreambuf_iterator<char>());
		}

		return "";
	}

	GLuint CreateShaderFromFile(const std::string& in_path, const GLenum& in_shaderType)
	{
		// Get the shader
		std::string shaderSrcString = LoadShaderFromFile(in_path);

		if (shaderSrcString.empty())
		{
			return 0;
		}
        
#ifdef __APPLE__
        shaderSrcString = "#version 410\n" + shaderSrcString;
#endif
        
#ifdef __WINDOWS__
        shaderSrcString = "#version 450\n" + shaderSrcString;
#endif

		const GLchar* shaderSrc = shaderSrcString.c_str();

		// Loading Vertex Shader
		GLuint shader = glCreateShader(in_shaderType);
		glShaderSource(shader, 1, &shaderSrc, NULL);
		glCompileShader(shader);

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_TRUE)
			std::cout << "shader compile success" << std::endl;
		else
			std::cout << "shader compile fail" << std::endl;

		return shader;
	}

	void DeleteShader(GLuint in_shader, GLuint shaderProgram)
	{
		glDetachShader(shaderProgram, in_shader);
		glDeleteShader(in_shader);
	}
}

ShaderCache::ShaderCache() {

}

ShaderCache::~ShaderCache() {

}

void ShaderCache::Init() {
	AddShader(DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER);
}

int ShaderCache::AddShader(std::string vertexShaderName, std::string fragShaderName) {
	GLuint vertexShader = CreateShaderFromFile(vertexShaderName, GL_VERTEX_SHADER);
	//GLuint tessControlShader = CreateShaderFromFile(DEFAULT_TESSELATION_CONTROL_SHADER, GL_TESS_CONTROL_SHADER);
	//GLuint tessEvalShader = CreateShaderFromFile(DEFAULT_TESSELATION_EVALUATION_SHADER, GL_TESS_EVALUATION_SHADER);
	//GLuint geometryShader = CreateShaderFromFile(DEFAULT_GEOMETRY_SHADER, GL_GEOMETRY_SHADER);
	GLuint fragShader = CreateShaderFromFile(fragShaderName, GL_FRAGMENT_SHADER);
	

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, tessControlShader);
	//glAttachShader(shaderProgram, tessEvalShader);
	//glAttachShader(shaderProgram, geometryShader);
	glAttachShader(shaderProgram, fragShader);

	//glBindFragDataLocation(shaderProgram, 0, "outColor");

	glLinkProgram(shaderProgram);

	if (glIsProgram(shaderProgram) == GL_TRUE)
		std::cout << "isProgram success" << std::endl;
	else
		std::cout << "isProgram fail" << std::endl;

	// Maybe check and specify vertex attributes here?
	//GLuint posLoc = glGetAttribLocation(shaderProgram, "position");

	Shader newShader = Shader();
	newShader._id = ++_latestId;
	newShader._shaderProgram = shaderProgram;

	_shaderCache.insert(std::pair<int, Shader>(newShader._id, newShader));

	return newShader._id;
}

GLuint ShaderCache::GetShaderProgram(int shaderId) const {
	int count = _shaderCache.count(shaderId);
	if (count == 0) {
		int defaultShaderCount = _shaderCache.count(0);
		if (defaultShaderCount == 0) {
			return _shaderCache.at(0)._shaderProgram;
		}
		else
		{
			return -1;
		}
	}

	return _shaderCache.at(shaderId)._shaderProgram;
}
