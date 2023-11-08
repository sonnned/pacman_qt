#ifndef PAC_H
#define PAC_H

#include "game_macros.h"
#include "ghost.h"
#include "wall.h"
#include "points.h"

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>
#include <QList>
#include <iostream>
#include <vector>
#include <string>

class Pac: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Pac();
    ~Pac();
    void setIs_moving(bool newIs_moving);
    unsigned int getSpeed() const;
    bool getIs_moving() const;
    bool getIs_alive() const;
    bool getIs_wall_collision() const;
    void setIs_wall_collision(bool newIs_wall_collision);
    unsigned int getScore() const;
    void set_freeze(bool freeze) {
        is_freezed = freeze;
    }


 /*
    void incy(int incr);
    void incrx(int incr);
    bool colision_down();
    bool colision_left();
    bool colision_right();
    bool colision_above();
*/
private:
    //Pac variables
    bool is_freezed = false;
    int amount_of_points = 0;
    unsigned int lives = 3;
    unsigned int score = 0;
    unsigned int speed = 6;
    bool is_powered = false;
    bool is_alive = true;
    bool is_moving = false;
    bool is_wall_collision = false;
    int x_pos = 264;
    int y_pos = 528;
    int x_map;
    int y_map;

    //Sprites variables
    unsigned int current_living_sprite = 1;
    unsigned int current_death_sprite = 1;
    const std::vector<std::string> PAC_SPRITES = {":/textures/PacMan32.png", ":/textures/GameOver32.png"};
    //Sprites
    QPixmap *living_pac;
    QPixmap *death_pac;
    QTimer *pac_sprite_change_timer;
    QTimer *power_timer;
    QList <QGraphicsItem*> colliding_items;
    //Sprites methods
    void cut_sprites(std::string sprite, int amount_of_sprites);
private slots:
    //Sprites events
    void auto_change_living_sprite();
    void auto_change_death_sprite();
    void pac_movement();
    void normal_mode();
signals:
    void game_won();
    void points_eaten(int points);
    void scare_ghosts();
    void ghost_eaten(int ghost_id);
    void game_over_message(std::string message);
    void lost_life();
    void pacman_position(int x, int y);
};

#endif // PAC_H
