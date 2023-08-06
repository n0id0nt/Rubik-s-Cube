#include "Scene.h"
#include "Component\RendererComponent.h"
#include "Component/ComponentRubiksCubeAdaptor.h"
#include "Window.h"

Scene::Scene(Window* window)
	: m_entities(), m_camera(new Camera(glm::vec3(0.0f, 0.0f, 6.0f))), m_window(window)
{
	// create the rubiks cube and respective components
	Entity* rubiksCube = CreateEntity("Rubiks Cube");
	rubiksCube->AddComponent(new ComponentRubiksCubeAdaptor(rubiksCube));
	//rubiksCube->AddComponent(new RendererComponent(entity, glm::vec3(0.1f, 0.9f, 0.1f)));
}

Scene::~Scene()
{
	
}

void Scene::Update()
{
	for (auto& entity : m_entities)
	{
		entity->Update();
	}
}

void Scene::Render()
{
	for (auto& entity : m_entities)
	{
		if (entity->HasComponent<RendererComponent>())
		{
			entity->GetComponent<RendererComponent>()->Render();
		}
	}
}

Entity* Scene::CreateEntity(std::string name)
{
	m_entities.push_back(std::make_unique<Entity>(this, name));
	return m_entities.back().get();
}

void Scene::RemoveEntity(Entity* entity)
{
}

