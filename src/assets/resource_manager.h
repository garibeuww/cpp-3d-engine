#pragma once
#include <unordered_map>
#include <string>

#include "../graphics/mesh.h"
#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../graphics/material.h"

class ResourceManager
{
public:
    static std::unordered_map<std::string, Mesh*> meshes;
    static std::unordered_map<std::string, Shader*> shaders;
    static std::unordered_map<std::string, Texture*> textures;
    static std::unordered_map<std::string, Material*> materials;

    static Mesh* LoadMesh(const std::string& name, const std::string& path);
    static Shader* LoadShader(const std::string& name, const std::string& vs, const std::string& fs);
    static Texture* LoadTexture(const std::string& name, const std::string& path);
    static Material* CreateMaterial(const std::string& name);

    static void Clear();
};