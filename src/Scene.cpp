#include "Scene.h"
#include "Component\RendererComponent.h"

Scene::Scene(unsigned int width, unsigned int height)
	: m_entities(std::vector<std::unique_ptr<Entity>>()), m_camera(new Camera(glm::vec3(0.0f, 0.0f, 6.0f), width, height))
{
	// create the rubiks cube and respective components
	Entity* entity = CreateEntity("Rubiks Cube");
	entity->AddComponent(new RendererComponent(entity, glm::vec3(0.1f, 0.9f, 0.1f)));
	entity->GetTransform()->SetPosition(glm::vec3(1.0f, 0.0f, 0.0f));

	Entity* entity1 = CreateEntity("Rubiks Cube 1");
	entity1->AddComponent(new RendererComponent(entity1, glm::vec3(0.85f, 0.4f, 0.01f)));
	entity1->GetTransform()->SetPosition(glm::vec3(1.0f, 1.0f, 1.0f));
	entity1->GetTransform()->SetRotation(glm::vec3(45.0f, 45.0f, 45.0f));

	Entity* entity2 = CreateEntity("Rubiks Cube 2");
	entity2->AddComponent(new RendererComponent(entity2, glm::vec3(0.85f, 0.85f, 0.08f)));
	entity2->GetTransform()->SetPosition(glm::vec3(-2.0f, 1.0f, 0.0f));
	entity2->GetTransform()->SetRotation(glm::vec3(45.0f, 45.0f, 45.0f));
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

