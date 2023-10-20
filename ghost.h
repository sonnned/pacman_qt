#ifndef GHOST_H
#define GHOST_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Ghost
{
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

};

#endif // GHOST_H
