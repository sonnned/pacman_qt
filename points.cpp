#include "points.h"

Points::Points(int x_pos, int y_pos, int sprite_position)
{
    points = new QPixmap;
    point_scale_timer = new QTimer;

    if (sprite_position == 17) {
        point_scale_timer->start(1000);
        connect(point_scale_timer, SIGNAL(timeout()), this, SLOT(scale_point()));
        is_power = true;
    }
    cut_sprites(POINT_SPRITES[0], sprite_position, x_pos, y_pos);
}

Points::~Points()
{
    delete points;
    delete point_scale_timer;
}

void Points::cut_sprites(std::string sprite, int amount_of_sprites, int x, int y)
{
    QPixmap points_sprite;
    points_sprite.load(QString::fromStdString(sprite));

    if (amount_of_sprites == 16) {
        *points = points_sprite.copy((1 * WALL_WEIGHT) - WALL_WEIGHT, WALL_HEIGHT, WALL_WEIGHT, WALL_HEIGHT);
    } else if (amount_of_sprites == 17) {
        *points = points_sprite.copy((2 * WALL_WEIGHT) - WALL_WEIGHT, WALL_HEIGHT, WALL_WEIGHT, WALL_HEIGHT);
    }

    *points = points->scaled(24, 24, Qt::KeepAspectRatio);
    setPixmap(*points);
    setPos(x, y);
}

void Points::scale_point()
{
    if (points->width() > 24)
        *points = points->scaled(24, 24, Qt::KeepAspectRatio);
    else
        *points = points->scaled(24 * 1.2, 24 * 1.2, Qt::KeepAspectRatio);

    setPixmap(*points);
}
