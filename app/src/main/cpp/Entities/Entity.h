//
// Created by wyrex on 8/14/25.
//

#ifndef FORE_ENTITY_H
#define FORE_ENTITY_H

#include "../stb/stb_image.h"

#include <unordered_map>
#include <vector>
#include <typeindex>

#include <android/log.h>

#include <GLES3/gl32.h>

#include "../Components/Component.h"
#include "../Components/Transform/Transform.h"

#include "../Utils/Shader.h"
#include "../Utils/Surface.h"
#include "../Utils/AssetLoader.h"

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

class Entity {
public:
    Entity();

    int id;

    std::string title;
    std::string description;

    bool isVisible = true;
    bool isUseMaterial = false;

    glm::mat4 model;

    GLuint VAO, VBO, EBO;
    GLuint vertexShader, fragmentShader, shaderProgram;

    std::vector<float> vertices;
    std::vector<unsigned int> drawOrder;

    std::unordered_map<std::type_index, std::vector<Component*>> components;

    void addComponent(Component *comp) {
        components[typeid(*comp)].push_back(comp);
        comp->setEntity(this);
    }

    template<typename T>
    T* getComponent() {
        auto it = components.find(typeid(T));
        if (it != components.end() && !it->second.empty())
            return static_cast<T*>(it->second[0]);
        return nullptr;
    }

    template<typename T>
    T* getComponent(size_t index) {
        auto it = components.find(typeid(T));
        if (it != components.end() && index < it->second.size())
            return static_cast<T*>(it->second[index]);
        return nullptr;
    }

    void updateBuffers();
    void draw();

    glm::vec3 position = glm::vec3(0, 0, 0);;
    glm::vec3 rotation = glm::vec3(0, 0, 0);;
    glm::vec3 scale = glm::vec3(1, 1, 1);

    int width, height, nrChannels;

    unsigned char* data;

    GLuint textureID;
    bool textureLoaded;
private:
};


#endif //FORE_ENTITY_H
