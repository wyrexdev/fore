//
// Created by wyrex on 8/16/25.
//

#ifndef FORE_MESHCOMPONENT_H
#define FORE_MESHCOMPONENT_H

#include "../Component.h"

#include "./Primitives/Primitive.h"

#include "./Primitives/Cube/Cube.h"
#include "./Primitives/Sphere/Sphere.h"

class MeshComponent : public Component {
public:
    MeshComponent() { type = "MeshComponent"; };

    void setMesh(const Primitive *mesh);

    void onCreate() override;
    void onRender() override;
};


#endif //FORE_MESHCOMPONENT_H
