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

extern "C" {

JNIEXPORT void JNICALL
Java_com_fore_engine_Bridge_NativeBridge_initAssetManager(JNIEnv* env, jclass, jobject assetManager) {
    AssetLoader::initAssetManager(env, assetManager);
}

JNIEXPORT void JNICALL
Java_com_fore_engine_Bridge_NativeBridge_onSurfaceCreated(JNIEnv*, jclass) {
    renderer.init();
}

JNIEXPORT void JNICALL
Java_com_fore_engine_Bridge_NativeBridge_onSurfaceChanged(JNIEnv*, jclass, jint width, jint height) {
    renderer.resize(width, height);
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

    renderer.draw(angle);
}

JNIEXPORT jint JNICALL
Java_com_fore_engine_Bridge_NativeBridge_onCalculateFPS(JNIEnv*, jclass) {
    return fps;
}

}
