//
// Created by wyrex on 8/16/25.
//

#ifndef FORE_SHADER_H
#define FORE_SHADER_H

#include <GLES3/gl32.h>

static const GLchar* vertexShaderCode =
        "#version 320 es\n"
        "layout(location = 0) in vec3 aPos;\n"
        "\n"
        "out vec3 vPos;\n"
        "\n"
        "uniform mat4 uModel;\n"
        "uniform mat4 uView;\n"
        "uniform mat4 uProj;\n"
        "\n"
        "void main() {\n"
        "    vec4 worldPos = uModel * vec4(aPos, 1.0);\n"
        "    vPos = (uView * worldPos).xyz;\n"
        "    gl_Position = uProj * uView * worldPos;\n"
        "}";

static const GLchar* fragmentShaderCode =
        "#version 320 es\n"
        "precision mediump float;\n"
        "\n"
        "in vec3 vPos;\n"
        "\n"
        "out vec4 fragColor;\n"
        "\n"
        "uniform vec3 vCol;\n"
        "uniform vec3 lightDir;\n"
        "\n"
        "void main() {\n"
        "    vec3 dx = dFdx(vPos);\n"
        "    vec3 dy = dFdy(vPos);\n"
        "    vec3 normal = normalize(cross(dx, dy));\n"
        "\n"
        "    float diff = max(dot(normal, normalize(-lightDir)), 0.0);\n"
        "    vec3 color = vCol * diff + vCol * 0.2;\n"
        "\n"
        "    fragColor = vec4(color, 1.0);\n"
        "}";

static GLuint compile(GLenum type, const char* src) {
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

static GLuint link(GLuint vs, GLuint fs) {
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


#endif //FORE_SHADER_H
