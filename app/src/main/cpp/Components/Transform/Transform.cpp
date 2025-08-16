//
// Created by wyrex on 8/16/25.
//

#include "Transform.h"

#include "../../Entities/Entity.h"

void Transform::setPosition(float x, float y, float z) {
    entity->rotation = glm::vec3(x, y, z);
}

void Transform::setRotate(float x, float y, float z) {
    entity->rotation = glm::vec3(x, y, z);
}

void Transform::setScale(float x, float y, float z) {
    entity->scale = glm::vec3(x, y, z);
}