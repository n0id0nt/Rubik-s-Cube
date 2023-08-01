#pragma once

#include <SDL.h>
#include <map>
#include <vector>
#include <array>
#include "Face.h"
#include "glm\glm.hpp"

#define CUBE_LAYERS 3
#define CUBE_SIDES 6

enum MoveDir
{
	Clockwise,
	Anticlockwise,
	Double
};

enum Side
{
	Back,
	Front,
	Left,
	Right,
	Down,
	Up,
	Core
};

class RubiksCube
{
public:
	typedef std::array<Side, 3> Corner;
	typedef std::array<Side, 2> Edge;
	typedef std::array<Side, 1> Center;

	RubiksCube();

	void Move(Side face, MoveDir moveDir);
	bool IsSolved();

	Corner GetCorner();
	Edge GetEdge();

	std::array<Side, CUBE_SIDES> GetColors(Corner sides);
	std::array<Side, CUBE_SIDES> GetColors(Edge sides);
	std::array<Side, CUBE_SIDES> GetColors(Center sides);

private:

	// declares all the cubes faces
	std::map<Side, Face> m_faces;
};

