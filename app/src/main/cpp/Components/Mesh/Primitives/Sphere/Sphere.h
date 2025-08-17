//
// Created by wyrex on 8/17/25.
//

#ifndef FORE_SPHERE_H
#define FORE_SPHERE_H

#include "../Primitive.h"
#include <cmath>
#include <vector>

class Sphere : public Primitive {
public:
    Sphere() {
        float radius = 1.0f;
        int sectorCount = 1028;
        int stackCount = 512;

        buildSphere(radius, sectorCount, stackCount);
    }

    void buildSphere(float radius, int sectorCount, int stackCount) {
        const float PI = acos(-1.0f);

        vertices.clear();
        drawOrder.clear();

        float x, y, z, xy;
        float nx, ny, nz, lengthInv = 1.0f / radius;
        float s, t;

        float sectorStep = 2 * PI / sectorCount;
        float stackStep = PI / stackCount;
        float sectorAngle, stackAngle;

        for(int i = 0; i <= stackCount; ++i) {
            stackAngle = PI / 2 - i * stackStep;
            xy = radius * cosf(stackAngle);
            z = radius * sinf(stackAngle);

            for(int j = 0; j <= sectorCount; ++j) {
                sectorAngle = j * sectorStep;

                x = xy * cosf(sectorAngle);
                y = xy * sinf(sectorAngle);
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
            }
        }

        unsigned int k1, k2;
        for(int i = 0; i < stackCount; ++i) {
            k1 = i * (sectorCount + 1);
            k2 = k1 + sectorCount + 1;

            for(int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
                if(i != 0) {
                    drawOrder.push_back(k1);
                    drawOrder.push_back(k2);
                    drawOrder.push_back(k1 + 1);
                }

                if(i != (stackCount - 1)) {
                    drawOrder.push_back(k1 + 1);
                    drawOrder.push_back(k2);
                    drawOrder.push_back(k2 + 1);
                }
            }
        }
    }
};

#endif //FORE_SPHERE_H