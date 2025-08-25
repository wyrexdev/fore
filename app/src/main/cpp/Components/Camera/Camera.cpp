//
// Created by wyrex on 8/20/25.
//

#include <android/log.h>
#include "Camera.h"

#include "../../Entities/Entity.h"

#include "../../Utils/Shader.h"

void Camera::onCreate() {

}

void Camera::onRender() {
    if (std::find(cameras.begin(), cameras.end(), this) == cameras.end()) {
        cameras.push_back(this);
    }
}

void Camera::setViewport(glm::vec4 v) {
    viewport = v;
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(entity->position, entity->position + Front, Up);
}