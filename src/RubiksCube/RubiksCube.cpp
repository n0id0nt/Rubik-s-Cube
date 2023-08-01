#include "RubiksCube.h"

RubiksCube::RubiksCube() 
	: m_up(Up), m_down(Down), m_left(Left), m_right(Right), m_back(Back), m_front(Front)
{
	
}

RubiksCube::~RubiksCube()
{
	
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

