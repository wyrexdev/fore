//
// Created by wyrex on 8/17/25.
//

#ifndef FORE_MATERIAL_H
#define FORE_MATERIAL_H

#include "../Component.h"

class Material : public Component {
public:
    Material() {};

    // For Images
    void loadTextureFromAssets(const char *path);

    void onCreate() override;
    void onRender() override;
private:
    int width, height, nrChannels;
    unsigned char* data;

    const char* path;
};


#endif //FORE_MATERIAL_H
