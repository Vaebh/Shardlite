#include "ShaderCache.h"
#include <fstream>

#include <iostream>
#include <vector>

using std::string;

int ShaderCache::m_latestId = -1;

const string DEFAULT_VERT_SHADER = "Assets/Shaders/VertexShader.txt";
const string DEFAULT_FRAG_SHADER = "Assets/Shaders/FragShader.txt";
const string DEFAULT_TESSELATION_CONTROL_SHADER = "Assets/Shaders/TessControl.txt";
const string DEFAULT_TESSELATION_EVALUATION_SHADER = "Assets/Shaders/TessEval.txt";
const string DEFAULT_GEOMETRY_SHADER = "Assets/Shaders/GeometryShader.txt";

namespace
{
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

	GLuint CreateShaderFromFile(const std::string& in_path, const GLenum& in_shaderType, std::string& out_shaderSource)
	{
		// Get the shader
		out_shaderSource = LoadShaderFromFile(in_path);

		if (out_shaderSource.empty())
		{
			return 0;
		}
        
#ifdef __APPLE__
        shaderSrcString = "#version 410\n" + shaderSrcString;
#endif
        
#ifdef _WIN32
		out_shaderSource = "#version 450\n" + out_shaderSource;
#endif

		const GLchar* shaderSrc = out_shaderSource.c_str();

		// Loading Vertex Shader
		GLuint shader = glCreateShader(in_shaderType);
		glShaderSource(shader, 1, &shaderSrc, NULL);
		glCompileShader(shader);

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_TRUE)
		{
			std::cout << "shader compile success" << std::endl;
		}
		else
		{
			std::cout << "shader compile fail" << std::endl;
		}

		return shader;
	}

	void DeleteShader(GLuint in_shader, GLuint shaderProgram)
	{
		glDetachShader(shaderProgram, in_shader);
		glDeleteShader(in_shader);
	}
}

ShaderCache::ShaderCache()
{

}

ShaderCache::~ShaderCache()
{

}

void ShaderCache::Init()
{
	int shaderIndex;
	AddShader(DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER, shaderIndex);
}

GLuint ShaderCache::AddShader(std::string vertexShaderName, std::string fragShaderName, int& shaderId)
{
	std::string vertexShaderSource, fragShaderSource;

	GLuint vertexShader = CreateShaderFromFile(vertexShaderName, GL_VERTEX_SHADER, vertexShaderSource);
	//GLuint tessControlShader = CreateShaderFromFile(DEFAULT_TESSELATION_CONTROL_SHADER, GL_TESS_CONTROL_SHADER);
	//GLuint tessEvalShader = CreateShaderFromFile(DEFAULT_TESSELATION_EVALUATION_SHADER, GL_TESS_EVALUATION_SHADER);
	//GLuint geometryShader = CreateShaderFromFile(DEFAULT_GEOMETRY_SHADER, GL_GEOMETRY_SHADER);
	GLuint fragShader = CreateShaderFromFile(fragShaderName, GL_FRAGMENT_SHADER, fragShaderSource);
	

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
	newShader.m_id = ++m_latestId;
	newShader.m_shaderProgram = shaderProgram;

	m_shaderParser.ParseVertexAttributes(GL_VERTEX_SHADER, vertexShaderSource, newShader.m_vertexAttributes);
	m_shaderParser.ParseShaderUniforms(newShader.m_shaderProgram, GL_VERTEX_SHADER, vertexShaderSource, newShader.m_shaderUniforms);

	m_shaderCache.insert(std::pair<int, Shader>(newShader.m_id, std::move(newShader)));

	shaderId = newShader.m_id;
	return newShader.m_shaderProgram;
}

Shader* ShaderCache::GetShader(int shaderId)
{
	if (m_shaderCache.find(shaderId) != m_shaderCache.end())
	{
		return &(m_shaderCache[shaderId]);
	}

	return nullptr;
}

GLuint ShaderCache::GetShaderProgram(int shaderId) const
{
	int count = m_shaderCache.count(shaderId);
	if (count == 0)
	{
		int defaultShaderCount = m_shaderCache.count(0);
		if (defaultShaderCount == 0)
		{
			return m_shaderCache.at(0).m_shaderProgram;
		}
		else
		{
			return -1;
		}
	}

	return m_shaderCache.at(shaderId).m_shaderProgram;
}
