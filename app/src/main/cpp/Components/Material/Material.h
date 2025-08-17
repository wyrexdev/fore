//
// Created by wyrex on 8/17/25.
//

#ifndef FORE_MATERIAL_H
#define FORE_MATERIAL_H

#include "../Component.h"

class Material : public Component {
public:
    Material();

    // For Images
    void loadTexture(std::string &path);
};


#endif //FORE_MATERIAL_H
