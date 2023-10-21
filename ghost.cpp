#include "ghost.h"

Ghost::Ghost()
{
    ghost_body = new QPixmap;
    ghost_eyes = new QPixmap;
    ghost_sprite_change_timer = new QTimer;
    ghost_sprite_change_timer->start(1000/20);

    if (is_alive && !is_scared) {
        connect(ghost_sprite_change_timer, SIGNAL(timeout()), this, SLOT(auto_change_living_sprite()));
        cut_sprites(GHOST_BODY_SPRITES[0], GHOST_EYES_SPRITES[0], current_ghost_body_sprite, current_ghost_eyes_sprite);
    } else if (is_alive && is_scared) {
        connect(ghost_sprite_change_timer, SIGNAL(timeout()), this, SLOT(auto_change_scared_sprite()));
        cut_sprites(GHOST_BODY_SPRITES[0], GHOST_EYES_SPRITES[0], current_ghost_body_sprite, current_ghost_eyes_sprite);
    } else {
        connect(ghost_sprite_change_timer, SIGNAL(timeout()), this, SLOT(auto_change_death_sprite()));
        cut_sprites(GHOST_BODY_SPRITES[0], GHOST_EYES_SPRITES[0], current_ghost_body_sprite, current_ghost_eyes_sprite);
    }

    setPos(x_pos, y_pos);
}

Ghost::~Ghost()
{
    delete ghost_body;
    delete ghost_eyes;
    delete ghost_sprite_change_timer;
}

void Ghost::cut_sprites(std::string sprite_body, std::string sprite_eye, int amount_of_sprites_body, int amount_of_sprites_eye)
{
    if (is_alive && !is_scared) {
        QPixmap living_sprite_body;
        QPixmap living_sprite_eye;
        living_sprite_body.load(QString::fromStdString(sprite_body));
        living_sprite_eye.load(QString::fromStdString(sprite_eye));

        *ghost_body = living_sprite_body.copy((amount_of_sprites_body * GHOST_WEIGHT) - GHOST_WEIGHT, 0, GHOST_WEIGHT, GHOST_HEIGHT);
        *ghost_eyes = living_sprite_eye.copy((amount_of_sprites_eye * GHOST_WEIGHT) - GHOST_WEIGHT, 0, GHOST_WEIGHT, GHOST_HEIGHT);
    } else if (is_alive && is_scared){
        QPixmap scared_sprite_body;
        QPixmap scared_sprite_eye;
        scared_sprite_body.load(QString::fromStdString(sprite_body));
        scared_sprite_eye.load(QString::fromStdString(sprite_eye));

        *ghost_body = scared_sprite_body.copy((amount_of_sprites_body * GHOST_WEIGHT) - GHOST_WEIGHT, 0, GHOST_WEIGHT, GHOST_HEIGHT);
        *ghost_eyes = scared_sprite_eye.copy((amount_of_sprites_eye * GHOST_WEIGHT) - GHOST_WEIGHT, 0, GHOST_WEIGHT, GHOST_HEIGHT);
    } else {
        QPixmap death_sprite_eye;
        death_sprite_eye.load(QString::fromStdString(sprite_eye));

        *ghost_eyes = death_sprite_eye.copy((amount_of_sprites_eye * GHOST_WEIGHT) - GHOST_WEIGHT, 0, GHOST_WEIGHT, GHOST_HEIGHT);
    }
}

void Ghost::auto_change_living_sprite()
{
    if (current_ghost_body_sprite == 6) current_ghost_body_sprite = 1;
    else current_ghost_body_sprite++;

    cut_sprites(GHOST_BODY_SPRITES[0], GHOST_EYES_SPRITES[0], current_ghost_body_sprite, current_ghost_eyes_sprite);
    QColor target_color = QColor(255, 255, 255);
    QColor replacement_color = QColor(255, 0, 0);
    change_pixmap_color(*ghost_body, target_color, replacement_color);


    QPixmap combined_pixmaps(*ghost_body);
    QPainter painter(&combined_pixmaps);

    painter.drawPixmap(0, 0, *ghost_eyes);
    painter.end();

    setPixmap(combined_pixmaps);
}

void Ghost::change_pixmap_color(QPixmap& pixmap, const QColor& target_color, const QColor& replacement_color)
{
    QImage image = pixmap.toImage();

    //Itera pixel
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            QColor pixel_color = image.pixelColor(x, y);
            if (pixel_color == target_color) {
                image.setPixelColor(x, y, replacement_color);
            }
        }
    }
    pixmap = QPixmap::fromImage(image);
}


void Ghost::auto_change_death_sprite()
{
    cut_sprites(GHOST_BODY_SPRITES[0], GHOST_EYES_SPRITES[0], current_ghost_body_sprite, current_ghost_eyes_sprite);
    setPixmap(*ghost_eyes);
}

void Ghost::auto_change_scared_sprite()
{
    if (current_ghost_body_sprite == 6) current_ghost_body_sprite = 1;
    else current_ghost_body_sprite++;

    current_ghost_eyes_sprite = 5;

    cut_sprites(GHOST_BODY_SPRITES[0], GHOST_EYES_SPRITES[0], current_ghost_body_sprite, current_ghost_eyes_sprite);
    QPixmap combined_pixmaps(*ghost_body);
    QPainter painter(&combined_pixmaps);

    painter.drawPixmap(0, 0, *ghost_eyes);
    painter.end();

    setPixmap(combined_pixmaps);
}

