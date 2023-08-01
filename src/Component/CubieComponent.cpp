#include "CubieComponent.h"
#include "../Entity/Entity.h"
#include "RendererComponent.h"

CubieComponent::CubieComponent(Entity* entity, ComponentRubiksCubeAdaptor* cubeComponent)
	: Component(entity), m_sides(), m_RubiksCubeComponent(cubeComponent)
{
	entity->AddComponent(new RendererComponent(entity, glm::vec3(0.1f, 0.9f, 0.1f)));
}

void CubieComponent::AddSide(Side side)
{
	m_sides.push_back(side);
}
