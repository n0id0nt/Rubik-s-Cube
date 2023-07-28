#pragma once

#include <vector>
#include "glm\glm.hpp"

enum MeshType
{
	kCube
};

struct Vertex
{
	glm::vec3 pos;
	glm::vec2 texCoord;
};

class Mesh
{
public:
	static void setCubeData(std::vector<Vertex>& vertices);
};

