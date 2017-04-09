#ifndef SHADER_CACHE
#define SHADER_CACHE

#ifdef _WIN32
#include <glew.h>
#include <gl\GL.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif

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

	int AddShader(std::string vertexShaderName, std::string fragShaderName);

	GLuint GetShaderProgram(int shaderId) const;

private:
	static int _latestId;
	std::map<int, Shader> _shaderCache;
};

#endif
