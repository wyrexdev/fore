//
// Created by wyrex on 8/14/25.
//

#include "Renderer.h"

#include <vector>
#include <string>

void Renderer::init() {

}

void Renderer::resize(int &width, int &height) {
    glViewport(0, 0, width, height);
}

void Renderer::draw() {
    glClearColor(1, 0, 0, 1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
