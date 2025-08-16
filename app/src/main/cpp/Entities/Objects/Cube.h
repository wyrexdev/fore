//
// Created by wyrex on 8/14/25.
//

#ifndef FORE_CUBE_H
#define FORE_CUBE_H

#include "../Entity.h"

class Cube : public Entity {
public:
    float vertices[24] = {
            -1, -1, -1,     // 0
            1, -1, -1,      // 1
            1, -1,  1,      // 2
            -1, -1,  1,    // 3
            1,  1, -1,    // 4
            1,  1,  1,    // 5
            -1,  1,  1,   // 6
            -1,  1, -1,   // 7
    };

    unsigned int drawOrder[36] = {
            3, 1, 0,         // BOTTOM
            3, 2, 1,         // FACE

            2, 3, 6,         // FRONT
            6, 5, 2,        // FACE

            3, 0, 7,       // LEFT
            7, 6, 3,       // FACE

            0, 1, 4,       // BACK
            4, 7, 0,       // FACE

            1, 2, 5,       // RIGHT
            5, 4, 1,       // FACE

            7, 4, 5,       // TOP
            5, 6, 7        // FACE
    };

    Cube();
    ~Cube();

    void draw() override;

    GLuint compile(GLenum type, const char* src);
    GLuint link(GLuint vs, GLuint fs);
private:
};


#endif //FORE_CUBE_H
