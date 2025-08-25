#ifndef FORE_CUBEMAP_H
#define FORE_CUBEMAP_H

#include "../../Entity.h"

#include "../../../Utils/AssetLoader.h"
#include "../../../Utils/Shader.h"

class CubeMap : public Entity {
public:
    CubeMap(const std::string& cubemapPath);
    ~CubeMap();

    bool loadCubemap(const std::string& cubemapPath);
    void draw();

protected:
    GLuint cubemapTexture = 0;
    GLuint cubeVAO = 0, cubeVBO = 0;
    bool cubemapLoaded = false;

    // Shader sources
    static constexpr const char* skyboxVertexShaderCode = R"(#version 300 es
        layout(location = 0) in vec3 aPos;
        out vec3 TexCoords;
        uniform mat4 uView;
        uniform mat4 uProj;
        void main() {
            TexCoords = aPos;
            vec4 pos = uProj * uView * vec4(aPos, 1.0);
            // Ensure skybox is rendered at the far plane
            gl_Position = pos.xyww;
        })";

    static constexpr const char* skyboxFragmentShaderCode = R"(#version 300 es
        precision mediump float;
        in vec3 TexCoords;
        out vec4 FragColor;
        uniform samplerCube skybox;
        void main() {
            // Use better texture sampling with proper filtering
            vec4 texColor = texture(skybox, TexCoords);
            // Apply gamma correction to improve color vibrancy
            vec3 gammaCorrected = pow(texColor.rgb, vec3(1.0/2.2));
            // Ensure proper alpha handling
            FragColor = vec4(gammaCorrected, 1.0);
        })";

private:
    void initializeGeometry();
    void initializeConversionGeometry();
    bool setupShaders();
    GLuint compileShaderProgram(const char* vertexSrc, const char* fragmentSrc);
    void updateBuffers();
};

#endif //FORE_CUBEMAP_H