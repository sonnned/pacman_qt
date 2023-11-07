#ifndef POINTS_H
#define POINTS_H

#include "game_macros.h"

#include <QObject>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <vector>
#include <string>
#include <iostream>

class Points: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Points(int x_pos, int y_pos, int sprite_position);
    ~Points();
    bool getIs_power() { return is_power; }
private:
    bool is_power = false;
    QPixmap *points;
    QTimer *point_scale_timer;
    std::vector<std::string> POINT_SPRITES = {":/textures/MapBlock7.png"};
    void cut_sprites(std::string sprite, int amount_of_sprites, int x, int y);
private slots:
    void scale_point();
};

#endif // POINTS_H
