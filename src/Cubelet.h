#pragma once

#include "opengl\openglHelper.h"
#include "opengl\Shader.h"
#include "opengl\Mesh.h"
#include "opengl\Texture.h"
#include "Camera.h"
#include "Transform.h"

#include "glm\glm.hpp"
#include <vector>

#define FACE_COUNT 6

enum Axis
{
	X,
	Y,
	Z
};



class Cubelet
{
private:
	struct CubletRotate
	{
		float degrees;
		Axis axis;
	};
public:
	Cubelet(glm::vec3** colorScheme, glm::vec3 position, Transform* parent);
	~Cubelet();

	void SetRotate(float rotate, Axis axis);
	Transform* GetTransform();

	void Render(glm::mat4 view, glm::mat4 projection);
private:
	Shader* m_Shader;
	Texture* m_Texture;
	std::vector<Vertex> m_Vertices;
	GLuint m_VAO, m_VBO;
	glm::vec3* m_ColorScheme[FACE_COUNT];
	Transform m_Transform;
};

