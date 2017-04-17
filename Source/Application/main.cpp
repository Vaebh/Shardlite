#include <iostream>
#include <SDL.h>
#include <fbxsdk.h>
#include <fbxsdk/core/fbxclassid.h>
#include <fbxsdk/scene/shading/fbxsurfacelambert.h>

#include "../EntityComponent/Entity.h"
#include "../EntityComponent/Component.h"
#include "../Rendering/ShaderCache.h"
#include "../Rendering/MeshManagement/MeshAssetManager.h"
#include "../Rendering/MeshManagement/Mesh.h"
#include "../Rendering/MeshManagement/MeshComponentManager.h"
#include "../Rendering/System/Batch.h"

#include "../Rendering/AssetLoading/TextureManager.h"
#include "../Rendering/AssetLoading/Texture.h"

#include "../Camera/FlyCam.h"

#ifdef _WIN32
#include <glew.h>
#include <gl\GL.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#endif

#include <SOIL.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <math.h>

#undef main

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

#ifdef __APPLE__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif
    
	SDL_GLContext gi_glcontext = SDL_GL_CreateContext(win);

	Entity entity = Entity();
	//entity._scale = glm::vec3(0.1f, 0.1f, 0.1f);
	
	entity.AddComponent<Component>();

#ifdef _WIN32
	glewExperimental = GL_TRUE;

	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		std::cout << "Glew failed init" << std::endl;
		std::cout << "Error initializing GLEW! %s\n" << glewGetErrorString(glewError) << std::endl;
		std::cin.get();
		return 2;
	}
#endif

	ShaderCache shaderCache = ShaderCache();
	//shaderCache.Init();

	GLuint shaderProgram;// = shaderCache.GetShaderProgram(0);

	GLuint vao = 0;
#ifdef _WIN32
    glCreateVertexArrays(1, &vao);
#endif
    
#ifdef __APPLE__
    glGenVertexArrays(1, &vao);
#endif
	
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

	shaderProgram = shaderCache.AddShader("Assets/Shaders/3DVertexShader.txt", "Assets/Shaders/3DFragShader.txt");

	MeshAssetManager meshManager = MeshAssetManager();
	TextureManager textureManager = TextureManager();

	//entity._scale = glm::vec3(0.0001f, 0.0001f, 0.0001f);
	entity._scale = glm::vec3(0.1f, 0.1f, 0.1f);
	//entity._scale = glm::vec3(1.f, 1.f, 1.f);

	MeshComponentManager meshCompManager = MeshComponentManager();
	MeshComponent* meshComp = meshCompManager.AddMeshComponent(&entity, "humanoid.fbx");
	std::vector<Batch> batches = meshCompManager.GetOpaqueBatches();
	Batch testBatch = batches[0];
	testBatch.GenerateBatchData();

	std::vector<GLfloat> vertexInfo = testBatch.GetVertexData();

	Mesh* shardliteMesh = meshComp->GetMesh();

	/*Mesh* shardliteMesh = meshManager.LoadMesh("skeleton.fbx");
	if (shardliteMesh == nullptr)
	{
		std::cout << "Mesh load failed" << std::endl;
		return 0;
	}*/
	//std::vector<GLfloat> vertexInfo = shardliteMesh->GetVertices();

	textureManager.RequestTexture("Assets/Textures/skeleton.png");
	//LoadTextureFromFile("Assets/Textures/skeleton.png");

	GLuint vao3d;
    GLuint vbo3d;
    
    // Just add this in defines until I hide it away in classes properly
#ifdef _WIN32
    glCreateVertexArrays(1, &vao3d);
    glCreateBuffers(1, &vbo3d);
#endif
    
#ifdef __APPLE__
    glGenVertexArrays(1, &vao3d);
    glGenBuffers(1, &vbo3d);
#endif
    
	glBindVertexArray(vao3d);
    
    GLuint posAttrib = glGetAttribLocation(shaderProgram, "position");
    
#ifdef _WIN32
    glNamedBufferStorage(vbo3d, vertexInfo.size() * sizeof(GLfloat), &vertexInfo[0], 0);
    
    glVertexArrayAttribFormat(vao3d, posAttrib, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vao3d, posAttrib, 0);
    glEnableVertexAttribArray(posAttrib);
    
    glVertexArrayVertexBuffer(vao3d, 0, vbo3d, 0, 3 * sizeof(GLfloat));
#endif
    
#ifdef __APPLE__
    glBindBuffer(GL_ARRAY_BUFFER, vbo3d);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexInfo.size(), &(vertexInfo[0]), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
#endif

	/*GLuint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glVertexArrayAttribFormat(vao3d, colAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));
	glVertexArrayAttribBinding(vao3d, colAttrib, 0);
	glEnableVertexAttribArray(colAttrib);*/

	std::vector<GLfloat> uvInfo = shardliteMesh->GetUVs();
    
	if (uvInfo.size() > 0)
	{
		GLuint vboUVs;
		GLuint texCoordAttrib = glGetAttribLocation(shaderProgram, "texcoord");

#ifdef _WIN32
		glCreateBuffers(1, &vboUVs);
		glNamedBufferStorage(vboUVs, uvInfo.size() * sizeof(GLfloat), &uvInfo[0], 0);

		texCoordAttrib = glGetAttribLocation(shaderProgram, "texcoord");
		glVertexArrayAttribFormat(vboUVs, texCoordAttrib, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vboUVs, texCoordAttrib, 1);
		glEnableVertexAttribArray(texCoordAttrib);

		glVertexArrayVertexBuffer(vao3d, 1, vboUVs, 0, 2 * sizeof(GLfloat));
#endif

#ifdef __APPLE__
		glGenBuffers(1, &vboUVs);

		glBindBuffer(GL_ARRAY_BUFFER, vboUVs);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * uvInfo.size(), &(uvInfo[0]), GL_STATIC_DRAW);

		texCoordAttrib = glGetAttribLocation(shaderProgram, "texcoord");
		glEnableVertexAttribArray(texCoordAttrib);
		glVertexAttribPointer(texCoordAttrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
#endif
	}
    
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

#ifdef _WIN32
		GLuint errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
			printf("%i, %s\n", errorCode, gluErrorString(errorCode));
#endif
	}

	std::cin.get();

	SDL_DestroyWindow(win);
	SDL_Quit();

	glDeleteVertexArrays(1, &vao);
	return 0;
}
