#include <Engine/Renderer/Ibo.h>

Ibo::Ibo(){}

Ibo::~Ibo(){}

void Ibo::Create(std::vector<unsigned int> indices)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void Ibo::Bind()const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void Ibo::Unbind()const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Ibo::Delete()
{
    glDeleteBuffers(1, &ID);
}