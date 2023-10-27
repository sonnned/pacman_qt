#ifndef GHOST_H
#define GHOST_H

#include "game_macros.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <iostream>
#include <vector>
#include <string>
#include <QColor>

class Ghost: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Ghost(const QColor &target_color, const QColor &replacement_color);
    Ghost(const QColor &target_color, const QColor &replacement_color, int x_pos, int y_pos);
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
    unsigned int x_pos = 120;
    unsigned int y_pos = 120;
    //Sprite variables
    const std::vector<std::string> GHOST_BODY_SPRITES = {":/textures/GhostBody32.png"};
    const std::vector<std::string> GHOST_EYES_SPRITES = {":/textures/GhostEyes32.png"};
    int current_ghost_body_sprite = 1;
    int current_ghost_eyes_sprite = 1;
    //Sprites
    QPixmap *ghost_body;
    QPixmap *ghost_eyes;
    QTimer *ghost_sprite_change_timer;
    QColor target_color;
    QColor replacement_color;
    void cut_sprites(std::string sprite_body, std::string sprite_eye, int amount_of_sprites_body, int amount_of_sprites_eye);
    void change_pixmap_color(QPixmap &pixmap);
private slots:
    void auto_change_living_sprite();
    void auto_change_death_sprite();
    void auto_change_scared_sprite();
};

#endif // GHOST_H
