#include <iostream>
#include <SDL.h>
#include <fbxsdk.h>

#include "../EntityComponent/Entity.h"
#include "../EntityComponent/Component.h"
#include "../Rendering/ShaderCache.h"

#include "../Camera/FlyCam.h"

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

FbxMesh* GetMesh(FbxNode* node)
{
	if (node == nullptr)
	{
		return nullptr;
	}

	for (int i = 0; i < node->GetChildCount(); ++i)
	{
		if (node->GetChild(i) == nullptr)
		{
			continue;
		}

		FbxMesh* mesh = node->GetChild(i)->GetMesh();
		if (mesh == nullptr)
		{
			if (node->GetChild(i)->GetChildCount() == 0)
			{
				return nullptr;
			}
			else
			{
				for (int j = 0; j < node->GetChildCount(); ++j)
				{
					if (GetMesh(node->GetChild(i)->GetChild(j)) != nullptr)
					{
						std::cout << "mesh found at indexes i: " << i << " j: " << j << std::endl;
					}
				}
			}
		}
		else
		{
			std::cout << "mesh found at index i: " << i << std::endl;
			std::cout << "mesh polygon count: " << mesh->GetPolygonCount() << std::endl;
			return mesh;
		}
	}

	return nullptr;
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

	entity._position = glm::vec3(0.f, 0.f, 5.f);

	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, entity._position) * glm::mat4_cast(entity._rotation) * glm::scale(model, entity._scale);

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

	int numVertices = 0;
	int numIndices = 0;

	FbxManager *manager = FbxManager::Create();

	FbxIOSettings *ioSettings = FbxIOSettings::Create(manager, IOSROOT);
	manager->SetIOSettings(ioSettings);

	FbxImporter *importer = FbxImporter::Create(manager, "");
	if (!importer->Initialize("Assets/Models/humanoid.fbx", -1, manager->GetIOSettings()))
	{
		std::cout << "Initialize unsuccessful" << std::endl;
	}

	if (importer->IsFBX())
	{
		std::cout << "model is an fbx" << std::endl;

		FBXSDK_printf("Animation Stack Information\n");

		int lAnimStackCount = importer->GetAnimStackCount();

		FBXSDK_printf("    Number of Animation Stacks: %d\n", lAnimStackCount);

		for (int i = 0; i < lAnimStackCount; i++)
		{
			FbxTakeInfo* lTakeInfo = importer->GetTakeInfo(i);

			FBXSDK_printf("    Animation Stack %d\n", i);
			FBXSDK_printf("         Name: \"%s\"\n", lTakeInfo->mName.Buffer());
			FBXSDK_printf("         Description: \"%s\"\n", lTakeInfo->mDescription.Buffer());

			// Change the value of the import name if the animation stack should be imported 
			// under a different name.
			FBXSDK_printf("         Import Name: \"%s\"\n", lTakeInfo->mImportName.Buffer());

			// Set the value of the import state to false if the animation stack should be not
			// be imported. 
			FBXSDK_printf("         Import State: %s\n", lTakeInfo->mSelect ? "true" : "false");
			FBXSDK_printf("\n");
		}
	}

	FbxScene *scene = FbxScene::Create(manager, "tempName");

	if (!importer->Import(scene))
	{
		std::cout << "import unsuccessful" << std::endl;
	}
	importer->Destroy();


	struct VertexInfo
	{
		glm::vec3 position;
	};

	FbxNode* rootNode = scene->GetRootNode();
	FbxMesh* fbxMesh = GetMesh(rootNode);
	/*if (fbxMesh != nullptr)
	{*/
		int vertexCount = 0;
		vertexCount = fbxMesh->GetControlPointsCount();

		VertexInfo* vertices;
		vertices = new VertexInfo[vertexCount];

		int triangleCount = fbxMesh->GetPolygonVertexCount() / 3;
		int indicesCount = fbxMesh->GetPolygonVertexCount();

		FbxVector4* fbxVerts = new FbxVector4[vertexCount];
		int arrayIndex = 0;
		memcpy(fbxVerts, fbxMesh->GetControlPoints(), vertexCount * sizeof(FbxVector4));
	//}
		float wValue = 1.f;
		std::vector<GLfloat> vertexInfo(vertexCount);
		for (int j = 0; j < triangleCount; ++j)
		{
			int index = 0;
			FbxVector4 fbxNorm(0, 0, 0, 0);
			FbxVector2 fbxUV(0, 0);
			bool texCoordFound = false;
			//face.indices[0] = index = fbxMesh->GetPolygonVertex(j, 0);
			vertices[index].position.x = (GLfloat)fbxVerts[index][0];
			vertices[index].position.y = (GLfloat)fbxVerts[index][1];
			vertices[index].position.z = (GLfloat)fbxVerts[index][2];
			fbxMesh->GetPolygonVertexNormal(j, 0, fbxNorm);

			index = fbxMesh->GetPolygonVertex(j, 1);
			vertices[index].position.x = (GLfloat)fbxVerts[index][0];
			vertices[index].position.y = (GLfloat)fbxVerts[index][1];
			vertices[index].position.z = (GLfloat)fbxVerts[index][2];

			index = fbxMesh->GetPolygonVertex(j, 2);
			vertices[index].position.x = (GLfloat)fbxVerts[index][0];
			vertices[index].position.y = (GLfloat)fbxVerts[index][1];
			vertices[index].position.z = (GLfloat)fbxVerts[index][2];

			vertexInfo.push_back(vertices[index]);
		}

	//FbxMesh* fbxMesh = rootNode->GetChild(0)->GetMesh();
	//std::cout << fbxMesh->GetPolygonVertexCount() << std::endl;

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

		uniformLoc = glGetUniformLocation(shaderProgram, "view");
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(GameCamera.CalculateViewMatrix() * glm::mat4_cast(entity._rotation)));

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