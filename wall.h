#ifndef WALL_H
#define WALL_H

#include "game_macros.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <vector>
#include <string>

class Wall: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Wall(int x_pos, int y_pos, int sprite_position);
    ~Wall();
private:
    QPixmap *wall;
    std::vector<std::string> WALL_SPRITES = {":/textures/MapBlock7.png"};
    void cut_sprites(std::string sprite, int amount_of_sprites, int x, int y);

};

#endif // WALL_H
