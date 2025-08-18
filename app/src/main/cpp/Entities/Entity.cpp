//
// Created by wyrex on 8/14/25.
//

#include "Entity.h"

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

    for (auto& [type, vec] : components) {
        for (auto* comp : vec) {
            comp->onCreate();
        }
    }
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

    for (auto& [type, vec] : components) {
        for (auto* comp : vec) {
            comp->onCreate();
        }
    }
}

void Entity::draw(Camera &cam) {
    if (!isVisible) return;

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position.x, position.y, position.z));

    glm::vec3 radians = glm::radians(glm::vec3(rotation.x, rotation.y, rotation.z));
    model = glm::rotate(model, radians.x, glm::vec3(1,0,0));
    model = glm::rotate(model, radians.y, glm::vec3(0,1,0));
    model = glm::rotate(model, radians.z, glm::vec3(0,0,1));

    model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));

    glm::mat4 view = cam.getViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), cam.width/cam.height, 0.1f, 100.0f);

    glm::vec3 lightDir = glm::normalize(glm::vec3(0.0f, 3.0f, 0.0f));
    lightDir = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(1,0,0)) * glm::vec4(lightDir, 0.0f);

    for (auto& [type, vec] : components) {
        for (auto* comp : vec) {
            comp->onRender();
        }
    }

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