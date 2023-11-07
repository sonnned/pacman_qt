#include "pac.h"

Pac::Pac()
{
    living_pac = new QPixmap;
    pac_sprite_change_timer = new QTimer;
    death_pac = new QPixmap;
    power_timer = new QTimer;
    pac_sprite_change_timer->start(1000/30);
    connect(pac_sprite_change_timer, SIGNAL(timeout()), this, SLOT(pac_movement()));
    connect(power_timer, SIGNAL(timeout()), this, SLOT(normal_mode()));
    setPos(x_pos, y_pos);
}

Pac::~Pac() {
    delete living_pac;
    delete death_pac;
    delete pac_sprite_change_timer;
    delete power_timer;
}

void Pac::setIs_moving(bool newIs_moving)
{
    is_moving = newIs_moving;
}

unsigned int Pac::getSpeed() const
{
    return speed;
}

bool Pac::getIs_moving() const
{
    return is_moving;
}

bool Pac::getIs_alive() const
{
    return is_alive;
}

bool Pac::getIs_wall_collision() const
{
    return is_wall_collision;
}

void Pac::setIs_wall_collision(bool newIs_wall_collision)
{
    is_wall_collision = newIs_wall_collision;
}

unsigned int Pac::getScore() const
{
    return score;
}

void Pac::cut_sprites(std::string sprite, int amount_of_sprites)
{
    if (is_alive) {
        QPixmap living_sprite;
        living_sprite.load(QString::fromStdString(sprite));
        *living_pac = living_sprite.copy((amount_of_sprites * LIVING_PAC_WEIGHT) - LIVING_PAC_WEIGHT, 0, LIVING_PAC_WEIGHT, LIVING_PAC_HEIGHT);
        *living_pac = living_pac->scaled(24, 24, Qt::KeepAspectRatio);
    } else {
        QPixmap death_sprite;
        death_sprite.load(QString::fromStdString(sprite));
        *death_pac = death_sprite.copy((amount_of_sprites * DEATH_PAC_WEIGHT) - DEATH_PAC_WEIGHT, 0, DEATH_PAC_WEIGHT, DEATH_PAC_HEIGHT);
        *death_pac = death_pac->scaled(24, 24, Qt::KeepAspectRatio);
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

void Pac::pac_movement() {
    colliding_items = collidingItems();

    if (is_alive) {
        for (int i = 0; i < colliding_items.size(); i++) {
            if (typeid(*(colliding_items[i])) == typeid(Ghost)) {
                Ghost *ghost = dynamic_cast<Ghost *>(colliding_items[i]);
                if (!ghost->getIs_alive()) continue;
                if (is_powered) {
                    emit ghost_eaten(ghost->getGhost_id());
                } else {
                    is_alive = false;
                    lives--;
                    pac_sprite_change_timer->setInterval(1000 / 10);
                    return;
                }
            }
            if (typeid(*(colliding_items[i])) == typeid(Wall)) {
                //is_wall_collision = true;
            }
            if (typeid(*(colliding_items[i])) == typeid(Points)) {
                Points *point = dynamic_cast<Points *>(colliding_items[i]); //<- Bajamos el puntero a la clase Points
                if (point->getIs_power()) {
                    score += 500;
                    is_powered = true;
                    power_timer->start(10000);
                    emit scare_ghosts();
                } else {
                    score += 100;
                }
                amount_of_points++;
                scene()->removeItem(colliding_items[i]);
                delete colliding_items[i];
                emit points_eaten(score);
                if (amount_of_points == 192) {
                    emit game_over_message("YOU WIN!");
                    emit game_won();
                    current_living_sprite = 1;
                    cut_sprites(PAC_SPRITES[0], current_living_sprite);
                    setPixmap(*living_pac);
                }
            }
        }

        if (current_living_sprite == 3)
            current_living_sprite = 1;
        else
            current_living_sprite++;

        if (is_moving) {
            cut_sprites(PAC_SPRITES[0], current_living_sprite);
            is_moving = false;
        } else {
            cut_sprites(PAC_SPRITES[0], 3);
        }
        setPixmap(*living_pac);
    } else {
        if (current_death_sprite == 10) {
            current_death_sprite = 1;
            if (lives > 0) {
                is_alive = true;
                x_pos = 264;
                y_pos = 528;
                setPos(x_pos, y_pos);
            } else {
                emit game_over_message("GAME OVER");
                emit game_won();
                current_living_sprite = 1;
                is_alive = true;
            }
        } else
            current_death_sprite++;

        cut_sprites(PAC_SPRITES[1], current_death_sprite);
        setPixmap(*death_pac);
    }
}

void Pac::normal_mode() {
    is_powered = false;
}