#include "RenderSystem.h"

#ifdef _WIN32
#include <glew.h>
#include <gl\GL.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#endif

#include <iostream>

int RenderSystem::StartUp()
{
#ifdef _WIN32
	glewExperimental = GL_TRUE;

	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		std::cout << "Glew failed init" << std::endl;
		std::cout << "Error initializing GLEW! %s\n" << glewGetErrorString(glewError) << std::endl;
		std::cin.get();
		return 1;
	}
#endif

	return SETUP_SUCCESS;
}

int RenderSystem::ShutDown()
{
	return SETUP_SUCCESS;
}