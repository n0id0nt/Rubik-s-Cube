#pragma once

#include <array>

#define NUMBER_OF_EDGES_PER_FACE 4
#define NUMBER_OF_CORNERS_PER_FACE 4 
#define NUMBER_OF_NEIGHBOURS 4 
#define NUMBER_OF_PIECES_PER_ROW 3 

enum Side;
enum MoveDir;

class Face
{
public:
	Face(Side side, std::array<Side, NUMBER_OF_NEIGHBOURS> neightbours);

	bool IsSolved();

	std::array<Side, NUMBER_OF_PIECES_PER_ROW> GetRow();
	std::array<Side, NUMBER_OF_PIECES_PER_ROW> SetRow();

	void Rotate(MoveDir direction);

	Side GetCornerSide(Side, Side);
	Side GetEdgeSide(Side);

private:
	std::array<Side, NUMBER_OF_EDGES_PER_FACE> m_edges;
	std::array<Side, NUMBER_OF_CORNERS_PER_FACE> m_corners;
	// list of neighboring face in a clockwise order
	std::array<Side, NUMBER_OF_NEIGHBOURS> m_neightbours;
	Side m_side;
};

