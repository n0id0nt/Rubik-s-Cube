#include "RubiksCube.h"

RubiksCube::RubiksCube() 
	: m_up(White), m_down(Yellow), m_left(Orange), m_right(Red), m_back(Blue), m_front(Green)
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

