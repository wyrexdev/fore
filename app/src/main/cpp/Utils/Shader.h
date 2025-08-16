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


#endif //FORE_SHADER_H
