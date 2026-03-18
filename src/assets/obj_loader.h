#pragma once
#include <string>
#include "../graphics/mesh.h"

class OBJLoader
{
public:
    static Mesh* Load(const std::string& path);
};