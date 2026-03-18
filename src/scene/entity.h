#pragma once

#include "../core/transform.h"
#include "../math/vec3.h"
#include "../math/mat4.h"
#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../graphics/material.h"

class Mesh;
class Shader;
class Texture;

class Entity
{
public:
	Transform transform;

    Mesh* mesh = nullptr;
	Material* material;

    Mat4 GetModelMatrix();
};