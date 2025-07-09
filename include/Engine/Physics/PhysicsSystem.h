#pragma once

#include <Engine/Scene/Transform.h>

class PhysicsSystem {

public:
    PhysicsSystem();
    ~PhysicsSystem();

    void Init(glm::vec3 gravity);
    void Integrate(Transform& objectTransform, RigidBodyComponent& objectRigidBody, float dt);
    bool CheckCollision(Transform& objectTransform, Transform& groundTransform);
    void ResolveCollision(Transform& objectTransform, RigidBodyComponent& objectRigidBody, Transform& object2Transform, RigidBodyComponent& object2RigidBody);
    glm::vec2 GetCollisionNormal(Transform& objectTransform, Transform& object2Transform);//, RigidBodyComponent& object2RigidBody);

private:
    glm::vec3 gravity;
    //glm::vec3 drg
    float dt;
};