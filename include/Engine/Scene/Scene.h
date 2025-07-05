#pragma once

#include <SDL.h>
#include <Engine/Core/Input.h>
#include<Engine/Scene/GameObject.h>
#include<Engine/Renderer/Renderer.h>

class Scene {
public: 
    void AddObject(std::string nameOfObject, std::shared_ptr<GameObject> object);

    virtual void OnEvent(const Input& input);

    virtual void OnUpdate(float dt);

    virtual void DrawObjects(Renderer& renderer);

    void SetOrthoProjMat(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);

protected:
    std::vector<std::shared_ptr<GameObject>> objectList;
    std::unordered_map<std::string, std::shared_ptr<GameObject>> objectMap;
    glm::mat4 projection;
};