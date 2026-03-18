#include "resource_manager.h"
#include "../math/vec2.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <filesystem>

// INIT MAPS
std::unordered_map<std::string, Mesh*> ResourceManager::meshes;
std::unordered_map<std::string, Shader*> ResourceManager::shaders;
std::unordered_map<std::string, Texture*> ResourceManager::textures;
std::unordered_map<std::string, Material*> ResourceManager::materials;

// MESH
Mesh* ResourceManager::LoadMesh(const std::string& name, const std::string& path)
{
    if (meshes.count(name))
        return meshes[name];

    std::vector<float> vertices;

    std::vector<Vec3> positions;
    std::vector<Vec3> normals;
    std::vector<Vec2> uvs;

    std::ifstream file(path);
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "v")
        {
            float x, y, z;
            ss >> x >> y >> z;
            positions.emplace_back(x, y, z);
        }
        else if (type == "vt")
        {
            float u, v;
            ss >> u >> v;
            uvs.emplace_back(u, v);
        }
        else if (type == "vn")
        {
            float x, y, z;
            ss >> x >> y >> z;
            normals.emplace_back(x, y, z);
        }
        else if (type == "f")
        {
            for (int i = 0; i < 3; i++)
            {
                std::string vert;
                ss >> vert;

                std::stringstream vss(vert);
                std::string p, t, n;

                std::getline(vss, p, '/');
                std::getline(vss, t, '/');
                std::getline(vss, n, '/');

                int pi = std::stoi(p) - 1;
                int ti = t.empty() ? 0 : std::stoi(t) - 1;
                int ni = n.empty() ? 0 : std::stoi(n) - 1;

                Vec3 pos = positions[pi];
                Vec2 uv = uvs[ti];
                Vec3 norm = normals[ni];

                vertices.push_back(pos.x);
                vertices.push_back(pos.y);
                vertices.push_back(pos.z);

                vertices.push_back(norm.x);
                vertices.push_back(norm.y);
                vertices.push_back(norm.z);

                vertices.push_back(uv.x);
                vertices.push_back(uv.y);
            }
        }
    }

    Mesh* mesh = new Mesh(vertices);
    meshes[name] = mesh;
    return mesh;
}

// SHADER
Shader* ResourceManager::LoadShader(
    const std::string& name,
    const std::string& vsPath,
    const std::string& fsPath)
{
    if (shaders.count(name))
        return shaders[name];

    // 🔧 Normaliza paths
    std::filesystem::path vs = std::filesystem::u8path(vsPath);
    std::filesystem::path fs = std::filesystem::u8path(fsPath);

    // 🔍 Debug útil
    std::cout << "[VS] " << vs << "\n";
    std::cout << "[FS] " << fs << "\n";

    // 🚨 Validação antes de abrir
    if (!std::filesystem::exists(vs))
    {
        std::cerr << "Vertex shader nao encontrado: " << vs << "\n";
        return nullptr;
    }

    if (!std::filesystem::exists(fs))
    {
        std::cerr << "Fragment shader nao encontrado: " << fs << "\n";
        return nullptr;
    }

    // 📂 Abertura com flags explícitas
    std::ifstream vFile(vs, std::ios::in);
    std::ifstream fFile(fs, std::ios::in);

    if (!vFile || !fFile)
    {
        std::cerr << "Erro abrindo arquivos shader!\n";
        std::cerr << "VS fail: " << vFile.fail() << " bad: " << vFile.bad() << "\n";
        std::cerr << "FS fail: " << fFile.fail() << " bad: " << fFile.bad() << "\n";
        return nullptr;
    }

    // 📖 Leitura segura
    std::stringstream vStream, fStream;
    vStream << vFile.rdbuf();
    fStream << fFile.rdbuf();

    std::string vCode = vStream.str();
    std::string fCode = fStream.str();

    if (vCode.empty() || fCode.empty())
    {
        std::cerr << "Shader vazio (possivel erro de leitura)\n";
        return nullptr;
    }

    // 🧠 Criação
    Shader* shader = new Shader(vCode.c_str(), fCode.c_str());
    shaders[name] = shader;

    return shader;
}

// TEXTURE
Texture* ResourceManager::LoadTexture(const std::string& name, const std::string& path)
{
    if (textures.count(name))
        return textures[name];

    Texture* tex = new Texture(path);
    textures[name] = tex;
    return tex;
}

// MATERIAL
Material* ResourceManager::CreateMaterial(const std::string& name)
{
    if (materials.count(name))
        return materials[name];

    Material* mat = new Material();
    materials[name] = mat;
    return mat;
}

// CLEANUP
void ResourceManager::Clear()
{
    for (auto& p : meshes) delete p.second;
    for (auto& p : shaders) delete p.second;
    for (auto& p : textures) delete p.second;
    for (auto& p : materials) delete p.second;

    meshes.clear();
    shaders.clear();
    textures.clear();
    materials.clear();
}