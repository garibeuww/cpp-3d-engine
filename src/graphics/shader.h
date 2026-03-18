#pragma once
#include <glad/glad.h>
#include <unordered_map>
#include <string>
#include "../math/vec3.h"

class Shader
{
public:
    Shader(const char* vertexSource, const char* fragmentSource);
    ~Shader();

    void Use();

    void SetMat4(const std::string& name, const float* value);
    void SetInt(const std::string& name, int value);
	void SetVec3(const std::string& name, const Vec3& value);

private:
    unsigned int program;
    std::unordered_map<std::string, int> uniformCache;

    int GetUniformLocation(const std::string& name);
};