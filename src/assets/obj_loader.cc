#include "obj_loader.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

#include "../math/vec3.h"
#include "../math/vec2.h"

Mesh* OBJLoader::Load(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
		std::cout << "ERRO: não conseguiu abrir OBJ:" << path << std::endl;
        return nullptr;

    std::vector<Vec3> positions;
    std::vector<Vec2> uvs;
    std::vector<Vec3> normals;

    std::vector<float> vertices;

    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;

        // posição
        if (prefix == "v")
        {
            Vec3 pos;
            ss >> pos.x >> pos.y >> pos.z;
            positions.push_back(pos);
        }

        // UV
        else if (prefix == "vt")
        {
            Vec2 uv;
            ss >> uv.x >> uv.y;
            uvs.push_back(uv);
        }

        // normal
        else if (prefix == "vn")
        {
            Vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        }

        // face
        else if (prefix == "f")
        {
            std::string v1, v2, v3;
            ss >> v1 >> v2 >> v3;

            std::vector<std::string> face = { v1, v2, v3 };

            for (auto& v : face)
            {
                std::stringstream vs(v);
                std::string iPos, iUV, iNorm;

                std::getline(vs, iPos, '/');
                std::getline(vs, iUV, '/');
                std::getline(vs, iNorm, '/');

                int posIndex = std::stoi(iPos) - 1;
                int uvIndex  = std::stoi(iUV) - 1;
                int normIndex = std::stoi(iNorm) - 1;

                Vec3 pos = positions[posIndex];
                Vec2 uv  = uvs[uvIndex];
                Vec3 norm = normals[normIndex];

                // layout: pos (3) + normal (3) + uv (2)
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

    return new Mesh(vertices);
}