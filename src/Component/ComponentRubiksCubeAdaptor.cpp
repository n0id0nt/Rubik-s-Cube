#include "ComponentRubiksCubeAdaptor.h"
#include "../Entity/Entity.h"
#include "../Scene.h"
#include "CubieComponent.h"
#include "RendererComponent.h"
#include "../Input.h"
#include <iostream>

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

	entity->AddComponent(new RendererComponent(entity, glm::vec3(0.1f, 0.9f, 0.1f)));
}
	

void ComponentRubiksCubeAdaptor::Update()
{
	// rotate
	glm::vec2 dir = Input::GetArrowDir();
	
	glm::vec3 rotation = GetEntity()->GetTransform()->GetRotation();
	GetEntity()->GetTransform()->SetRotation(glm::vec3(rotation.x + dir.y, rotation.y + dir.x, rotation.z));

	// get the move and set the piece
	if (false)
	{
		//m_rubiksCube.Move()
	}
}

void ComponentRubiksCubeAdaptor::CreateCubie(int x, int y, int z)
{
	// check whether center, edge, or corner
	bool onXBoundry = x == 0 || x == CUBE_LAYERS - 1;
	bool onYBoundry = y == 0 || y == CUBE_LAYERS - 1;
	bool onZBoundry = z == 0 || z == CUBE_LAYERS - 1;

	// ignore when core
	if (!(onXBoundry || onYBoundry || onZBoundry))
		return;

	CubieComponent* cubie;
	Entity* entity;
	// is corner
	if (onXBoundry && onYBoundry && onZBoundry)
	{
		entity = GetEntity()->GetScene()->CreateEntity("Corner");
		cubie = new CubieComponent(entity, this);
		entity->AddComponent(cubie);
	}
	// is edge
	else if ((onXBoundry && onYBoundry) || (onXBoundry && onZBoundry) || (onYBoundry && onZBoundry))
	{
		entity = GetEntity()->GetScene()->CreateEntity("Edge");
		cubie = new CubieComponent(entity, this);
		entity->AddComponent(cubie);
	}
	// is Center
	else
	{
		entity = GetEntity()->GetScene()->CreateEntity("Center");
		cubie = new CubieComponent(entity, this);
		entity->AddComponent(cubie);
	}

	float offset = CUBE_LAYERS / 2.0f;
	entity->GetTransform()->SetPosition(glm::vec3(x - offset, y - offset, z - offset));
	entity->GetTransform()->SetParent(GetEntity()->GetTransform());

	m_cubies.push_back(cubie);
}
