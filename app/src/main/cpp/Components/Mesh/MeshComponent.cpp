//
// Created by wyrex on 8/16/25.
//

#include "MeshComponent.h"

#include "../../Entities/Entity.h"

void MeshComponent::setMesh(const Primitive *mesh) {
    entity->vertices = mesh->vertices;
    entity->drawOrder = mesh->drawOrder;
    entity->updateBuffers();
}