#pragma once
#include "Component.h"
#include "../RubiksCube/RubiksCube.h"
#include <vector>

class CubieComponent;

class ComponentRubiksCubeAdaptor :
    public Component
{
public:
    ComponentRubiksCubeAdaptor(Entity* entity);

    void Update();

    void CreateCubie(int x, int y, int z);

private:
    RubiksCube m_rubiksCube;
    bool m_isAnimating;
    std::vector<CubieComponent*> m_cubies;
};

