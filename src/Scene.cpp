#include "Scene.h"
#include "Component\RendererComponent.h"

Scene::Scene(unsigned int width, unsigned int height)
	: m_entities(std::vector<std::unique_ptr<Entity>>()), m_camera(new Camera(glm::vec3(0.0f, 0.0f, 6.0f), width, height))
{
	// create the rubiks cube and respective components
	Entity* entity = CreateEntity("Rubiks Cube");
	entity->AddComponent(new RendererComponent(entity));
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

