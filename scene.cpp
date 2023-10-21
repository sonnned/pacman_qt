#include "scene.h"

Scene::Scene()
{
    scene = new QGraphicsScene;
    pac = new Pac;
    ghost = new Ghost;
}

Scene::~Scene()
{
    delete scene;
    delete pac;
    delete ghost;
}

void Scene::set_graphicsview(QGraphicsView *graphics)
{
    this->graphics = graphics;
    scene->setSceneRect(0, 0, graphics->width()-2, graphics->height()-2);
    scene->addItem(pac);
    scene->addItem(ghost);
    graphics->setScene(scene);
}

