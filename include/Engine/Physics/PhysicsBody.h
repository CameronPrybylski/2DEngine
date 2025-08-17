#pragma once

#include <Engine/Scene/Transform.h>
#include <string>

struct PhysicsBody 
{
    Transform* transform;
    RigidBodyComponent* rigidBody;
    std::string id;
};

struct CollisionEvent
{
    PhysicsBody body1;
    PhysicsBody body2;
    glm::vec2 collisionNormalBody1;
    glm::vec2 collisionNormalBody2;
};