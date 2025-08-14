//
// Created by wyrex on 8/14/25.
//

#pragma once

#ifndef FORE_RENDERER_H
#define FORE_RENDERER_H

#include <GLES3/gl32.h>

class Renderer {
public:
    void init();
    void resize(int &width, int &height);
    void draw();

private:
    GLuint program = 0;
    GLuint vao = 0, vbo = 0;
};


#endif //FORE_RENDERER_H
