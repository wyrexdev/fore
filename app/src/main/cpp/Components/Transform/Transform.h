//
// Created by wyrex on 8/16/25.
//

#ifndef FORE_TRANSFORM_H
#define FORE_TRANSFORM_H

#include "../Component.h"

class Transform : public Component {
public:
    Transform() { type = "Transform"; };

    void setPosition(float x, float y, float z);
    void setRotate(float x, float y, float z);
    void setScale(float x, float y, float z);

    void onCreate() override;
    void onRender() override;
};


#endif //FORE_TRANSFORM_H
