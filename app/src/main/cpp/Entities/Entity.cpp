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
    glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, drawOrder.size(), drawOrder.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Entity::draw() {
    if(isVisible) {
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

        GLuint lightLoc = glGetUniformLocation(shaderProgram, "lightDir");
        glUniform3fv(lightLoc, 1, glm::value_ptr(lightDir));

        GLuint modelLoc = glGetUniformLocation(shaderProgram, "uModel");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        GLuint viewLoc = glGetUniformLocation(shaderProgram, "uView");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        GLuint projLoc = glGetUniformLocation(shaderProgram, "uProj");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

        GLuint colorLoc = glGetUniformLocation(shaderProgram, "vCol");
        glUniform3f(colorLoc, 1.0f, 0.0f, 1.0f);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, drawOrder.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}

void Entity::addComponent(Component *comp) {
    int key = nextKey++;

    comp->setEntity(this);
    components[key] = comp;
}