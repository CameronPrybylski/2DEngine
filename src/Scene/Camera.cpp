#include <Engine/Scene/Camera.h>

Camera::Camera(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
    SetOrthoProjMat(minX, maxX, minY, maxY, minZ, maxZ);
    SetVP();
}

void Camera::Create(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
    SetOrthoProjMat(minX, maxX, minY, maxY, minZ, maxZ);
    SetVP();
}

void Camera::SetViewMatrix()
{
    view = glm::mat4(1.0f);
    view = glm::translate(view, viewPosition);
    view = glm::rotate(view, glm::radians(viewRotation.x), glm::vec3(1,0,0));
    view = glm::rotate(view, glm::radians(viewRotation.y), glm::vec3(0,1,0));
    view = glm::rotate(view, glm::radians(viewRotation.z), glm::vec3(0,0,1));
    view = glm::inverse(view);
}

void Camera::SetOrthoProjMat(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
    projection = glm::ortho(minX, maxX, minY, maxY,  minZ, maxZ);
}

void Camera::SetVP()
{
    vp = projection * GetViewMatrix();
}
