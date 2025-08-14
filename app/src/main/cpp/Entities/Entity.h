//
// Created by wyrex on 8/14/25.
//

#ifndef FORE_ENTITY_H
#define FORE_ENTITY_H

#include <unordered_map>
#include <vector>

#include "Math/Vector3.h"
#include "Graphics/Color.h"
#include "Components/Component.h"

class Entity {
public:
    Entity();

    int id;

    std::string title;
    std::string description;

    bool isVisible;

    std::vector<float> vertices;

    std::unordered_map<int, Component> components;

    Graphics::Color color = Graphics::Color("#FF8000");

    void draw();

private:

};


#endif //FORE_ENTITY_H
