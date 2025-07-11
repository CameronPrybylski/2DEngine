#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 position{0.0f};
    glm::vec3 rotation{0.0f};

    glm::mat4 GetViewMatrix() const {
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, position);
        view = glm::rotate(view, glm::radians(rotation.x), glm::vec3(1,0,0));
        view = glm::rotate(view, glm::radians(rotation.y), glm::vec3(0,1,0));
        view = glm::rotate(view, glm::radians(rotation.z), glm::vec3(0,0,1));
        view = glm::inverse(view);
        return view;
    }
};