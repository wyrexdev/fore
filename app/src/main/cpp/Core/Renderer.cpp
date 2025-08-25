//
// Created by wyrex on 8/14/25.
//

#include "Renderer.h"

#include "../Utils/Surface.h"
#include "../Entities/Entity.h"
#include "../Components/Mesh/MeshComponent.h"
#include "../Components/Material/Material.h"
#include "../Components/Camera/Camera.h"

#include <GLES3/gl32.h>
#include <android/log.h>

Entity cube, cam, mainCam;

CubeMap* skybox = nullptr;
std::vector<Camera*> cameras;

void Renderer::init() {
    glEnable(GL_DEPTH_TEST);

    cube = Entity();
    cam = Entity();

    mainCam = Entity();

    MeshComponent *mesh = new MeshComponent();
    cube.addComponent(mesh);
    Transform* transform = new Transform();
    cube.addComponent(transform);

    Transform* cT = new Transform();
    cam.addComponent(cT);

    cT->setPosition(0, 0, 25);

    Camera* camComp = new Camera();
    cam.addComponent(camComp);

    Camera* mCC = new Camera();
    mainCam.addComponent(mCC);

    Transform* cmT = new Transform();
    mainCam.addComponent(cmT);

    cmT->setPosition(0, 0, 25);


    Material *mat = new Material();
    cube.addComponent(mat);
    mat->loadTextureFromAssets("land-with-grass-seamless-background-ecology-terrain-backdrop-summer-desert-with-mossy-cracks-surface-hot-grunge-weather-climate-pattern-grass-texture-photo.jpg");

    skybox = new CubeMap("e243d6fce8004e60be7024c6f0338f94.jpg");

    cube.getComponent<MeshComponent>()->setMesh(new Cube());
}

void Renderer::resize(int width, int height) {
    Surface::width = width;
    Surface::height = height;

    glViewport(0, 0, width, height);
}

void Renderer::draw(float angle) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cam.getComponent<Camera>()->setViewport(glm::vec4(20.0f, Surface::height - 520.0f, 500.0f, 500.0f));
    mainCam.getComponent<Camera>()->setViewport(glm::vec4(0.0f, 0.0f, Surface::width, Surface::height));

    mainCam.draw();
    cam.draw();
    
    cube.draw();
    skybox->draw();

    cube.getComponent<Transform>()->setScale(10, 0.1f, 10);
    cube.getComponent<Transform>()->setPosition(0, -5, 0);
}
