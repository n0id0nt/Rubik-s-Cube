#pragma once

#include <SDL.h>
#include "Face.h"

enum MoveDir
{
	Clockwise,
	Anticlockwise,
	Double
};

enum Color
{
	White,
	Yellow,
	Green,
	Blue,
	Red,
	Orange
};

enum Side
{
	Up,
	Down,
	Front,
	Back,
	Right,
	Left
};

//const glm::vec3 blue	= glm::vec3(0.05f, 0.25f, 0.7f);
//const glm::vec3 green	= glm::vec3(0.1f, 0.9f, 0.1f);
//const glm::vec3 orange	= glm::vec3(0.85f, 0.4f, 0.01f);
//const glm::vec3 red		= glm::vec3(0.9f, 0.1f, 0.15f);
//const glm::vec3 yellow	= glm::vec3(0.85f, 0.85f, 0.08f);
//const glm::vec3 white	= glm::vec3(1.0f, 1.0f, 1.0f);
//const glm::vec3 black	= glm::vec3(0.0f, 0.0f, 0.0f);

class RubiksCube
{
	typedef std::array<Color, 3> Corner;
	typedef std::array<Color, 2> Edge;

public:
	RubiksCube();
	~RubiksCube();

	void Move(Side face, MoveDir moveDir);
	bool IsSolved();

	Corner GetCorner();
	Edge GetEdge();

private:
	// declares all the cubes faces
	Face m_up;
	Face m_down;
	Face m_left;
	Face m_right;
	Face m_front;
	Face m_back;
};

