#include <Engine/Physics/PhysicsSystem.h>
#include <iostream>

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

void PhysicsSystem::RegisterBody(Transform& transform, RigidBodyComponent& rigidBody)
{
    PhysicsBody physBod;
    physBod.transform = &transform;
    physBod.rigidBody = &rigidBody;
    physicsBodies.push_back(physBod);
}

void PhysicsSystem::Update(float dt)
{
    for(auto& obj : physicsBodies)
    {   
        if(!obj.rigidBody->isStatic)
        {
            Integrate(*obj.transform, *obj.rigidBody, dt);
        }
    }
    for(auto& obj : physicsBodies)
    {
        if(!obj.rigidBody->isStatic)
        {
            for(auto& staticObj : physicsBodies)
            {
                if(staticObj.rigidBody->isStatic)
                //if(staticObj != obj)
                {   
                    ResolveCollision(*obj.transform, *obj.rigidBody, *staticObj.transform, *staticObj.rigidBody);
                }

            }            
        }
    }
}

void PhysicsSystem::Integrate(Transform& objectTransform, RigidBodyComponent& objectRigidBody, float dt)
{
    this->dt = dt;
    objectRigidBody.previousPosition = objectTransform.position;
    objectRigidBody.velocity += gravity * dt;
    objectTransform.position += objectRigidBody.velocity * dt;
    
}

bool PhysicsSystem::CheckCollision(Transform& objectTransform, Transform& staticObjectTransform)
{
    return  objectTransform.position.x - objectTransform.scale.x / 2 < staticObjectTransform.position.x + staticObjectTransform.scale.x / 2 &&
            objectTransform.position.x + objectTransform.scale.x / 2 > staticObjectTransform.position.x - staticObjectTransform.scale.x / 2  &&
            objectTransform.position.y - objectTransform.scale.y / 2 < staticObjectTransform.position.y + staticObjectTransform.scale.y / 2 &&
            objectTransform.position.y + objectTransform.scale.y / 2 > staticObjectTransform.position.y - staticObjectTransform.scale.y / 2;
}

glm::vec2 PhysicsSystem::GetCollisionNormal(Transform& objectTransform, Transform& object2Transform)
{
    float dx = (objectTransform.position.x - object2Transform.position.x);
    float px = (objectTransform.scale.x + object2Transform.scale.x) - std::abs(dx);

    float dy = (objectTransform.position.y - object2Transform.position.y);
    float py = (objectTransform.scale.y + object2Transform.scale.y) - std::abs(dy);
    
    glm::vec2 normal;
    
    if (px < py) {
         // Resolve on x-axis
        if (dx > 0)
            normal = glm::vec2(1, 0);  // Collided from left
        else
            normal = glm::vec2(-1, 0); // Collided from right
    }
    else {
        // Resolve on y-axis
        if (dy > 0)
            normal = glm::vec2(0, 1);  // Collided from below
        else
            normal = glm::vec2(0, -1); // Collided from above
    }

    return normal;

}

void PhysicsSystem::ResolveCollision(Transform& objectTransform, RigidBodyComponent& objectRigidBody, Transform& object2Transform, RigidBodyComponent& object2RigidBody)
{
    if(CheckCollision(objectTransform, object2Transform))
    {
        
        // Calculate half extents and sides
        float aLeft   = objectTransform.position.x - objectTransform.scale.x / 2;
        float aRight  = objectTransform.position.x + objectTransform.scale.x / 2;
        float aBottom = objectTransform.position.y - objectTransform.scale.y / 2;
        float aTop    = objectTransform.position.y + objectTransform.scale.y / 2;

        float bLeft   = object2Transform.position.x - object2Transform.scale.x / 2;
        float bRight  = object2Transform.position.x + object2Transform.scale.x / 2;
        float bBottom = object2Transform.position.y - object2Transform.scale.y / 2;
        float bTop    = object2Transform.position.y + object2Transform.scale.y / 2;

        // Compute overlaps
        float overlapX = std::min(aRight, bRight) - std::max(aLeft, bLeft);
        float overlapY = std::min(aTop, bTop) - std::max(aBottom, bBottom);

        // Resolve along smallest axis
        if (overlapX < overlapY) {
            if (objectTransform.position.x < object2Transform.position.x) {
                objectTransform.position.x -= overlapX;
                objectRigidBody.velocity.x = 0;
            } else {
                objectTransform.position.x += overlapX;
                objectRigidBody.velocity.x = 0;
            }
        } else {
            if (objectTransform.position.y < object2Transform.position.y) {
                objectTransform.position.y -= overlapY;
                objectRigidBody.velocity.y = 0;
            } else {
                objectTransform.position.y += overlapY;
                objectRigidBody.velocity.y = 0;
            }
        }
    }
}