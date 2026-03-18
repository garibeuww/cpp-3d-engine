#include "material.h"

Material::Material()
{
    shader = nullptr;
    texture = nullptr;
    color = Vec3(1.0f, 1.0f, 1.0f);
}

void Material::Bind() const
{
    if (shader)
        shader->Use();

    if (texture)
        texture->Bind(0);

    if (shader)
    {
        shader->SetVec3("uColor", color);
        shader->SetInt("uTexture", 0);
    }
}