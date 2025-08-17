#include <jni.h>
#include <android/log.h>

#include <chrono>

#include "Core/Renderer.h"

#include "Entities/Entity.h"

#include "Components/Transform/Transform.h"
#include "Components/Mesh/MeshComponent.h"

static int frames = 0;
static int fps = 0;
static auto lastTime = std::chrono::high_resolution_clock::now();

static Renderer renderer;

static Entity entity;

auto *tf = new Transform();

extern "C" {

JNIEXPORT void JNICALL
Java_com_fore_engine_Bridge_NativeBridge_onSurfaceCreated(JNIEnv*, jclass) {
    renderer.init();

    entity = Entity();

    auto *mesh = new MeshComponent();
    entity.addComponent(mesh);
    mesh->setMesh(new Sphere());

    entity.addComponent(tf);

    tf->setScale(5, 5, 5);

    entity.isVisible = true;
}

JNIEXPORT void JNICALL
Java_com_fore_engine_Bridge_NativeBridge_onSurfaceChanged(JNIEnv*, jclass, jint width, jint height) {
    renderer.resize(width, height);
}

JNIEXPORT void JNICALL
Java_com_fore_engine_Bridge_NativeBridge_onDrawFrame(JNIEnv*, jclass) {
    renderer.draw();
    entity.draw();

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

    float angle = elapsed.count() * 45.0f;
    tf->setRotate(angle, 0, 0);

}

JNIEXPORT jint JNICALL
Java_com_fore_engine_Bridge_NativeBridge_onCalculateFPS(JNIEnv*, jclass) {
    return fps;
}

}
