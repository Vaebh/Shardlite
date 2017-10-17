#ifndef DRAW_CALL_OBJECT_SHARDLITE
#define DRAW_CALL_OBJECT_SHARDLITE

#include "GLIncludes.h"

class MeshComponent;

struct DrawCallObject
{
	MeshComponent* m_meshComp;
	float m_zPos;
	GLuint m_vaoId;
	int m_numVerts;

	DrawCallObject()
	{

	}

	DrawCallObject(MeshComponent* meshComp, float zPos, GLuint vao, int numVerts)
	{
		m_meshComp = meshComp;
		m_zPos = zPos;
		m_vaoId = vao;
		m_numVerts = numVerts;
	}
};

#endif