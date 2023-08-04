#include "Face.h"
#include "RubiksCube.h"

Face::Face(Side side, std::array<Side, NUMBER_OF_NEIGHBOURS> neightbours)
	: m_side(side), m_corners(), m_edges(), m_neighbours(neightbours)
{
	std::fill(m_corners.begin(), m_corners.end(), side);
	std::fill(m_edges.begin(), m_edges.end(), side);
	/*
	m_corners[0] = Up;
	m_corners[1] = Down;
	m_corners[2] = Left;
	m_corners[3] = Right;

	m_edges[0] = Up;
	m_edges[1] = Down;
	m_edges[2] = Left;
	m_edges[3] = Right;
	//*/
}

Face::Face()
	: m_side(Core), m_corners(), m_edges(), m_neighbours()
{
	std::fill(m_corners.begin(), m_corners.end(), m_side);
	std::fill(m_edges.begin(), m_edges.end(), m_side);
}

bool Face::IsSolved()
{
	// check if all the edges and all the corners match the side
	return false;
}

std::array<Side, NUMBER_OF_PIECES_PER_ROW> Face::GetRow(Side neighbour)
{
	std::array<Side, NUMBER_OF_PIECES_PER_ROW> row;
	int index = GetIndexOfNeighbour(neighbour);
	int index2 = (index + 1) % NUMBER_OF_NEIGHBOURS;
	row[0] = m_corners[index];
	row[1] = m_edges[index];
	row[2] = m_corners[index2];
	return row;
}

void Face::SetRow(std::array<Side, NUMBER_OF_PIECES_PER_ROW> row, Side neighbour)
{
	int index = GetIndexOfNeighbour(neighbour);
	int index2 = (index + 1) % NUMBER_OF_NEIGHBOURS;
	m_corners[index] = row[0];
	m_edges[index] = row[1];
	m_corners[index2] = row[2];
}

void Face::Rotate(MoveDir direction)
{
	Side swap = m_edges[0];
	for (int i = 1; i < m_edges.size(); i++)
	{
		m_edges[i - 1] = m_edges[i];
	}
	m_edges[m_edges.size() - 1] = swap;

	swap = m_corners[0];
	for (int i = 1; i < m_corners.size(); i++)
	{
		m_corners[i - 1] = m_corners[i];
	}
	m_corners[m_corners.size() - 1] = swap;
}

Side Face::GetCornerSide(Side neighbour1, Side neighbour2)
{
	if ((m_neighbours[0] == neighbour1 && m_neighbours[m_neighbours.size() - 1] == neighbour2)
		|| (m_neighbours[0] == neighbour2 && m_neighbours[m_neighbours.size() - 1] == neighbour1))
	{
		return m_corners[0];
	}
	for (int i = 1; i < m_neighbours.size(); i++)
	{
		if ((m_neighbours[i - 1] == neighbour1 && m_neighbours[i] == neighbour2)
			|| (m_neighbours[i - 1] == neighbour2 && m_neighbours[i] == neighbour1))
		{
			return m_corners[i];
		}
	}
	return Core;
}

Side Face::GetEdgeSide(Side neighbour)
{
	for (int i = 0; i < m_neighbours.size(); i++)
	{
		if (m_neighbours[i] == neighbour)
		{
			return m_edges[i];
		}
	}
	return Core;
}

Side Face::GetSide()
{
	return m_side;
}

std::array<Side, NUMBER_OF_NEIGHBOURS> Face::GetNeighbours()
{
	return m_neighbours;
}

int Face::GetIndexOfNeighbour(Side side)
{
	for (int i = 0; i < m_neighbours.size(); i++)
	{
		if (m_neighbours[i] == side)
			return i;
	}
	return -1;
}
