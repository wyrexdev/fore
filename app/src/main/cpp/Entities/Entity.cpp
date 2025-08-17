//
// Created by wyrex on 8/14/25.
//

#include "Entity.h"
#include "../Utils/AssetLoader.h"

Entity::Entity() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, drawOrder.size() * sizeof(unsigned int), drawOrder.data(), GL_STATIC_DRAW);

    // Position attribute (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Texture coordinate attribute (location = 1)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    vertexShader = compile(GL_VERTEX_SHADER, vertexShaderCode);
    fragmentShader = compile(GL_FRAGMENT_SHADER, fragmentShaderCode);
    shaderProgram = link(vertexShader, fragmentShader);
}

void Entity::updateBuffers() {
    if (vertices.empty() || drawOrder.empty()) return;

    if (VBO != 0) glDeleteBuffers(1, &VBO);
    if (EBO != 0) glDeleteBuffers(1, &EBO);
    if (VAO != 0) glDeleteVertexArrays(1, &VAO);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, drawOrder.size() * sizeof(unsigned int), drawOrder.data(), GL_STATIC_DRAW);

    // Position attribute (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Texture coordinate attribute (location = 1)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Entity::loadTexture(const char* path) {
    if (textureLoaded) {
        glDeleteTextures(1, &textureID);
    }

    int width, height, nrChannels;
    unsigned char* data = AssetLoader::loadImageAsset(path, &width, &height, &nrChannels);

    if (!data) {
        textureLoaded = false;
        return;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = nrChannels == 4 ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    textureLoaded = true;
}

void Entity::draw() {
    if (!isVisible) return;

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position.x, position.y, position.z));

    glm::vec3 radians = glm::radians(glm::vec3(rotation.x, rotation.y, rotation.z));
    model = glm::rotate(model, radians.x, glm::vec3(1,0,0));
    model = glm::rotate(model, radians.y, glm::vec3(0,1,0));
    model = glm::rotate(model, radians.z, glm::vec3(0,0,1));

    model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), Surface::width/Surface::height, 0.1f, 100.0f);

    glm::vec3 lightDir = glm::normalize(glm::vec3(0.0f, 3.0f, 0.0f));
    lightDir = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(1,0,0)) * glm::vec4(lightDir, 0.0f);

    glUseProgram(shaderProgram);

    glUniform3fv(glGetUniformLocation(shaderProgram, "lightDir"), 1, glm::value_ptr(lightDir));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "uModel"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "uView"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "uProj"), 1, GL_FALSE, glm::value_ptr(proj));
    glUniform3f(glGetUniformLocation(shaderProgram, "vCol"), 1.0f, 1.0f, 1.0f);
    glUniform1i(glGetUniformLocation(shaderProgram, "useMaterial"), isUseMaterial ? 1 : 0);

    if (isUseMaterial && textureLoaded) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glUniform1i(glGetUniformLocation(shaderProgram, "oTexture"), 0);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, drawOrder.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Entity::addComponent(Component *comp) {
    int key = nextKey++;

    comp->setEntity(this);
    components[key] = comp;
}