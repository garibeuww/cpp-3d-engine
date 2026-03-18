#pragma once
#include <string>
#include <glad/glad.h>

class Texture
{
public:
    GLuint ID;

    Texture(const std::string& path);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
};