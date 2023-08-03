#include "RubiksCube.h"

RubiksCube::RubiksCube()
{
	m_faces = {
		{Up, Face(Up, {Back, Right, Front, Left})},
		{Down, Face(Down, {Front, Right, Back, Left})},
		{Left, Face(Left, {Up, Front, Down, Back})},
		{Right, Face(Right, {Up, Back, Down, Front})},
		{Front, Face(Front, {Up, Right, Down, Left})},
		{Back, Face(Back, {Up, Left, Down, Right})},
	};
}

void RubiksCube::Move(Side face, MoveDir moveDir)
{
	m_faces[face].Rotate(moveDir);

	// rotate the edges clockwise
	auto neighbours = m_faces[face].GetNeighbours();
	std::array<Side, NUMBER_OF_PIECES_PER_ROW> swap = m_faces[neighbours[0]].GetRow(face);
	for (int i = 1; i < neighbours.size(); i++)
	{
		m_faces[neighbours[i - 1]].SetRow(m_faces[neighbours[i]].GetRow(face), face);
	}
	m_faces[neighbours[neighbours.size() - 1]].SetRow(swap, face);
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
				Side neighbour1 = j == 0 ? sides[1] : sides[0];
				Side neighbour2 = j == 1 ? sides[2] : sides[1];
				colorScheme[i] = m_faces[sides[j]].GetCornerSide(neighbour1, neighbour2);
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
				Side neighbour = j == 0 ? sides[1] : sides[0];
				colorScheme[i] = m_faces[sides[j]].GetEdgeSide(neighbour);
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
				colorScheme[i] = m_faces[sides[j]].GetSide();
			}
		}
	}
	return colorScheme;
}

