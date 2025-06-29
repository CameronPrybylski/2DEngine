#pragma once
#include <Engine/Renderer/QuadMesh.h>
#include <Engine/Scene/Transform.h>

class GameObject {

public:
    GameObject();
    ~GameObject();

    std::shared_ptr<Mesh> mesh;
    Transform transform;
    std::string shaderName;


};