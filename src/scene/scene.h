#pragma once

#include <vector>
#include "entity.h"

class Scene
{
public:
    std::vector<Entity*> entities;

    void Add(Entity* entity);
    void Render(class Renderer& renderer, class Camera& camera);
};