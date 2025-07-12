#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 viewPosition{0.0f};
    glm::vec3 viewRotation{0.0f};
    glm::mat4 projection;
    glm::mat4 vp;

    glm::mat4 GetViewMatrix() const {
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, viewPosition);
        view = glm::rotate(view, glm::radians(viewRotation.x), glm::vec3(1,0,0));
        view = glm::rotate(view, glm::radians(viewRotation.y), glm::vec3(0,1,0));
        view = glm::rotate(view, glm::radians(viewRotation.z), glm::vec3(0,0,1));
        view = glm::inverse(view);
        return view;
    }

    void SetOrthoProjMat(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
    {
        projection = glm::ortho(minX, maxX, minY, maxY,  minZ, maxZ);
    }

    void SetVP()
    {
        vp = projection * GetViewMatrix();
    }
};