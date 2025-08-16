//
// Created by wyrex on 8/14/25.
//

#include "Entity.h"

void Entity::addComponent(Component *comp) {
    int key = nextKey++;

    comp->setEntity(this);
    components[key] = comp;
}