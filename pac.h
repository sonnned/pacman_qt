#ifndef PAC_H
#define PAC_H

#include "game_macros.h"
#include "ghost.h"

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
private:
    //Pac variables
    unsigned int lives = 3;
    unsigned int score = 0;
    unsigned int speed = 8;
    unsigned int power_time = 10;
    bool is_powered = false;
    bool is_alive = true;
    bool is_moving = false;
    int x_pos = 0;
    int y_pos = 0;
    //Sprites variables
    unsigned int current_living_sprite = 1;
    unsigned int current_death_sprite = 1;
    const std::vector<std::string> PAC_SPRITES = {":/textures/PacMan32.png", ":/textures/GameOver32.png"};
    //Sprites
    QPixmap *living_pac;
    QPixmap *death_pac;
    QTimer *pac_sprite_change_timer;
    QList <QGraphicsItem*> colliding_items;
    //Sprites methods
    void cut_sprites(std::string sprite, int amount_of_sprites);
private slots:
    //Sprites events
    void auto_change_living_sprite();
    void auto_change_death_sprite();
    void pac_movement();
};

#endif // PAC_H
