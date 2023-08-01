#pragma once

#include <array>

enum Side;
enum MoveDir;

class Face
{
public:
	Face(Side side);

	bool IsSolved();

	std::array<Side, 3> GetRow();
	std::array<Side, 3> SetRow();

	void Rotate(MoveDir direction);

private:
	std::array<Side, 4> m_corners;
	std::array<Side, 4> m_edges;
	Side m_side;
};

