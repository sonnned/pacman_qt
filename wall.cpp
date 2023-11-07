#include "wall.h"

Wall::Wall(int x_pos, int y_pos, int sprite_position)
{
    wall = new QPixmap;
    if (sprite_position == 1 || sprite_position == 16 || sprite_position == 17) {
        return;
    }
    cut_sprites(WALL_SPRITES[0], sprite_position, x_pos, y_pos);
}

Wall::~Wall()
{
    delete wall;
}

void Wall::cut_sprites(std::string sprite, int amount_of_sprites, int x, int y)
{
    QPixmap wall_sprite;
    wall_sprite.load(QString::fromStdString(sprite));
    //*wall = wall_sprite.copy((amount_of_sprites * WALL_WEIGHT) - WALL_WEIGHT, 0, WALL_WEIGHT, WALL_HEIGHT);

    if (amount_of_sprites == 11) {
        *wall = wall_sprite.copy((amount_of_sprites * WALL_WEIGHT) - WALL_WEIGHT, 0, WALL_WEIGHT, WALL_HEIGHT);
    } else if (amount_of_sprites == 2) {
        *wall = wall_sprite.copy((amount_of_sprites * WALL_WEIGHT) - WALL_WEIGHT, 0, WALL_WEIGHT, WALL_HEIGHT);
    } else if (amount_of_sprites == 3) {
        *wall = wall_sprite.copy((amount_of_sprites * WALL_WEIGHT) - WALL_WEIGHT, 0, WALL_WEIGHT, WALL_HEIGHT);
    } else if (amount_of_sprites == 4) {
        *wall = wall_sprite.copy((amount_of_sprites * WALL_WEIGHT) - WALL_WEIGHT, 0, WALL_WEIGHT, WALL_HEIGHT);
    } else if (amount_of_sprites == 5) {
        *wall = wall_sprite.copy((amount_of_sprites * WALL_WEIGHT) - WALL_WEIGHT, 0, WALL_WEIGHT, WALL_HEIGHT);
    } else if (amount_of_sprites == 6) {
        *wall = wall_sprite.copy((amount_of_sprites * WALL_WEIGHT) - WALL_WEIGHT, 0, WALL_WEIGHT, WALL_HEIGHT);
    } else if (amount_of_sprites == 7) {
        *wall = wall_sprite.copy((amount_of_sprites * WALL_WEIGHT) - WALL_WEIGHT, 0, WALL_WEIGHT, WALL_HEIGHT);
    } else if (amount_of_sprites == 8) {
        *wall = wall_sprite.copy((amount_of_sprites * WALL_WEIGHT) - WALL_WEIGHT, 0, WALL_WEIGHT, WALL_HEIGHT);
    } else if (amount_of_sprites == 9) {
        *wall = wall_sprite.copy((amount_of_sprites * WALL_WEIGHT) - WALL_WEIGHT, 0, WALL_WEIGHT, WALL_HEIGHT);
    } else if (amount_of_sprites == 10) {
        *wall = wall_sprite.copy((amount_of_sprites * WALL_WEIGHT) - WALL_WEIGHT, 0, WALL_WEIGHT, WALL_HEIGHT);
    } else if (amount_of_sprites == 12) {
        *wall = wall_sprite.copy((amount_of_sprites * WALL_WEIGHT) - WALL_WEIGHT, 0, WALL_WEIGHT, WALL_HEIGHT);
    } else if (amount_of_sprites == 13) {
        *wall = wall_sprite.copy((amount_of_sprites * WALL_WEIGHT) - WALL_WEIGHT, 0, WALL_WEIGHT, WALL_HEIGHT);
    } else if (amount_of_sprites == 14) {
        *wall = wall_sprite.copy((amount_of_sprites * WALL_WEIGHT) - WALL_WEIGHT, 0, WALL_WEIGHT, WALL_HEIGHT);
    } else if (amount_of_sprites == 15) {
        *wall = wall_sprite.copy((amount_of_sprites * WALL_WEIGHT) - WALL_WEIGHT, 0, WALL_WEIGHT, WALL_HEIGHT);
    } else if (amount_of_sprites == 18) {
        *wall = wall_sprite.copy((3 * WALL_WEIGHT) - WALL_WEIGHT, WALL_HEIGHT, WALL_WEIGHT, WALL_HEIGHT);
    }

    *wall = wall->scaled(24, 24, Qt::KeepAspectRatio);
    setPixmap(*wall);
    setPos(x, y);
}
