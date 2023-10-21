#ifndef GHOST_H
#define GHOST_H

#include "game_macros.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Ghost: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Ghost();
    ~Ghost();
private:
    //Ghost variables
    bool is_alive = true;
    bool is_scared = false;
    bool is_eaten = false;
    unsigned int speed = 1;
    unsigned int scared_speed = 1;
    unsigned int eaten_speed = 2;
    unsigned int scared_time = 10;
    //Sprites
    QPixmap *living_ghost;
    QPixmap *death_ghost;
    QTimer *ghost_sprite_change_timer;
};

#endif // GHOST_H
