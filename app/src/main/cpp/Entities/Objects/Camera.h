#ifndef FORE_CAMERA_H
#define FORE_CAMERA_H

#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include <cmath>

class Camera {
public:
    float width;
    float height;

    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;

    glm::vec3 Rotation;

    Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f),
           glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f))
            : Position(pos), Front(front), Up(up), Rotation(0.0f, -90.0f, 0.0f) {}

    glm::mat4 getViewMatrix() {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void setPosition(const glm::vec3& pos) {
        Position = pos;
    }

    void setRotation(const glm::vec3& rot) {
        Rotation = rot;

        float pitch = rot.x;
        float yaw   = rot.y;
        float roll  = rot.z;

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        Front = glm::normalize(front);

        glm::vec3 right = glm::normalize(glm::cross(Front, glm::vec3(0.0f, 1.0f, 0.0f)));

        glm::mat4 rollMat = glm::rotate(glm::mat4(1.0f), glm::radians(roll), Front);
        glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        Up = glm::normalize(glm::vec3(rollMat * glm::vec4(worldUp, 0.0f)));

        right = glm::normalize(glm::cross(Front, Up));
        Up    = glm::normalize(glm::cross(right, Front));
    }
};

#endif //FORE_CAMERA_H
