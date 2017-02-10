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

void MouseUpdate(float &CamYaw, float &CamPitch)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	//SDL_WarpMouseGlobal(r_width / 2, r_height / 2);

	CamYaw += (x - 640 / 2)*0.2;
	CamPitch += (y - 480 / 2)*0.2;

	if (CamPitch<-90) {
		CamPitch = -90;
	}

	if (CamPitch>90) {
		CamPitch = 90;
	}
}

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
	//shaderCache.Init();

	GLuint shaderProgram;// = shaderCache.GetShaderProgram(0);

	GLuint vao;
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//shaderCache.AddShader()

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

	

	glm::vec3 position = glm::vec3(0.f, 0.f, 5.f);
	glm::quat rot = glm::quat();
	glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f);

	

	shaderCache.AddShader("Assets/Shaders/3DVertexShader.txt", "Assets/Shaders/3DFragShader.txt");
	shaderProgram = shaderCache.GetShaderProgram(0);
	//glUseProgram(shaderProgram);


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

	//glm::vec3 camPosition = glm::vec3(0.f, 0.f, -2.f);//(1.f, 1.f, -2.f);
	//glm::vec3 target = glm::vec3(0.f, 0.f, 0.f);

	float horizontalAngle = 3.14f;
	float verticalAngle = 0.f;
	float testRot = 0.f;

	double m_last = 0.f;
	double m_current = 0.f;
	double deltaTime = 0.f;

	//A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
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
		testRot = 0.f;
		if (keystate[SDL_SCANCODE_A])
		{
			GameCamera.m_position -= GameCamera.m_right * (float)(0.005f * deltaTime);
			//testRot -= 120.f * deltaTime;
		}
		if (keystate[SDL_SCANCODE_D])
		{
			GameCamera.m_position += GameCamera.m_right * (float)(0.005f * deltaTime);
			//testRot += 120.f * deltaTime;
		}

		if (keystate[SDL_SCANCODE_ESCAPE])
		{
			SDL_DestroyWindow(win);
			SDL_Quit();

			glDeleteVertexArrays(1, &vao);
			return 0;
		}

		int x;
		int y;
		SDL_GetMouseState(&x, &y);

		x -= 320;
		y -= 240;

		horizontalAngle += x;
		//horizontalAngle = (int)horizontalAngle % 360;

		//SDL_WarpMouseInWindow(win, (short)(640 / 2), ((short)480 / 2));
		std::cout << "x: " << x << std::endl;
		std::cout << "horizontalAngle: " << horizontalAngle << std::endl;

		GameCamera.RotatePitch(glm::radians((float)(-y % 480) * 8.f));
		GameCamera.RotateYaw(glm::radians((float)(x % 640) * 8.f));
		

		/*float dx = x - (640.f / 2.f);
		float dy = y - (480.f / 2.f);

		float sensativity = 30.0f;
		//bool invertMouse = false;
		GameCamera.Rotate(, glm::vec3(0.f, 1.f, 0.f));
		GameCamera.Rotate((invertMouse ? 1.0f : -1.0f) * dy * frameTime *sensativity);
		camera.rotateY(dx * frameTime * sensativity);
		Sdl.SDL_WarpMouse((short)centerX, (short)centerY);*/



		//GameCamera.Rotate(glm::radians(testRot), glm::vec3(0.f, 1.f, 0.f));

		uniformLoc = glGetUniformLocation(shaderProgram, "view");
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(GameCamera.CalculateViewMatrix() * glm::mat4_cast(rot)));

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			/* handle your event here */

			//glm::vec3 camForward = glm::normalize(GameCamera.m_direction);

			/*switch (event.type)
			{
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_LEFT:
							//position.x -= 0.1f;
							//camPosition.x -= 0.1f;
							//target.x -= 0.1f;

							model = glm::mat4(1);
							model = glm::translate(model, position * camForward) * glm::mat4_cast(rot) * glm::scale(model, scale);

							uniformLoc = glGetUniformLocation(shaderProgram, "model");
							glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(model));
							break;

						case SDLK_RIGHT:
							//camPosition.x += 0.1f;
							//target.x += 0.1f;
							//position += glm::vec3(0.0f, 0.0f, 1.0f) * glm::vec3(0.1f, 0.0f, 0.0f);

							model = glm::mat4(1);
							model = glm::translate(model, position) * glm::mat4_cast(rot) * glm::scale(model, scale);

							uniformLoc = glGetUniformLocation(shaderProgram, "model");
							glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(model));
							break;

						/*case SDLK_w:
							GameCamera.m_position += GameCamera.m_direction * 0.4f;
							break;

						case SDLK_s:
							GameCamera.m_position -= GameCamera.m_direction * 0.4f;
							break;

						case SDLK_a:
							testRot -= 8000.f;
							break;

						case SDLK_d:
							testRot += 8000.f;
							break;

						case SDLK_ESCAPE:
							SDL_DestroyWindow(win);
							SDL_Quit();

							glDeleteVertexArrays(1, &vao);
							return 0;
							break;
					}
					break;
			}*/

			/*glm::mat4 viewMatrix = glm::lookAt(
				//camPosition,
				//target,
				camPosition,
				camPosition + direction,
				glm::vec3(0.0f, 1.0f, 0.0f)
			);*/

			//glm::quat &rot = glm::angleAxis(glm::radians(testRot), glm::vec3(0.f, 1.f, 0.f));
			//glm::eulerAngles(rot);

			
		}

		
		//First clear the renderer
		//SDL_RenderClear(ren);
		////Draw the texture
		//SDL_RenderCopy(ren, tex, NULL, NULL);
		////Update the screen
		//SDL_RenderPresent(ren);

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