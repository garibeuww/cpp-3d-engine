#pragma once
#include "shader.h"
#include "texture.h"
#include "../math/vec3.h"

class Material
{
public:
    Shader* shader;
    Texture* texture;

    Vec3 color;

    Material();

    void Bind() const;
};