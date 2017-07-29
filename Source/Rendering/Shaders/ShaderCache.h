// We should be able to query the shader for specific attributes and their setup info like binding indexes, sizes, and types
// We'll be able to do this because when a shader is loaded we'll scan its contents and determine what attributes are specified there
// We will match these by name against a list of predetermined attribute names that we support, and will fail the shader creation if there is an attribute mismatch
// As long as there is one valid attribute then it can go ahead, but we will log that there were unspported types or names in the shader

// This hardcoded support will allow us to know exactly what they need for their setup.

// We can do the same for uniforms.

// We can use this info to then do vertex attribute setup in a much nicer way, which is dependant on the actual shaders and what
// they specifically need (as opposed to needing all of them to support all things right now)


#ifndef SHADER_CACHE
#define SHADER_CACHE

#include "ShaderParser.h"

#ifdef _WIN32
#include <glew.h>
#include <gl\GL.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif

#include <map>

struct Shader
{
	int m_id;
	GLuint m_shaderProgram;

	VertexAttribute m_vertexAttributes[AllowedAttributeArraySize];
};

class ShaderCache
{
public:
	ShaderCache();
	~ShaderCache();

	void Init();

	GLuint AddShader(std::string vertexShaderName, std::string fragShaderName, int& shaderId);

	GLuint GetShaderProgram(int shaderId) const;
	Shader* GetShader(int shaderId);

private:
	static int m_latestId;
	std::map<int, Shader> m_shaderCache;

	ShaderParser m_shaderParser;
};

#endif