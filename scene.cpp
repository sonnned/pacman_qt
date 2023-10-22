#include "scene.h"

Scene::Scene()
{
    scene = new QGraphicsScene;
}

Scene::~Scene()
{
    delete scene;
}

void Scene::set_graphicsview(QGraphicsView *graphics)
{
    this->graphics = graphics;
    scene->setSceneRect(0, 0, graphics->width()-2, graphics->height()-2);
    graphics->setScene(scene);
}

void Scene::set_pac(Pac *pac)
{
    scene->addItem(pac);
}

