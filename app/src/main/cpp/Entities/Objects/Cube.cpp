//
// Created by wyrex on 8/14/25.
//

#include "Cube.h"


#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"

#include "Camera.h"

#include "../../Utils/Surface.h"

extern Camera camera;

Cube::Cube() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(drawOrder), drawOrder, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    vertexShader = compile(GL_VERTEX_SHADER, vertexShaderCode);
    fragmentShader = compile(GL_FRAGMENT_SHADER, fragmentShaderCode);
    shaderProgram = link(vertexShader, fragmentShader);
}

float getTime() {
    using namespace std::chrono;
    static auto start = high_resolution_clock::now();
    auto now = high_resolution_clock::now();
    duration<float> elapsed = now - start;
    return elapsed.count();
}

Cube::~Cube() {
}

void Cube::draw() {
    if(isVisible) {
        float time = getTime();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -8.0f, -4.0f));
        model = glm::scale(model, glm::vec3(4, 0.1f, 3));
        // model = glm::rotate(model, time, glm::vec3(0.0f, 1.0f, 0.0f));

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
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}

GLuint Cube::compile(GLenum type, const char* src) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);
    GLint ok;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if(!ok){
        GLint len;
        glGetShaderiv(s, GL_INFO_LOG_LENGTH, &len);
        std::vector<char> log(len);
        glGetShaderInfoLog(s, len, nullptr, log.data());
        glDeleteShader(s);
        throw std::runtime_error(log.data());
    }
    return s;
}

GLuint Cube::link(GLuint vs, GLuint fs) {
    GLuint p = glCreateProgram();
    glAttachShader(p, vs);
    glAttachShader(p, fs);
    glLinkProgram(p);
    GLint ok;
    glGetProgramiv(p, GL_LINK_STATUS, &ok);
    if(!ok){
        GLint len;
        glGetProgramiv(p, GL_INFO_LOG_LENGTH, &len);
        std::vector<char> log(len);
        glGetProgramInfoLog(p, len, nullptr, log.data());
        glDeleteProgram(p);
        throw std::runtime_error(log.data());
    }
    glDeleteShader(vs);
    glDeleteShader(fs);
    return p;
}
