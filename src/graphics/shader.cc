#include "shader.h"
#include <glad/glad.h>
#include <iostream>

static void CheckCompile(unsigned int shader)
{
    int success;
    char infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "Shader compile error:\n" << infoLog << std::endl;
    }
}

Shader::Shader(const char* vertexSource, const char* fragmentSource)
{
    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexSource, nullptr);
    glCompileShader(vs);
    CheckCompile(vs);

    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentSource, nullptr);
    glCompileShader(fs);
    CheckCompile(fs);

    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cout << "Program link error:\n" << infoLog << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader()
{
    glDeleteProgram(program);
}

void Shader::Use()
{
    glUseProgram(program);
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (uniformCache.find(name) != uniformCache.end())
        return uniformCache[name];

    int location = glGetUniformLocation(program, name.c_str());
    uniformCache[name] = location;
    return location;
}

void Shader::SetMat4(const std::string& name, const float* value)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, value);
}

void Shader::SetVec3(const std::string& name, const Vec3& value)
{
    GLint location = glGetUniformLocation(program, name.c_str());
    glUniform3f(location, value.x, value.y, value.z);
}

void Shader::SetInt(const std::string& name, int value)
{
	GLint location = glGetUniformLocation(program, name.c_str());
	glUniform1i(location, value);
}