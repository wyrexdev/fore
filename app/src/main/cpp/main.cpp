#include <jni.h>
#include <android/log.h>

#include <chrono>

#include "Core/Renderer.h"
#include "Utils/AssetLoader.h"

#include "Entities/Entity.h"

#include "Components/Transform/Transform.h"
#include "Components/Mesh/MeshComponent.h"

static int frames = 0;
static int fps = 0;
static auto lastTime = std::chrono::high_resolution_clock::now();

static Renderer renderer;
static Camera camera;
static Camera topMapCamera;

extern "C" {

JNIEXPORT void JNICALL
Java_com_fore_engine_Bridge_NativeBridge_initAssetManager(JNIEnv* env, jclass, jobject assetManager) {
    AssetLoader::initAssetManager(env, assetManager);
}

JNIEXPORT void JNICALL
Java_com_fore_engine_Bridge_NativeBridge_onSurfaceCreated(JNIEnv*, jclass) {
    camera = Camera();
    topMapCamera = Camera();
    renderer.init();

    camera.setPosition(glm::vec3(0.0f, 0.0f, 25.0f));
    topMapCamera.setRotation(glm::vec3(0, 90, 0));
}

JNIEXPORT void JNICALL
Java_com_fore_engine_Bridge_NativeBridge_onSurfaceChanged(JNIEnv*, jclass, jint width, jint height) {
    renderer.resize(width, height);
    camera.width = width;
    camera.height = height;

    topMapCamera.width = 50.0f;
    topMapCamera.height = 50.0f;
}

JNIEXPORT void JNICALL
Java_com_fore_engine_Bridge_NativeBridge_onDrawFrame(JNIEnv*, jclass) {
    frames++;

    static auto startTime = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> delta = now - lastTime;
    std::chrono::duration<float> elapsed = now - startTime;

    if (delta.count() >= 1.0f) {
        fps = frames;
        frames = 0;
        lastTime = now;
    }

    float angle = elapsed.count();

    renderer.draw(angle, topMapCamera);
    renderer.draw(angle, camera);
}

JNIEXPORT jint JNICALL
Java_com_fore_engine_Bridge_NativeBridge_onCalculateFPS(JNIEnv*, jclass) {
    return fps;
}

}
