#include <iostream>
#include <SDL.h>

#include "Application.h"

#include "../EntityComponent/Entity.h"
#include "../EntityComponent/Component.h"
#include "../Rendering/Shaders/ShaderCache.h"
#include "../Rendering/MeshManagement/MeshAssetManager.h"
#include "../Rendering/MeshManagement/Mesh.h"
#include "../Rendering/MeshManagement/MeshComponentManager.h"
#include "../Rendering/System/Batch.h"

#include "../Rendering/AssetLoading/TextureManager.h"
#include "../Rendering/AssetLoading/Texture.h"

#include "../Camera/FlyCam.h"

#include "../Rendering/Animation/Skeleton.h"

#include "assimp\Importer.hpp"
#include "assimp\postprocess.h"

#include <SOIL.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <math.h>

#undef main
	
int SETUP_SUCCESS = 2;

SDL_Window* gameWindow = nullptr;

ShaderCache shaderCache;
MeshAssetManager meshAssetManager;
MeshComponentManager meshComponentManager;

TextureManager textureManager;

void GetTestVertexInfo(std::vector<GLfloat>& vertexVector)
{
	std::vector<Batch> batches = meshComponentManager.GetOpaqueBatches();
	Batch testBatch = batches[0];
	testBatch.GenerateBatchData();

	vertexVector = testBatch.GetVertexData();
}

void AssimpTest()
{
	Assimp::Importer Importer;
	const aiScene* pScene = Importer.ReadFile("Assets/Models/skeleton.fbx", aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	if (pScene) {
		std::cout << "loaded" << std::endl;
	}
	else {
		std::cout << "error" << std::endl;
	}
}

int main()
{
	Application app;
	app.StartUpSystems();

	gameWindow = app.GetWindow();

	shaderCache.Init();

	Entity entity;

	// Humanoid Scale
	//entity._scale = glm::vec3(0.1f, 0.1f, 0.1f);

	// Skeleton Scale
	entity._scale = glm::vec3(1.f, 1.f, 1.f);

	//entity._position = glm::vec3(0.f, 0.f, 5.f);

	entity._rotation = entity._rotation * glm::angleAxis(1.f, glm::vec3(-80.f, 0.f, 0.f));

	int shaderId;
	GLuint shaderProgram = shaderCache.AddShader("Assets/Shaders/3DVertexShader.txt", "Assets/Shaders/3DFragShader.txt", shaderId);
	Shader* defaultShader = shaderCache.GetShader(shaderId);

	MeshComponent* meshComp = meshComponentManager.AddMeshComponent(&entity, "skeleton.fbx", defaultShader);
	Mesh* shardliteMesh = meshComp->GetMesh();

	textureManager.RequestTexture("Assets/Textures/skeleton.png");

	int vertexCount = shardliteMesh->GetVertexCount();
    
	glUseProgram(shaderProgram);

	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, entity._position) * glm::mat4_cast(entity._rotation) * glm::scale(model, entity._scale);

	glm::mat4 proj = glm::perspective(45.0f, 640.0f / 480.0f, 0.1f, 1000.0f);
	/*GLint uniformLoc = glGetUniformLocation(shaderProgram, "projection");
	glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(proj));*/

	meshComp->BindUniformData(Matrix4f, defaultShader->m_shaderUniforms[Model], model);
	meshComp->BindUniformData(Matrix4f, defaultShader->m_shaderUniforms[Projection], proj);

	GLint uniformLoc = -1;

	/*std::vector<glm::mat4> jointTransforms;
	meshComp->GetMesh()->m_skeleton->GetJointTransforms(jointTransforms);

	for (int i = 0; i < meshComp->GetMesh()->m_skeleton->_joints.size(); ++i)
	{
		//meshComp->GetMesh()->m_skeleton->_joints[i]._node->index
	}

	uniformLoc = glGetUniformLocation(shaderProgram, "jointTransforms");
	glUniformMatrix4fv(uniformLoc, jointTransforms.size(), GL_FALSE, glm::value_ptr(jointTransforms[0]));*/

	FlyCamera GameCamera = FlyCamera(gameWindow);
	//GameCamera.m_position = glm::vec3(0.23f, 1.65f, 4.18f);
	GameCamera.m_position = glm::vec3(8.f, 18.65f, 24.18f);
	GameCamera.m_direction = glm::vec3(0.f, 0.f, -1.f);
	GameCamera.m_inverted = false;
	//GameCamera.RotateYaw(180.f);
	//GameCamera.m_direction = glm::vec3(-1.f, -0.f, 0.f);

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
			SDL_DestroyWindow(gameWindow);
			SDL_Quit();

			//glDeleteVertexArrays(1, &vao3d);
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

		if (keystate[SDL_SCANCODE_BACKSPACE])
		{
			std::cout << "Cam pos: " << GameCamera.m_position.x << ", " << GameCamera.m_position.y << ", " << GameCamera.m_position.z << std::endl;
		}

		model = glm::mat4(1);
		model = glm::translate(model, entity._position) * glm::mat4_cast(entity._rotation) * glm::scale(model, entity._scale);
		uniformLoc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(model));

		uniformLoc = glGetUniformLocation(shaderProgram, "view");
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(GameCamera.CalculateViewMatrix()));// *glm::mat4_cast(entity._rotation)));

		glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		//glUseProgram(shaderProgram);
		//glBindVertexArray(vao3d);
		glDrawArrays(GL_TRIANGLES, 0, vertexCount);
		

		SDL_GL_SwapWindow(gameWindow);

#ifdef _WIN32
		GLuint errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
			printf("%i, %s\n", errorCode, gluErrorString(errorCode));
#endif
	}

	std::cin.get();

	SDL_DestroyWindow(gameWindow);
	SDL_Quit();

	//glDeleteVertexArrays(1, &vao3d);
	return 0;
}
