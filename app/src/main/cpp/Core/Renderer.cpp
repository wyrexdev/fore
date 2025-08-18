//
// Created by wyrex on 8/14/25.
//

#include "Renderer.h"

#include "../Utils/Surface.h"
#include "../Entities/Entity.h"
#include "../Components/Mesh/MeshComponent.h"
#include "../Components/Material/Material.h"

#include <GLES3/gl32.h>
#include <android/log.h>

Entity cube;

CubeMap* skybox = nullptr;

void Renderer::init() {
    glEnable(GL_DEPTH_TEST);

    cube = Entity();

    MeshComponent *mesh = new MeshComponent();
    cube.addComponent(mesh);
    Transform* transform = new Transform();
    cube.addComponent(transform);

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

void Renderer::draw(float angle, Camera &cam) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    skybox->draw(cam);

    cube.draw(cam);

    cube.getComponent<Transform>()->setScale(10, 0.1f, 10);
    cube.getComponent<Transform>()->setPosition(0, -5, 0);
}
