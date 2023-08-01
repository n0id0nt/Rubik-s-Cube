#include "Face.h"

Face::Face(Side side, std::array<Side, NUMBER_OF_NEIGHBOURS> neightbours)
	: m_side(side), m_corners(), m_edges(), m_neightbours(neightbours)
{
}

bool Face::IsSolved()
{
	return false;
}

std::array<Side, 3> Face::GetRow()
{
	return std::array<Side, 3>();
}

std::array<Side, 3> Face::SetRow()
{
	return std::array<Side, 3>();
}

void Face::Rotate(MoveDir direction)
{
}

Side Face::GetCornerSide(Side neighbour1, Side neighbour2)
{
	for (int i = 1; i < m_neightbours.size(); i++)
	{
		if ((m_neightbours[i - 1] == neighbour1 && m_neightbours[i] == neighbour2)
			|| (m_neightbours[i - 1] == neighbour2 && m_neightbours[i] == neighbour1))
		{
			return m_edges[i];
		}
	}
	return m_edges[0];
}

Side Face::GetEdgeSide(Side neighbour)
{
	for (int i = 0; i < m_neightbours.size(); i++)
	{
		if (m_neightbours[i] == neighbour)
		{
			return m_edges[i];
		}
	}
}
