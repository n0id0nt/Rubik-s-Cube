#pragma once

#include "Component.h"
#include "../RubiksCube/RubiksCube.h"
#include <vector>
#include "ComponentRubiksCubeAdaptor.h"
#include "RendererComponent.h"

class CubieComponent : public Component
{
public:
	CubieComponent(Entity* entity, ComponentRubiksCubeAdaptor* cubeComponent, std::vector<Side> sides);

	void Update() {}

	void UpdateColors();

private:
	std::vector<Side> m_sides;
	ComponentRubiksCubeAdaptor* m_RubiksCubeComponent;
	RendererComponent* m_renderComponent;
};

