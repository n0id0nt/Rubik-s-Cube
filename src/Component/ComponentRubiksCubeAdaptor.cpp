#include "ComponentRubiksCubeAdaptor.h"
#include "../Entity/Entity.h"
#include "../Scene.h"
#include "CubieComponent.h"
#include "RendererComponent.h"
#include "../Input.h"
#include <iostream>
#include <array>

ComponentRubiksCubeAdaptor::ComponentRubiksCubeAdaptor(Entity* entity)
	: Component(entity), m_rubiksCube(), m_isAnimating(false), m_cubies()
{
	// create cubies
	for (int x = 0; x < CUBE_LAYERS; x++)
	{
		for (int y = 0; y < CUBE_LAYERS; y++)
		{
			for (int z = 0; z < CUBE_LAYERS; z++)
			{
				CreateCubie(x, y, z);
			}
		}
	}
}
	

void ComponentRubiksCubeAdaptor::Update()
{
	const float rotationSpeed = 3.0f;
	// rotate
	glm::vec2 dir = Input::GetArrowDir();
	glm::vec3 rotation = GetEntity()->GetTransform()->GetRotation();
	GetEntity()->GetTransform()->SetRotation(glm::vec3(rotation.x + dir.y * rotationSpeed, rotation.y - dir.x * rotationSpeed, rotation.z));

	// rotate cube sides
	// up
	if (Input::isKeyDown(SDL_SCANCODE_U))
	{
		Move(Up, Clockwise);
	}
	else if (Input::isKeyDown(SDL_SCANCODE_D))
	{
		Move(Down, Clockwise);
	}
	else if (Input::isKeyDown(SDL_SCANCODE_R))
	{
		Move(Right, Clockwise);
	}
	else if (Input::isKeyDown(SDL_SCANCODE_L))
	{
		Move(Left, Clockwise);
	}
	else if (Input::isKeyDown(SDL_SCANCODE_F))
	{
		Move(Front, Clockwise);
	}
	else if (Input::isKeyDown(SDL_SCANCODE_B))
	{
		Move(Back, Clockwise);
	}

	// animate the move
	if (false)
	{
		//m_rubiksCube.Move()
	}
}

void ComponentRubiksCubeAdaptor::CreateCubie(int x, int y, int z)
{
	// check whether center, edge, or corner
	std::vector<Side> sides;

	if (x == 0)
	{
		sides.push_back(Left);
	}
	else if (x == CUBE_LAYERS - 1)
	{
		sides.push_back(Right);
	}

	if (y == 0)
	{
		sides.push_back(Down);
	}
	else if (y == CUBE_LAYERS - 1)
	{
		sides.push_back(Up);
	}

	if (z == 0)
	{
		sides.push_back(Back);
	}
	else if (z == CUBE_LAYERS - 1)
	{
		sides.push_back(Front);
	}

	// ignore when core
	if (sides.size() == 0)
		return;

	CubieComponent* cubie;
	Entity* entity;
	entity = GetEntity()->GetScene()->CreateEntity("Cubie");
	cubie = new CubieComponent(entity, this, sides);
	entity->AddComponent(cubie);

	float offset = CUBE_LAYERS / 2.0f - 0.5f;
	entity->GetTransform()->SetPosition(glm::vec3(x - offset, y - offset, z - offset));
	entity->GetTransform()->SetParent(GetEntity()->GetTransform());

	cubie->UpdateColors();

	m_cubies.push_back(cubie);
}

std::array<Side, CUBE_SIDES> ComponentRubiksCubeAdaptor::GetColors(std::vector<Side> sides)
{
	int sidesCount = sides.size();
	switch (sidesCount)
	{
	case 1:
		RubiksCube::Center center;
		std::copy(sides.begin(), sides.begin() + sidesCount, center.begin());
		return m_rubiksCube.GetColors(center);
	case 2:
		RubiksCube::Edge edge;
		std::copy(sides.begin(), sides.begin() + sidesCount, edge.begin());
		return m_rubiksCube.GetColors(edge);
	case 3:
		RubiksCube::Corner corner;
		std::copy(sides.begin(), sides.begin() + sidesCount, corner.begin());
		return m_rubiksCube.GetColors(corner);
	}

	return std::array<Side, CUBE_SIDES>();
}

glm::vec3 ComponentRubiksCubeAdaptor::ConvertSideToColor(Side side)
{
	switch (side)
	{
	case Up:
		return white;
	case Down:
		return yellow;
	case Left:
		return orange;
	case Right:
		return red;
	case Front:
		return green;
	case Back:
		return blue;
	}
	return black;
}

void ComponentRubiksCubeAdaptor::Move(Side side, MoveDir dir)
{
	std::cout << "move" << std::endl;

	// update internal model
	m_rubiksCube.Move(side, dir);
	// update color scheme
	UpdateColors();
}

void ComponentRubiksCubeAdaptor::UpdateColors()
{
	for (auto& cubie : m_cubies)
	{
		cubie->UpdateColors();
	}
}
