//
// Created by wyrex on 8/14/25.
//
#ifndef FORE_COMPONENT_H
#define FORE_COMPONENT_H

#include <string>

class Entity;

class Component {
public:
    virtual ~Component() = default;

    Entity *entity;
    void setEntity(Entity* e) { entity = e; }

    std::string type;
    std::string title;
    std::string description;

    bool isActive;
};


#endif //FORE_COMPONENT_H
