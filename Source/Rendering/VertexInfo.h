#ifndef VERTEX_INFO_SHARDLITE
#define VERTEX_INFO_SHARDLITE

#include <vector>
#include "GLIncludes.h"

struct VertexInfo
{
	std::vector<GLfloat> _positions;
	std::vector<GLfloat> _uvs;
	std::vector<GLuint> _blendingIndices;
	std::vector<GLfloat> _blendingWeight;
};

#endif