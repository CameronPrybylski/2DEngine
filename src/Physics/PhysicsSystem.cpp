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

void PhysicsSystem::RegisterBody(Transform& transform, RigidBodyComponent& rigidBody, std::string id)
{
    PhysicsBody physBod;
    physBod.transform = &transform;
    physBod.rigidBody = &rigidBody;
    physBod.id = id;
    physicsBodies.push_back(physBod);
}

std::vector<CollisionEvent> PhysicsSystem::Update(float dt)
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
                if(staticObj.rigidBody->isStatic && staticObj.transform != obj.transform)
                //if(staticObj.transform != obj.transform)
                {   
                    ResolveCollision(*obj.transform, *obj.rigidBody, *staticObj.transform, *staticObj.rigidBody);
                }

            }            
        }
    }

    std::vector<CollisionEvent> collisions;
    for(int i = 0; i < physicsBodies.size(); i++)
    {   
        auto& dynObj1 = physicsBodies[i];
        for(int j = i + 1; j < physicsBodies.size(); j++)
        {
            auto& dynObj2 = physicsBodies[j];
            if(CheckCollision(*dynObj1.transform, *dynObj2.transform))
            {
                CollisionEvent collEvent;
                collEvent.body1 = dynObj1;
                collEvent.body2 = dynObj2;
                collEvent.collisionNormalBody1 = GetCollisionNormal(*dynObj1.transform, *dynObj2.transform);
                collEvent.collisionNormalBody2 = GetCollisionNormal(*dynObj2.transform, *dynObj1.transform);
                collisions.push_back(collEvent);
            }
        }
    }
    return collisions;
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
    return  objectTransform.position.x - objectTransform.scale.x / 2 <= staticObjectTransform.position.x + staticObjectTransform.scale.x / 2 &&
            objectTransform.position.x + objectTransform.scale.x / 2 >= staticObjectTransform.position.x - staticObjectTransform.scale.x / 2  &&
            objectTransform.position.y - objectTransform.scale.y / 2 <= staticObjectTransform.position.y + staticObjectTransform.scale.y / 2 &&
            objectTransform.position.y + objectTransform.scale.y / 2 >= staticObjectTransform.position.y - staticObjectTransform.scale.y / 2;
}

glm::vec2 PhysicsSystem::GetCollisionNormal(Transform& objectTransform, Transform& object2Transform)
{
    /*
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
    */

    float aLeft   = objectTransform.position.x - objectTransform.scale.x / 2;
    float aRight  = objectTransform.position.x + objectTransform.scale.x / 2;
    float aBottom = objectTransform.position.y - objectTransform.scale.y / 2;
    float aTop    = objectTransform.position.y + objectTransform.scale.y / 2;

    float bLeft   = object2Transform.position.x - object2Transform.scale.x / 2;
    float bRight  = object2Transform.position.x + object2Transform.scale.x / 2;
    float bBottom = object2Transform.position.y - object2Transform.scale.y / 2;
    float bTop    = object2Transform.position.y + object2Transform.scale.y / 2;

    float overlapX = std::min(aRight, bRight) - std::max(aLeft, bLeft);
    float overlapY = std::min(aTop, bTop) - std::max(aBottom, bBottom);

    if (overlapX < overlapY) {
        return (objectTransform.position.x < object2Transform.position.x) ? glm::vec2(-1, 0) : glm::vec2(1, 0);
    } else {
        return (objectTransform.position.y < object2Transform.position.y) ? glm::vec2(0, -1) : glm::vec2(0, 1);
    }

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