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
    OBB obb(transform);
    physBod.obb = obb;
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
    std::vector<std::pair<PhysicsBody, PhysicsBody>> possibleCollsions = BroadPhaseCollision();
    std::vector<CollisionEvent> collisions;
    for(auto& possibleCollision : possibleCollsions)
    {
        if(CheckCollision(possibleCollision.first, possibleCollision.second))
        { 
            CollisionEvent collEvent;
            collEvent.body1 = possibleCollision.first;
            collEvent.body2 = possibleCollision.second;
            collEvent.collisionNormalBody1 = GetCollisionNormal(possibleCollision.first, possibleCollision.second);
            collEvent.collisionNormalBody2 = GetCollisionNormal(possibleCollision.second, possibleCollision.first);
            collisions.push_back(collEvent);

            if((possibleCollision.first.rigidBody->isStatic && !possibleCollision.second.rigidBody->isStatic) ||
            (!possibleCollision.first.rigidBody->isStatic && possibleCollision.second.rigidBody->isStatic))
            {
                if(possibleCollision.second.rigidBody->isStatic)
                {
                    ResolveCollision(possibleCollision.first, possibleCollision.second);
                }
                else
                {
                    ResolveCollision(possibleCollision.second, possibleCollision.first);
                }
            }
        }
    }
    /*
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
    */
    return collisions;
}

void PhysicsSystem::Integrate(Transform& objectTransform, RigidBodyComponent& objectRigidBody, float dt)
{
    this->dt = dt;
    objectRigidBody.previousPosition = objectTransform.position;
    objectRigidBody.velocity += gravity * dt;
    objectTransform.position += objectRigidBody.velocity * dt;
    
}

std::vector<glm::vec3> PhysicsSystem::GetOBBCorners(OBB obb)
{
     // Get the 4 corners of the OBB
    glm::vec3 x = obb.xAxis * obb.halfWidth;
    glm::vec3 y = obb.yAxis * obb.halfHeight;
    //glm::vec3 z = {0.0f, 0.0f, 0.0f};

    std::vector<glm::vec3> corners = {
        obb.center + x + y,
        obb.center - x + y,
        obb.center - x - y,
        obb.center + x - y
    };
    return corners;
}

glm::vec2 GetMinMaxX(std::vector<glm::vec3> obbCorners)
{
    float minX = obbCorners[0].x;
    float maxX = obbCorners[0].x;
    for(auto& corner : obbCorners)
    {
        if(corner.x <= minX)
        {
            minX = corner.x;
        }
        if(corner.x >= maxX)
        {
            maxX = corner.x;
        }
    }
    return {minX, maxX};
}

std::vector<glm::vec3> PhysicsSystem::GetMinMaxXYZ(std::vector<glm::vec3> obbCorners)
{
    float minX = obbCorners[0].x;
    float maxX = obbCorners[0].x;
    float minY = obbCorners[0].y;
    float maxY = obbCorners[0].y;
    float minZ = obbCorners[0].z;
    float maxZ = obbCorners[0].z;
    for(auto& corner : obbCorners)
    {
        if(corner.x <= minX)
        {
            minX = corner.x;
        }
        if(corner.x >= maxX)
        {
            maxX = corner.x;
        }
        if(corner.y <= minY)
        {
            minY = corner.y;
        }
        if(corner.y >= maxY)
        {
            maxY = corner.y;
        }
        if(corner.y <= minZ)
        {
            minZ = corner.z;
        }
        if(corner.z >= maxZ)
        {
            maxZ = corner.z;
        }
    }
    std::vector<glm::vec3> minMax = {
        {minX, minY, minZ},
        {maxX, maxY, maxZ}
    };
    return minMax;
}

std::vector<std::pair<PhysicsBody, PhysicsBody>> PhysicsSystem::BroadPhaseCollision()
{
    for(auto& physBod : physicsBodies)
    {
        physBod.UpdateOBB();
        std::vector<glm::vec3> minMax = GetMinMaxXYZ(GetOBBCorners(physBod.obb));
        physBod.obb.minX = minMax[0].x;
        physBod.obb.maxX = minMax[1].x;
        physBod.obb.minY = minMax[0].y;
        physBod.obb.maxY = minMax[1].y;
    }
    std::sort(physicsBodies.begin(), physicsBodies.end());
    std::vector<std::pair<PhysicsBody, PhysicsBody>> possibleCollisions;
    std::unordered_map<std::string, PhysicsBody> activeList;
    for(auto& physObj : physicsBodies)
    {
        for(auto& activeObj : activeList)
        {
            if(activeObj.second.obb.maxX < physObj.obb.minX)
            {
                activeList.erase(activeObj.first);
            }
        }
        for(auto& activeObj : activeList)
        {
            if(activeObj.second.obb.minX < physObj.obb.maxX)
            {
                possibleCollisions.push_back(std::make_pair(activeObj.second, physObj));
            }
        }
        activeList[physObj.id] = physObj;
    }
    return possibleCollisions;

    /*
    // 1. Sort objects by their minimum x-coordinate (or any chosen axis)
    Sort(objects, by_min_x_coordinate)

    // 2. Initialize a list to store active objects (those potentially overlapping)
    active_objects = empty_list

    // 3. Iterate through the sorted objects
    for each object in objects:
        // 4. Remove inactive objects from 'active_objects'
        //    An object is inactive if its maximum x-coordinate is less than the current object's minimum x-coordinate
        for each active_obj in active_objects:
            if active_obj.max_x < object.min_x:
                Remove active_obj from active_objects

        // 5. Check for potential overlaps with active objects
        //    For each active object, if their x-intervals overlap, then check for y-interval overlap
        for each active_obj in active_objects:
            if CheckOverlap(object, active_obj): // This function checks for overlap on all axes
                // If overlap confirmed, report as a potential collision pair
                ReportPotentialCollision(object, active_obj)

        // 6. Add the current object to 'active_objects'
        Add object to active_objects
    */

}

bool PhysicsSystem::CheckCollision(PhysicsBody& physBod1, PhysicsBody& physBod2)
{
    /*   
    Each OBB needs:
        center → the rectangle’s center in world space.
        halfExtents → half-width and half-height.
        rotation (radians or degrees).
        axes → you can compute two normalized direction vectors:
            xAxis = (cosθ, sinθ)
            yAxis = (-sinθ, cosθ) (perpendicular)
    */
    OBB obb1 = physBod1.obb;
    OBB obb2 = physBod2.obb;

    glm::vec3 axes[4] = {obb1.xAxis, obb2.xAxis, obb1.yAxis, obb2.yAxis};

    for(auto& axis : axes)
    {
        glm::vec2 projection1 = ProjectOBB(obb1, axis);
        glm::vec2 projection2 = ProjectOBB(obb2, axis);
        //If projection1Max >= projection2Min && projection2Max >= projection1Min overlap exists
        //If not then there is definitely no collision.
        if(!(projection1.y >= projection2.x && projection2.y >= projection1.x))
        {
            return false;
        }
    }

    return true;
   
    //AABB
    /*
    return  objectTransform.position.x - objectTransform.scale.x / 2 <= staticObjectTransform.position.x + staticObjectTransform.scale.x / 2 &&
            objectTransform.position.x + objectTransform.scale.x / 2 >= staticObjectTransform.position.x - staticObjectTransform.scale.x / 2  &&
            objectTransform.position.y - objectTransform.scale.y / 2 <= staticObjectTransform.position.y + staticObjectTransform.scale.y / 2 &&
            objectTransform.position.y + objectTransform.scale.y / 2 >= staticObjectTransform.position.y - staticObjectTransform.scale.y / 2;
    */ 
}

glm::vec2 PhysicsSystem::ProjectOBB(const OBB& obb, glm::vec3 axis)
{
   std::vector<glm::vec3> corners = GetOBBCorners(obb);
    /*
    // Get the 4 corners of the OBB
    glm::vec3 x = obb.xAxis * obb.halfWidth;
    glm::vec3 y = obb.yAxis * obb.halfHeight;
    //glm::vec3 z = {0.0f, 0.0f, 0.0f};

    glm::vec3 corners[4] = {
        obb.center + x + y,
        obb.center - x + y,
        obb.center - x - y,
        obb.center + x - y
    };
    */
    // Project all corners onto axis
    float min = glm::dot(corners[0],axis);
    float max = min;
    for (int i = 1; i < 4; i++) {
        float p = glm::dot(corners[i], axis);
        if (p < min) min = p;
        if (p > max) max = p;
    }

    return { min, max };
}

glm::vec2 PhysicsSystem::GetCollisionNormal(PhysicsBody& physBod1, PhysicsBody& physBod2)
{
    Transform& objectTransform = *physBod1.transform;
    Transform& object2Transform = *physBod2.transform;
    RigidBodyComponent& objectRigidBody = *physBod1.rigidBody;
    RigidBodyComponent& object2RigidBody = *physBod2.rigidBody;
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

    /*
    float aLeft   = objectTransform.position.x - objectTransform.scale.x / 2;
    float aRight  = objectTransform.position.x + objectTransform.scale.x / 2;
    float aBottom = objectTransform.position.y - objectTransform.scale.y / 2;
    float aTop    = objectTransform.position.y + objectTransform.scale.y / 2;

    float bLeft   = object2Transform.position.x - object2Transform.scale.x / 2;
    float bRight  = object2Transform.position.x + object2Transform.scale.x / 2;
    float bBottom = object2Transform.position.y - object2Transform.scale.y / 2;
    float bTop    = object2Transform.position.y + object2Transform.scale.y / 2;
    */
    float aLeft   = physBod1.obb.minX;
    float aRight  = physBod1.obb.maxX;
    float aBottom = physBod1.obb.minY;
    float aTop    = physBod1.obb.maxY;

    float bLeft   = physBod2.obb.minX;
    float bRight  = physBod2.obb.maxX;
    float bBottom = physBod2.obb.minY;
    float bTop    = physBod2.obb.maxY;

    float overlapX = std::min(aRight, bRight) - std::max(aLeft, bLeft);
    float overlapY = std::min(aTop, bTop) - std::max(aBottom, bBottom);

    if (overlapX < overlapY) {
        return (objectTransform.position.x < object2Transform.position.x) ? glm::vec2(-1, 0) : glm::vec2(1, 0);
    } else {
        return (objectTransform.position.y < object2Transform.position.y) ? glm::vec2(0, -1) : glm::vec2(0, 1);
    }

}

void PhysicsSystem::ResolveCollision(PhysicsBody& physBod1, PhysicsBody& physBod2)
{
    Transform& objectTransform = *physBod1.transform;
    Transform& object2Transform = *physBod2.transform;
    RigidBodyComponent& objectRigidBody = *physBod1.rigidBody;
    RigidBodyComponent& object2RigidBody = *physBod2.rigidBody;
    //if(CheckCollision(physBod1, physBod2))
           
    // Calculate half extents and sides
    /*
    float aLeft   = objectTransform.position.x - objectTransform.scale.x / 2;
    float aRight  = objectTransform.position.x + objectTransform.scale.x / 2;
    float aBottom = objectTransform.position.y - objectTransform.scale.y / 2;
    float aTop    = objectTransform.position.y + objectTransform.scale.y / 2;

    float bLeft   = object2Transform.position.x - object2Transform.scale.x / 2;
    float bRight  = object2Transform.position.x + object2Transform.scale.x / 2;
    float bBottom = object2Transform.position.y - object2Transform.scale.y / 2;
    float bTop    = object2Transform.position.y + object2Transform.scale.y / 2;
    */
    float aLeft   = physBod1.obb.minX;
    float aRight  = physBod1.obb.maxX;
    float aBottom = physBod1.obb.minY;
    float aTop    = physBod1.obb.maxY;

    float bLeft   = physBod2.obb.minX;
    float bRight  = physBod2.obb.maxX;
    float bBottom = physBod2.obb.minY;
    float bTop    = physBod2.obb.maxY;

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