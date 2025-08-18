//
// Created by wyrex on 8/17/25.
//

#include "Material.h"

#include "../../Entities/Entity.h"

void Material::onCreate() {
    entity->isUseMaterial = true;

    glGenTextures(1, &entity->textureID);
    glBindTexture(GL_TEXTURE_2D, entity->textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = nrChannels == 4 ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    entity->textureLoaded = true;
}

void Material::onRender() {

}

void Material::loadTextureFromAssets(const char *path) {
    this->path = path;

    if (entity->textureLoaded) {
        glDeleteTextures(1, &entity->textureID);
    }

    data = AssetLoader::loadImageAsset(path, &width, &height, &nrChannels);

    if (!data) {
        entity->textureLoaded = false;
        return;
    }
}

