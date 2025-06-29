#pragma once

#include<Engine/Scene/GameObject.h>
#include<Engine/Renderer/Renderer.h>

class Scene {
public: 
    void AddObject(std::shared_ptr<GameObject> object);

    void Update(float dt);

    void DrawQuads(Renderer& renderer);

    void SetOrthoProjMat(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);

private:
    std::vector<std::shared_ptr<GameObject>> objects;
    glm::mat4 projection;
};