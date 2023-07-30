#pragma once

#include <vector>
#include "Entity\Entity.h"
#include <memory>
#include "Camera.h"
#include <string>

class Scene
{
public :
	Scene(unsigned int width = 0, unsigned int height = 0);
	~Scene();

	void Update();
	void Render();

	Entity* CreateEntity(std::string name);
	void RemoveEntity(Entity* entity);

	Camera* GetCamera() const { return m_camera.get(); }

private:
	std::vector<std::unique_ptr<Entity>> m_entities;
	std::unique_ptr<Camera> m_camera;
};

