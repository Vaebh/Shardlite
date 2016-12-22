#ifndef SHADER_CACHE
#define SHADER_CACHE

#include <glew.h>

#include <map>

struct Shader {
	int _id;
	GLuint _shaderProgram;
};

class ShaderCache
{
public:
	ShaderCache();
	~ShaderCache();

	void Init();

	void AddShader(std::string vertexShaderName, std::string fragShaderName);

	GLuint GetShaderProgram(int shaderId) const;

private:
	static int _latestId;
	std::map<int, Shader> _shaderCache;
};

#endif