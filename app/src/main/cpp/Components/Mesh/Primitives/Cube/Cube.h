//
// Created by wyrex on 8/17/25.
//

#ifndef FORE_CUBE_H
#define FORE_CUBE_H

#include "../Primitive.h"

class Cube : public Primitive {
public:
    Cube() {
        vertices = {
                -1, -1, -1,     // 0
                1, -1, -1,      // 1
                1, -1,  1,      // 2
                -1, -1,  1,    // 3
                1,  1, -1,    // 4
                1,  1,  1,    // 5
                -1,  1,  1,   // 6
                -1,  1, -1,   // 7
        };

        drawOrder = {
                3, 1, 0,         // BOTTOM
                3, 2, 1,         // FACE0

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
    }
};


#endif //FORE_CUBE_H
