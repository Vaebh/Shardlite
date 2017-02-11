#include <iostream>
#include <SDL.h>
#include "../EntityComponent/Entity.h"
#include "../EntityComponent/Component.h"
#include "../Rendering/ShaderCache.h"

#include "../Camera/Camera.h"

#include <glew.h>
#include <gl\GL.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <math.h>

#undef main

const GLfloat cubeVerts[] = {
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Shardlite", 100, 100, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_GRABBED);
	if (win == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_GLContext gi_glcontext = SDL_GL_CreateContext(win);

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
	//shaderCache.Init();

	GLuint shaderProgram;// = shaderCache.GetShaderProgram(0);

	GLuint vao;
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);

	const GLfloat vertPositions[] = { 0.f, 0.5f, 0.f,
		-0.5f, -0.5f, 0.f,
		0.5f, -0.5f, 0.f };

	const GLfloat vertColours[] = { 0.f, 1.f, 0.f, 1.0f,
		0.f, 0.f, 1.f, 1.0f,
		0.f, 1.f, 0.f, 1.0f };

	const GLfloat vertsCombined[] = { -0.5f, 0.5f, 0.f, 0.f, 1.f, 0.f, 1.0f,
		-1.f, -0.5f, 0.f, 0.f, 0.f, 1.f, 1.0f,
		0.f, -0.5f, 0.f, 0.f, 1.f, 0.f, 1.0f };

	/*GLuint vbo;
	//glCreateBuffers(sizeof(GLfloat) * 9, &vbo);

	GLuint buffers[2];
	glCreateBuffers(2, &buffers[0]);

	glNamedBufferStorage(buffers[0], sizeof(vertPositions), vertPositions, 0);
	glVertexArrayVertexBuffer(vao, 0, buffers[0], 0, 3 * sizeof(GLfloat));
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexArrayAttribFormat(vao, posAttrib, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vao, posAttrib, 0);
	glEnableVertexAttribArray(posAttrib);


	glNamedBufferStorage(buffers[1], sizeof(vertColours), vertColours, 0);
	glVertexArrayVertexBuffer(vao, 1, buffers[1], 0, 4 * sizeof(GLfloat));
	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glVertexArrayAttribFormat(vao, colAttrib, 4, GL_FLOAT, GL_FALSE,0);
	glVertexArrayAttribBinding(vao, colAttrib, 1);
	glEnableVertexAttribArray(colAttrib);

	GLuint vao2;
	glCreateVertexArrays(1, &vao2);
	glBindVertexArray(vao2);

	glCreateBuffers(1, &vbo);
	glNamedBufferStorage(vbo, sizeof(vertsCombined), vertsCombined, 0);
	posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexArrayAttribFormat(vao2, posAttrib, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vao2, posAttrib, 0);
	glEnableVertexAttribArray(posAttrib);

	colAttrib = glGetAttribLocation(shaderProgram, "color");
	glVertexArrayAttribFormat(vao2, colAttrib, 4, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));
	glVertexArrayAttribBinding(vao2, colAttrib, 0);
	glEnableVertexAttribArray(colAttrib);

	glVertexArrayVertexBuffer(vao2, 0, vbo, 0, 7 * sizeof(GLfloat));*/

	shaderCache.AddShader("Assets/Shaders/3DVertexShader.txt", "Assets/Shaders/3DFragShader.txt");
	shaderProgram = shaderCache.GetShaderProgram(0);

	GLuint vao3d;
	glCreateVertexArrays(1, &vao3d);
	glBindVertexArray(vao3d);

	GLuint vbo3d;

	glCreateBuffers(1, &vbo3d);
	glNamedBufferStorage(vbo3d, sizeof(cubeVerts), cubeVerts, 0);

	GLuint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexArrayAttribFormat(vao3d, posAttrib, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vao3d, posAttrib, 0);
	glEnableVertexAttribArray(posAttrib);

	GLuint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glVertexArrayAttribFormat(vao3d, colAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));
	glVertexArrayAttribBinding(vao3d, colAttrib, 0);
	glEnableVertexAttribArray(colAttrib);

	glVertexArrayVertexBuffer(vao3d, 0, vbo3d, 0, 8 * sizeof(GLfloat));

	glUseProgram(shaderProgram);

	glm::vec3 position = glm::vec3(0.f, 0.f, 5.f);
	glm::quat rot = glm::quat();
	glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f);

	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, position) * glm::mat4_cast(rot) * glm::scale(model, scale);

	GLint uniformLoc = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(model));

	glm::mat4 proj = glm::perspective(45.0f, 640.0f / 480.0f, 1.0f, 1000.0f);
	uniformLoc = glGetUniformLocation(shaderProgram, "proj");
	glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(proj));

	/*glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 18, &(verts), GL_STATIC_DRAW);*/
	//glBindVertexBuffer()

	Camera GameCamera = Camera();

	double m_last = 0.f;
	double m_current = 0.f;
	double deltaTime = 0.f;

	while(true) {

		m_last = m_current;
		m_current = SDL_GetPerformanceCounter();
		deltaTime = (double)((m_current - m_last) * 1000 / SDL_GetPerformanceFrequency());

		const Uint8* keystate = SDL_GetKeyboardState(NULL);

		if (keystate[SDL_SCANCODE_W])
		{
			GameCamera.m_position += GameCamera.m_direction * (float)(0.005f * deltaTime);
		}
		if (keystate[SDL_SCANCODE_S])
		{
			GameCamera.m_position -= GameCamera.m_direction * (float)(0.005f * deltaTime);
		}
		if (keystate[SDL_SCANCODE_A])
		{
			GameCamera.m_position += GameCamera.m_right * (float)(0.005f * deltaTime);
		}
		if (keystate[SDL_SCANCODE_D])
		{
			GameCamera.m_position -= GameCamera.m_right * (float)(0.005f * deltaTime);
		}

		if (keystate[SDL_SCANCODE_UP])
		{
			model = glm::mat4(1);
			model = glm::translate(model, position += glm::vec3(0.f, 0.f, 0.1f)) * glm::mat4_cast(rot) * glm::scale(model, scale);

			uniformLoc = glGetUniformLocation(shaderProgram, "model");
			glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(model));
		}

		if (keystate[SDL_SCANCODE_ESCAPE])
		{
			SDL_DestroyWindow(win);
			SDL_Quit();

			glDeleteVertexArrays(1, &vao);
			return 0;
		}

		uniformLoc = glGetUniformLocation(shaderProgram, "view");
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(GameCamera.CalculateViewMatrix() * glm::mat4_cast(rot)));

		bool mouseGrabbed = false;
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_MOUSEMOTION:
				int x;
				int y;
				if (!mouseGrabbed)
				{
					SDL_GetRelativeMouseState(&x, &y);

					GameCamera.RotatePitch(glm::radians((float)(y) * 100.f));
					GameCamera.RotateYaw(glm::radians((float)(x) * 100.f));

					SDL_WarpMouseInWindow(win, (short)(640 / 2), ((short)480 / 2));
				}
				else
				{
					// Soak up the mouse event generated by warping the mouse back to the middle
					SDL_GetRelativeMouseState(&x, &y);
				}

				mouseGrabbed = !mouseGrabbed;
				break;
			}
		}

		//const GLfloat red[] = { sin(SDL_GetTicks() * 0.001f) * 0.5f + 0.5f, cos(SDL_GetTicks() * 0.001f) * 0.5f + 0.5f, 0.0f, 1.0f };
		const GLfloat red[] = { 1.f, 0.0f, 0.0f, 1.0f };
		

		/*glClearBufferfv(GL_COLOR, 0, red);
		glUseProgram(shaderProgram);

		GLfloat offset[] = { sin(SDL_GetTicks() * 0.001f) * 0.5f, cos(SDL_GetTicks() * 0.001f) * 0.5f, 0.0f };

		//glVertexAttrib3fv(0, offset);

		glPointSize(5.f);
		glPatchParameteri(GL_PATCH_VERTICES, 3);

		glBindVertexArray(vao);
		glDrawArrays(GL_PATCHES, 0, 3);

		glBindVertexArray(vao2);
		glDrawArrays(GL_PATCHES, 0, 3);*/


		glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		//glUseProgram(shaderProgram);
		glBindVertexArray(vao3d);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		

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