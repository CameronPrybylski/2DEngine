#pragma once
#include <Engine/Renderer/Renderer.h>
#include <Engine/Renderer/QuadMesh.h>
#include <Engine/Scene/Transform.h>
#include <Engine/Core/Input.h>

class GameObject {

public:
    GameObject();
    ~GameObject();

    virtual void OnEvent(const Input& input);
    virtual void Update(float dt);
    virtual void Render(Renderer& renderer, glm::mat4 projection);

    std::shared_ptr<Mesh> mesh;
    Transform transform;
    RigidBodyComponent rigidBody;
    std::string shaderName;


};