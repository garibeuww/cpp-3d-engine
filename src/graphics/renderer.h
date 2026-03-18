#pragma once

class Entity;
class Camera;

class Renderer
{
public:
    void Draw(Entity& e, Camera& camera);
};