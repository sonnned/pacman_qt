#include "pac.h"

Pac::Pac()
{
    living_pac = new QPixmap;
    pac_sprite_change_timer = new QTimer;
    death_pac = new QPixmap;
    pac_sprite_change_timer->start(1000/30);
    connect(pac_sprite_change_timer, SIGNAL(timeout()), this, SLOT(pac_movement()));
    if (is_alive) {
        connect(pac_sprite_change_timer, SIGNAL(timeout()), this, SLOT(auto_change_living_sprite()));
        cut_sprites(PAC_SPRITES[0], current_living_sprite);
    } else {
        connect(pac_sprite_change_timer, SIGNAL(timeout()), this, SLOT(auto_change_death_sprite()));
        cut_sprites(PAC_SPRITES[1], current_death_sprite);
    }
    setPos(x_pos, y_pos);
}

Pac::~Pac() {
    delete living_pac;
    delete death_pac;
    delete pac_sprite_change_timer;
}

void Pac::setIs_moving(bool newIs_moving)
{
    is_moving = newIs_moving;
}

unsigned int Pac::getSpeed() const
{
    return speed;
}

void Pac::cut_sprites(std::string sprite, int amount_of_sprites)
{
    if (is_alive) {
        QPixmap living_sprite;
        living_sprite.load(QString::fromStdString(sprite));
        *living_pac = living_sprite.copy((amount_of_sprites * LIVING_PAC_WEIGHT) - LIVING_PAC_WEIGHT, 0, LIVING_PAC_WEIGHT, LIVING_PAC_HEIGHT);
    } else {
        QPixmap death_sprite;
        death_sprite.load(QString::fromStdString(sprite));
        *death_pac = death_sprite.copy((amount_of_sprites * DEATH_PAC_WEIGHT) - DEATH_PAC_WEIGHT, 0, DEATH_PAC_WEIGHT, DEATH_PAC_HEIGHT);
    }
}

void Pac::auto_change_living_sprite()
{
    if (current_living_sprite == 3) current_living_sprite = 1;
    else current_living_sprite++;

    if (is_moving) {
        cut_sprites(PAC_SPRITES[0], current_living_sprite);
        is_moving = false;
    } else {
        cut_sprites(PAC_SPRITES[0], 3);
    };
    setPixmap(*living_pac);

}

void Pac::auto_change_death_sprite() {
    if (current_death_sprite == 10) current_death_sprite = 1;
    else current_death_sprite++;

    cut_sprites(PAC_SPRITES[1], current_death_sprite);
    setPixmap(*death_pac);
}

void Pac::pac_movement()
{
    colliding_items = collidingItems();

    for (int i = 0; i < colliding_items.size(); i++) {
        if (typeid(*(colliding_items[i])) == typeid(Ghost)) {
            x_pos = 0;
            y_pos = 0;
            setPos(x_pos, y_pos);
        }
    }
}
