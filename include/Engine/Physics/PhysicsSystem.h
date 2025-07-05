#pragma once

#include <Engine/Scene/Transform.h>

class PhysicsSystem {

public:
    PhysicsSystem();
    ~PhysicsSystem();

    void Init(glm::vec3 gravity);

private:
    glm::vec3 gravity;
};