#pragma once
#include <glad/glad.h>
#include <vector>

class Mesh
{
public:
    Mesh(const std::vector<float>& vertices);
    ~Mesh();
	
	void Draw() const;
    void Bind() const;
    void Unbind() const;
    unsigned int GetVAO() const { return VAO; }
    size_t GetVertexCount() const { return vertexCount; }

private:
    unsigned int VAO, VBO;
    size_t vertexCount;
};