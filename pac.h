#ifndef PAC_H
#define PAC_H

#include "game_macros.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <iostream>
#include <vector>
#include <string>

class Pac: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Pac();
    ~Pac();
private:
    //Pac variables
    unsigned int lives = 3;
    unsigned int score = 0;
    unsigned int speed = 1;
    unsigned int power_time = 10;
    bool is_powered = false;
    bool is_alive = false;
    //Sprites variables
    unsigned int current_living_sprite = 1;
    unsigned int current_death_sprite = 1;
    const std::vector<std::string> PAC_SPRITES = {":/textures/PacMan32.png", ":/textures/GameOver32.png"};
    //Sprites
    QPixmap *living_pac;
    QPixmap *death_pac;
    QTimer *pac_sprite_change_timer;
    //Sprites methods
    void cut_sprites(std::string sprite, int amount_of_sprites);
private slots:
    //Sprites events
    void auto_change_living_sprite();
    void auto_change_death_sprite();
};

#endif // PAC_H
