#include "CubieComponent.h"
#include "../Entity/Entity.h"
#include "RendererComponent.h"

CubieComponent::CubieComponent(Entity* entity, ComponentRubiksCubeAdaptor* cubeComponent, std::vector<Side> sides)
	: Component(entity), m_sides(sides), m_RubiksCubeComponent(cubeComponent)
{
	m_renderComponent = new RendererComponent(entity);
	entity->AddComponent(m_renderComponent);
}

void CubieComponent::UpdateColors()
{
	auto sides =  m_RubiksCubeComponent->GetColors(m_sides);
	RendererComponent::ColorScheme colorScheme {};
	for (int i = 0; i < sides.size(); i++)
	{
		colorScheme[i] = ComponentRubiksCubeAdaptor::ConvertSideToColor(sides[i]);
	}
	m_renderComponent->SetColorSceme(colorScheme);
}
