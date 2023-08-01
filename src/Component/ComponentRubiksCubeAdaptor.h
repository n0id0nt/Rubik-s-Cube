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

    std::array<Side, CUBE_SIDES> GetColors(std::vector<Side> sides);

    static glm::vec3 ConvertSideToColor(Side);

private:
    RubiksCube m_rubiksCube;
    bool m_isAnimating;
    std::vector<CubieComponent*> m_cubies;
};

