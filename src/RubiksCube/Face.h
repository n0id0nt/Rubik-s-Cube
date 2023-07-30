#pragma once

#include <array>

enum Color;
enum MoveDir;

class Face
{
public:
	Face(Color color);

	bool IsSolved();

	std::array<Color, 3> GetRow();
	std::array<Color, 3> SetRow();

	void Rotate(MoveDir direction);

private:
	std::array<Color, 4> m_corners;
	std::array<Color, 4> m_edges;
	Color m_center;
};

