#include <iostream>
#include <SDL.h>
#include <fbxsdk.h>
#include <fbxsdk\core\fbxclassid.h>
#include <fbxsdk\scene\shading\fbxsurfacelambert.h>

#include "../EntityComponent/Entity.h"
#include "../EntityComponent/Component.h"
#include "../Rendering/ShaderCache.h"
#include "../Rendering/MeshManagement/MeshAssetManager.h"
#include "../Rendering/MeshManagement/Mesh.h"

#include "../Camera/FlyCam.h"

#include <glew.h>
#include <SOIL.h>
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

unsigned char* LoadTextureFromFile(const GLchar* in_texName)
{
	GLuint* texture = new GLuint;
	glGenTextures(1, texture);
	GLint width = 0, height = 0;

	unsigned char* image = NULL;

	std::string amendedPath(in_texName);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *texture);
	image = SOIL_load_image(amendedPath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (image == NULL)
	{
		std::cout << "Image " << in_texName << " is null!" << std::endl;
		std::cout << "SOIL error: " << SOIL_last_result() << std::endl;

		return NULL;
	}

	return image;
}

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
	//entity._scale = glm::vec3(0.1f, 0.1f, 0.1f);
	
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

	MeshAssetManager meshManager = MeshAssetManager();

	//entity._scale = glm::vec3(0.0001f, 0.0001f, 0.0001f);
	entity._scale = glm::vec3(0.1f, 0.1f, 0.1f);
	//entity._scale = glm::vec3(1.f, 1.f, 1.f);

	

	Mesh* shardliteMesh = meshManager.LoadMesh("skeleton.fbx");
	if (shardliteMesh == nullptr)
	{
		std::cout << "Mesh load failed" << std::endl;
		return 0;
	}
	std::vector<GLfloat> vertexInfo = shardliteMesh->GetVertices();

	LoadTextureFromFile("Assets/Textures/skeleton.png");

	GLuint vao3d;
	glCreateVertexArrays(1, &vao3d);
	glBindVertexArray(vao3d);

	GLuint vbo3d;

	glCreateBuffers(1, &vbo3d);
	glNamedBufferStorage(vbo3d, vertexInfo.size() * sizeof(GLfloat), &vertexInfo[0], 0);

	GLuint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexArrayAttribFormat(vao3d, posAttrib, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vao3d, posAttrib, 0);
	glEnableVertexAttribArray(posAttrib);

	/*GLuint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glVertexArrayAttribFormat(vao3d, colAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));
	glVertexArrayAttribBinding(vao3d, colAttrib, 0);
	glEnableVertexAttribArray(colAttrib);*/

	glVertexArrayVertexBuffer(vao3d, 0, vbo3d, 0, 3 * sizeof(GLfloat));

	std::vector<GLfloat> uvInfo = shardliteMesh->GetUVs();

	GLuint vboUVs;
	glCreateBuffers(1, &vboUVs);
	glNamedBufferStorage(vboUVs, uvInfo.size() * sizeof(GLfloat), &uvInfo[0], 0);

	GLuint texCoordAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	glVertexArrayAttribFormat(vboUVs, texCoordAttrib, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vboUVs, texCoordAttrib, 1);
	glEnableVertexAttribArray(texCoordAttrib);

	glVertexArrayVertexBuffer(vao3d, 1, vboUVs, 0, 2 * sizeof(GLfloat));

	glUseProgram(shaderProgram);

	//entity._position = glm::vec3(0.f, 0.f, 5.f);

	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, entity._position) * glm::mat4_cast(entity._rotation) * glm::scale(model, entity._scale);

	GLint uniformLoc = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(model));

	uniformLoc = glGetUniformLocation(shaderProgram, "textureSprite");
	glUniform1i(uniformLoc, 0);

	glm::mat4 proj = glm::perspective(45.0f, 640.0f / 480.0f, 0.1f, 1000.0f);
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

	//entity._rotation = entity._rotation * glm::angleAxis(1.f, glm::vec3(-80.f, 0.f, 0.f));

	FlyCamera GameCamera = FlyCamera(win);

	double m_last = 0.f;
	double m_current = 0.f;
	double deltaTime = 0.f;

	while(true)
	{
		m_last = m_current;
		m_current = SDL_GetPerformanceCounter();
		deltaTime = (double)((m_current - m_last) * 1000 / SDL_GetPerformanceFrequency());

		const Uint8* keystate = SDL_GetKeyboardState(NULL);

		GameCamera.Update(deltaTime);

		if (keystate[SDL_SCANCODE_UP])
		{
			model = glm::mat4(1);
			model = glm::translate(model, entity._position += glm::vec3(0.f, 0.f, 0.1f)) * glm::mat4_cast(entity._rotation) * glm::scale(model, entity._scale);

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

		if (keystate[SDL_SCANCODE_2])
		{
			entity._position = glm::vec3(0.f, 0.f, 2.f);
		}

		if (keystate[SDL_SCANCODE_3])
		{
			entity._position = glm::vec3(0.f, 0.f, 3.f);
		}

		if (keystate[SDL_SCANCODE_4])
		{
			entity._position = glm::vec3(0.f, 0.f, 4.f);
		}

		if (keystate[SDL_SCANCODE_5])
		{
			entity._position = glm::vec3(0.f, 0.f, 5.f);
		}

		if (keystate[SDL_SCANCODE_6])
		{
			entity._rotation *= glm::angleAxis(1.f, glm::vec3(0.f, 1.f, 0.f));
		}

		model = glm::mat4(1);
		model = glm::translate(model, entity._position) * glm::mat4_cast(entity._rotation) * glm::scale(model, entity._scale);
		uniformLoc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(model));

		uniformLoc = glGetUniformLocation(shaderProgram, "view");
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(GameCamera.CalculateViewMatrix()));// *glm::mat4_cast(entity._rotation)));

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
		glDrawArrays(GL_TRIANGLES, 0, vertexInfo.size());
		

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