//
// Created by wyrex on 8/14/25.
//

#include "Renderer.h"

#include "../Utils/Surface.h"

#include <GLES3/gl32.h>
#include <android/log.h>

void Renderer::init() {
    glEnable(GL_DEPTH_TEST);
}

void Renderer::resize(int width, int height) {
    Surface::width = width;
    Surface::height = height;

    glViewport(0, 0, width, height);
}

void Renderer::draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
