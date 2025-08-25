//
// Created by wyrex on 8/14/25.
//

#ifndef FORE_RENDERER_H
#define FORE_RENDERER_H

#include "../Entities/Objects/Cubemap/Cubemap.h"

class Renderer {
public:
    void init();
    void resize(int width, int height);
    void draw(float angle);
};

#endif //FORE_RENDERER_H
