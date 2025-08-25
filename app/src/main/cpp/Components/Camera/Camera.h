//
// Created by wyrex on 8/20/25.
//

#ifndef FORE_CAMERA_H
#define FORE_CAMERA_H

#include <GLES3/gl32.h>

#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"

#include "../Component.h"

class Camera : public Component {
public:
    int zIndex;

    float far = 100.0f;
    float near = 0.1f;

    float fieldOfView = 45.0f;

    glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec4 viewport;

    glm::mat4 getViewMatrix();

    void setViewport(glm::vec4 viewport);

    void onCreate() override;
    void onRender() override;
};


#endif //FORE_CAMERA_H
