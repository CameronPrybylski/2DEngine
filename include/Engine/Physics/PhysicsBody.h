#pragma once

#include <Engine/Scene/Transform.h>

struct PhysicsBody 
{
    Transform* transform;
    RigidBodyComponent* rigidBody;
};

struct CollisionEvent
{
    PhysicsBody body1;
    PhysicsBody body2;
    glm::vec2 collisionNormalBody1;
    glm::vec2 collisionNormalBody2;
};