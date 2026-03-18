#include "scene.h"
#include "../graphics/renderer.h"

void Scene::Add(Entity* entity)
{
    entities.push_back(entity);
}

void Scene::Render(Renderer& renderer, Camera& camera)
{
    for (auto e : entities)
    {
        renderer.Draw(*e, camera);
    }
}