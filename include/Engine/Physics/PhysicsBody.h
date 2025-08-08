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
};