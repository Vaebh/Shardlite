#include <iostream>
#include <SDL.h>
#include "../EntityComponent/Entity.h"
#include "../EntityComponent/Component.h"
#include "../Rendering/ShaderCache.h"

#include <glew.h>
#include <gl\GL.h>

#include <math.h>

#undef main

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	/*SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}*/

	/*SDL_Surface *bmp = SDL_LoadBMP("Assets/hello.bmp");
	if (bmp == nullptr) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	if (tex == nullptr) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}*/


	SDL_GLContext gi_glcontext = SDL_GL_CreateContext(win);
	/*SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 0);*/

	Entity entity = Entity();
	entity.AddComponent<Component>();

	glewExperimental = GL_TRUE;

	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		std::cout << "Glew failed init" << std::endl;
		std::cout << "Error initializing GLEW! %s\n" << glewGetErrorString(glewError) << std::endl;
		std::cin.get();
		return 2;
	}

	ShaderCache shaderCache = ShaderCache();
	shaderCache.Init();

	GLuint shaderProgram = shaderCache.GetShaderProgram(0);

	GLuint vao;
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//shaderCache.AddShader()

	const GLfloat verts[] = { 0.f, 0.5f, 0.f, 1.f, 0.f, 0.f,
		-0.5f, -0.5f, 0.f, 1.f, 0.f, 0.f,
		0.5f, -0.5f, 0.f, 1.f, 0.f, 0.f };

	GLuint vbo;
	//glCreateBuffers(sizeof(GLfloat) * 9, &vbo);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 18, &(verts), GL_STATIC_DRAW);
	//glBindVertexBuffer()

	//A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
	while(true) {
		//First clear the renderer
		//SDL_RenderClear(ren);
		////Draw the texture
		//SDL_RenderCopy(ren, tex, NULL, NULL);
		////Update the screen
		//SDL_RenderPresent(ren);

		const GLfloat red[] = { sin(SDL_GetTicks() * 0.001f) * 0.5f + 0.5f, cos(SDL_GetTicks() * 0.001f) * 0.5f + 0.5f, 0.0f, 1.0f };

		

		glClearBufferfv(GL_COLOR, 0, red);
		glUseProgram(shaderProgram);

		//glPointSize(40.f);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		SDL_GL_SwapWindow(win);

		GLuint errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
			printf("%i, %s\n", errorCode, gluErrorString(errorCode));
	}

	std::cin.get();

	/*SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);*/
	SDL_DestroyWindow(win);
	SDL_Quit();

	glDeleteVertexArrays(1, &vao);
	return 0;
}