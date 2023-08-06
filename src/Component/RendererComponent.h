#pragma once

#include "Component.h"
#include "..\opengl\Shader.h"
#include "..\opengl\Texture.h"
#include "..\opengl\Mesh.h"
#include "glm\glm.hpp"
#include "../opengl/IRenderer.h"
#include "..\opengl\openglHelper.h"
#include <array>
#include "../RubiksCube/RubiksCube.h"

const glm::vec3 blue = glm::vec3(0.05f, 0.25f, 0.7f);
const glm::vec3 green = glm::vec3(0.1f, 0.9f, 0.1f);
const glm::vec3 orange = glm::vec3(0.85f, 0.4f, 0.01f);
const glm::vec3 red = glm::vec3(0.9f, 0.1f, 0.15f);
const glm::vec3 yellow = glm::vec3(0.85f, 0.85f, 0.08f);
const glm::vec3 white = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::vec3 black = glm::vec3(0.0f, 0.0f, 0.0f);

class Panel;

struct Vertex
{
	glm::vec3 pos;
	glm::vec2 texCoord;
};

class RendererComponent : public Component, public IRenderer
{
public:
	typedef std::array<glm::vec3, CUBE_SIDES> ColorScheme;

	RendererComponent(Entity* entity);
	RendererComponent(Entity* entity, ColorScheme colorScheme);

	void Update() {}

	void Render(Panel* panel) override;

	void SetColorSceme(ColorScheme colorScheme);

private:

	void initOpenGL();

	Shader* m_Shader;
	Texture* m_Texture;
	std::vector<Vertex> m_Vertices;
	GLuint m_VAO, m_VBO;
	ColorScheme m_colorScheme;
};

