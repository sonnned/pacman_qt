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
    Ghost(const QColor &target_color, const QColor &replacement_color, int ghost_id);
    Ghost(const QColor &target_color, const QColor &replacement_color, int x_pos, int y_pos, int ghost_id);
    ~Ghost();
    void set_freeze(bool freeze) {
        is_freezed = freeze;
    }
    void scared_mode();
    int getGhost_id() const {
        return ghost_id;
    }
    bool getIs_alive() const {
        return is_alive;
    }
public slots:
    void eaten_mode(int ghost_id);
private:
    int ghost_id;
    //Ghost variables
    bool is_freezed = false;
    bool is_alive = true;
    bool is_scared = false;
    bool is_eaten = false;
    unsigned int speed = 1;
    unsigned int scared_speed = 1;
    unsigned int eaten_speed = 2;
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
    QTimer *scared_timer;
    QColor target_color;
    QColor replacement_color;
    void cut_sprites(std::string sprite_body, std::string sprite_eye, int amount_of_sprites_body, int amount_of_sprites_eye);
    void change_pixmap_color(QPixmap &pixmap);
    void blinky_movement(int pac_x, int pac_y);
    int target_x = 0;
    int target_y = 0;
private slots:
    void auto_change_sprite();
    void normal_mode();
};

#endif // GHOST_H
