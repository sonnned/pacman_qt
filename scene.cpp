#include "scene.h"

Scene::Scene()
{
    scene = new QGraphicsScene;
    pac = new Pac;
}

Scene::~Scene()
{
    delete scene;
    delete pac;
}

void Scene::set_graphicsview(QGraphicsView *graphics)
{
    this->graphics = graphics;
    scene->setSceneRect(0, 0, graphics->width()-2, graphics->height()-2);
    scene->addItem(pac);
    graphics->setScene(scene);
}
