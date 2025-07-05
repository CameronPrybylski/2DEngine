#include <Engine/Physics/PhysicsSystem.h>

PhysicsSystem::PhysicsSystem()
{
}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::Init(glm::vec3 gravity)
{
    this->gravity = gravity;
}