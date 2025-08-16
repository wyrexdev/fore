#include <jni.h>
#include <android/log.h>

#include "Core/Renderer.h"

#include "Entities/Objects/Cube.h"
#include "Components/Transform/Transform.h"

static Renderer renderer;

static Cube cube;

extern "C" {

JNIEXPORT void JNICALL
Java_com_fore_engine_Bridge_NativeBridge_onSurfaceCreated(JNIEnv*, jclass) {
    renderer.init();

    cube = Cube();
    cube.isVisible = true;
}

JNIEXPORT void JNICALL
Java_com_fore_engine_Bridge_NativeBridge_onSurfaceChanged(JNIEnv*, jclass, jint width, jint height) {
    renderer.resize(width, height);
}

JNIEXPORT void JNICALL
Java_com_fore_engine_Bridge_NativeBridge_onDrawFrame(JNIEnv*, jclass) {
    renderer.draw();

    auto *tf = new Transform();
    cube.addComponent(tf);

    tf->setPosition(0, 0, 0);
    tf->setScale(1, 2, 1);
    tf->setRotate(80, 10, 2);

    cube.draw();

}

}
