#pragma once

#include <Engine/Scene/Transform.h>

struct PhysicsBody 
{
    Transform* transform;
    RigidBodyComponent* rigidBody;
};