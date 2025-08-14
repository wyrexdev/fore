//
// Created by wyrex on 8/14/25.
//

#ifndef FORE_ENTITY_H
#define FORE_ENTITY_H

#include "Math/Vector3.h"
#include "Graphics/Color.h"

class Entity {
public:
    Entity();

    std::string title;
    std::string description;

    bool isVisible;

    Graphics::Color color = Graphics::Color("#FF8000");

    void draw();

private:

};


#endif //FORE_ENTITY_H
