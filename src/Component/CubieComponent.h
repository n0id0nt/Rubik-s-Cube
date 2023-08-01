#pragma once

#include "Component.h"
#include "../RubiksCube/RubiksCube.h"
#include <vector>
#include "ComponentRubiksCubeAdaptor.h"

class CubieComponent : public Component
{
public:
	CubieComponent(Entity* entity, ComponentRubiksCubeAdaptor* cubeComponent);

	void AddSide(Side side);

	void Update() {}

private:
	std::vector<Side> m_sides;
	ComponentRubiksCubeAdaptor* m_RubiksCubeComponent;
};

