//
// Created by wyrex on 8/16/25.
//

#ifndef FORE_CAMERA_H
#define FORE_CAMERA_H

#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;

    Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f),
           glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f))
        : Position(pos), Front(front), Up(up) {}

    glm::mat4 getViewMatrix() {
        return glm::lookAt(Position, Position + Front, Up);
    }
};

extern Camera camera;

#endif //FORE_CAMERA_H
