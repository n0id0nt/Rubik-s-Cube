#include "Face.h"

Face::Face(Side side)
	: m_side(side)
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
