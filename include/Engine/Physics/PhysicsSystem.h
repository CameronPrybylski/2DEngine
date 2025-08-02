#pragma once

//#include <Engine/Scene/GameObject.h>
#include <Engine/Physics/PhysicsBody.h>
#include <vector>

class PhysicsSystem {

public:
    PhysicsSystem();
    ~PhysicsSystem();

    void Init(glm::vec3 gravity);
    void SetGravity(glm::vec3 gravity){this->gravity = gravity;}
    void Update(float dt);
    void Integrate(Transform& objectTransform, RigidBodyComponent& objectRigidBody, float dt);
    bool CheckCollision(Transform& objectTransform, Transform& groundTransform);
    void ResolveCollision(Transform& objectTransform, RigidBodyComponent& objectRigidBody, Transform& object2Transform, RigidBodyComponent& object2RigidBody);
    glm::vec2 GetCollisionNormal(Transform& objectTransform, Transform& object2Transform);//, RigidBodyComponent& object2RigidBody);
    void RegisterBody(Transform& transform, RigidBodyComponent& rigidBody);
    void ClearBodies(){physicsBodies.clear();}

private:
    glm::vec3 gravity;
    std::vector<PhysicsBody> physicsBodies;
    //glm::vec3 drg
    float dt;
};