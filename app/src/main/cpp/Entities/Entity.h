//
// Created by wyrex on 8/14/25.
//

#ifndef FORE_ENTITY_H
#define FORE_ENTITY_H

#include "../stb/stb_image.h"

#include <unordered_map>
#include <vector>
#include <GLES3/gl32.h>

#include "../Components/Component.h"

#include "../Utils/Shader.h"
#include "../Utils/Surface.h"

#include "./Objects/Camera.h"

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

extern Camera camera;

class Entity {
public:
    Entity();

    int id;

    std::string title;
    std::string description;

    bool isVisible;
    bool isUseMaterial = false;

    glm::mat4 model;

    GLuint VAO, VBO, EBO;
    GLuint vertexShader, fragmentShader, shaderProgram;

    std::vector<float> vertices;
    std::vector<unsigned int> drawOrder;

    std::unordered_map<int, Component*> components;
    void addComponent(Component *comp);

    void updateBuffers();
    void draw();

    void loadTexture(const char* path);

    glm::vec3 position = glm::vec3(0, 0, 0);;
    glm::vec3 rotation = glm::vec3(0, 0, 0);;
    glm::vec3 scale = glm::vec3(1, 1, 1);

    int width, height, nrChannels;

    unsigned char* data;
private:
    GLuint textureID;
    bool textureLoaded;

    int nextKey = 1;
};


#endif //FORE_ENTITY_H
