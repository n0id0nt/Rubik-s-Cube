#include "RubiksCube.h"

RubiksCube::RubiksCube()
{
	m_faces = {
		{Up, Face(Up, {Back, Right, Front, Left})},
		{Down, Face(Down, {Front, Right, Back, Left})},
		{Left, Face(Left, {Up, Front, Down, Back})},
		{Right, Face(Right, {Up, Back, Down, Right})},
		{Front, Face(Front, {Up, Right, Down, Left})},
		{Back, Face(Back, {Up, Left, Down, Right})},
	};
}

void RubiksCube::Move(Side face, MoveDir moveDir)
{
}

bool RubiksCube::IsSolved()
{
	return false;
}

RubiksCube::Corner RubiksCube::GetCorner()
{
	return Corner();
}

RubiksCube::Edge RubiksCube::GetEdge()
{
	return Edge();
}

std::array<Side, CUBE_SIDES> RubiksCube::GetColors(Corner sides)
{
	std::array<Side, CUBE_SIDES> colorScheme;
	std::fill(colorScheme.begin(), colorScheme.end(), Core);
	for (int i = 0; i < CUBE_SIDES; i++)
	{
		for (int j = 0; j < sides.size(); j++)
		{
			if (i == sides[j])
			{
				colorScheme[i] = sides[j];
			}
		}
	}
	return colorScheme;
}

std::array<Side, CUBE_SIDES> RubiksCube::GetColors(Edge sides)
{
	std::array<Side, CUBE_SIDES> colorScheme;
	std::fill(colorScheme.begin(), colorScheme.end(), Core);
	for (int i = 0; i < CUBE_SIDES; i++)
	{
		for (int j = 0; j < sides.size(); j++)
		{
			if (i == sides[j])
			{
				colorScheme[i] = sides[j];
			}
		}
	}
	return colorScheme;
}

std::array<Side, CUBE_SIDES> RubiksCube::GetColors(Center sides)
{
	std::array<Side, CUBE_SIDES> colorScheme;
	std::fill(colorScheme.begin(), colorScheme.end(), Core);
	for (int i = 0; i < CUBE_SIDES; i++)
	{
		for (int j = 0; j < sides.size(); j++)
		{
			if (i == sides[j])
			{
				colorScheme[i] = sides[j];
			}
		}
	}
	return colorScheme;
}

