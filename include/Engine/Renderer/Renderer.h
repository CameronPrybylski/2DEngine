#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <Engine/Renderer/Mesh.h>
#include <Engine/Scene/GameObject.h>
#include <Engine/Core/AssetManager.h>

class Renderer{

public:
    Renderer();
    ~Renderer();
    void DrawQuad(const Mesh& mesh, const Transform& modelMatrix, Shader& shader, glm::mat4 projection);
    void Clear();

private:

};