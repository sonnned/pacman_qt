#ifndef SCENE_H
#define SCENE_H

#include "pac.h"
#include <QGraphicsView>
#include <QGraphicsScene>

class Scene
{
public:
    Scene();
    ~Scene();
    void set_graphicsview(QGraphicsView *graphics);
    void set_pac(Pac *pac);
private:
    QGraphicsView *graphics;
    QGraphicsScene *scene;
};

#endif // SCENE_H
