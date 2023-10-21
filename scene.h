#ifndef SCENE_H
#define SCENE_H

#include "pac.h"
#include "ghost.h"

#include <QGraphicsView>
#include <QGraphicsScene>

class Scene
{
public:
    Scene();
    ~Scene();
    void set_graphicsview(QGraphicsView *graphics);
private:
    QGraphicsView *graphics;
    QGraphicsScene *scene;
    Pac *pac;
    Ghost *ghost;

};

#endif // SCENE_H
