#pragma once

#include <Engine/Scene/Transform.h>
#include <string>
#include <cmath>

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

struct OBB
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
    OBB(const Transform& transform)
    {
        center = glm::vec3(transform.position.x, transform.position.y, transform.position.z);
        halfWidth = transform.scale.x / 2;
        halfHeight = transform.scale.y / 2;
        rotation = transform.rotation;
        xAxis = glm::vec3(std::cos(glm::radians(rotation.z)), std::sin(glm::radians(rotation.z)), 0.0f);
        yAxis = glm::vec3(-1 * std::sin(glm::radians(rotation.z)), std::cos(glm::radians(rotation.z)), 0.0f);
    }
    glm::vec3 center;
    float halfWidth;
    float halfHeight;
    glm::vec3 rotation;
    glm::vec3 xAxis;
    glm::vec3 yAxis;

};