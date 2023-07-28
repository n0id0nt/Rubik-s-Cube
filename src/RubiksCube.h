#pragma once

#include <list>
#include <SDL.h>
#include "Cubelet.h"
#include "Camera.h"

enum MoveDir
{
	Clockwise,
	Anticlockwise,
	Double
};

const glm::vec3 blue	= glm::vec3(0.05f, 0.25f, 0.7f);
const glm::vec3 green	= glm::vec3(0.1f, 0.9f, 0.1f);
const glm::vec3 orange	= glm::vec3(0.85f, 0.4f, 0.01f);
const glm::vec3 red		= glm::vec3(0.9f, 0.1f, 0.15f);
const glm::vec3 yellow	= glm::vec3(0.85f, 0.85f, 0.08f);
const glm::vec3 white	= glm::vec3(1.0f, 1.0f, 1.0f);
const glm::vec3 black	= glm::vec3(0.0f, 0.0f, 0.0f);

class RubiksCube
{
public:
	RubiksCube(unsigned int layerCount, Camera* camera);
	~RubiksCube();

	void Move(unsigned int layer, Axis axis, MoveDir moveDir);

	void Rotate(float degrees, Axis axis);

	void Input(const SDL_Event &e);

	void Update();

	void Render();
private:
	unsigned int m_LayerCount;
	Cubelet**** m_Cubelets; // 3d array
	glm::vec3 m_ColorScheme[7];
	Camera* m_Camera;

	// Animate moves
	bool m_IsLerping;
	Axis m_CurAxis;

	float m_CurRot;
	float m_TarRot;
	float m_InitRot;

	char m_Dir;
	Transform m_MoveTransform;
	const float ROTATE_SPEED = 2.5f;
	std::vector<Cubelet*> m_FocusCublets;
	Transform m_Transform;
};

