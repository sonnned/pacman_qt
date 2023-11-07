#include "ghost.h"

Ghost::Ghost(const QColor &target_color, const QColor &replacement_color, int ghost_id)
{
    this->target_color = target_color;
    this->replacement_color = replacement_color;
    this->ghost_id = ghost_id;

    ghost_body = new QPixmap;
    ghost_eyes = new QPixmap;
    ghost_sprite_change_timer = new QTimer;
    scared_timer = new QTimer;
    ghost_sprite_change_timer->start(1000/20);
    connect(ghost_sprite_change_timer, SIGNAL(timeout()), this, SLOT(auto_change_sprite()));
    connect(scared_timer, SIGNAL(timeout()), this, SLOT(normal_mode()));
    setPos(x_pos, y_pos);
}

Ghost::Ghost(const QColor &target_color, const QColor &replacement_color, int x_pos, int y_pos, int ghost_id)
{
    this->target_color = target_color;
    this->replacement_color = replacement_color;
    this->x_pos = x_pos;
    this->y_pos = y_pos;
    this->ghost_id = ghost_id;

    ghost_body = new QPixmap;
    ghost_eyes = new QPixmap;
    ghost_sprite_change_timer = new QTimer;
    scared_timer = new QTimer;
    ghost_sprite_change_timer->start(1000/20);
    connect(ghost_sprite_change_timer, SIGNAL(timeout()), this, SLOT(auto_change_sprite()));
    connect(scared_timer, SIGNAL(timeout()), this, SLOT(normal_mode()));
    setPos(x_pos, y_pos);
}

Ghost::~Ghost()
{
    delete ghost_body;
    delete ghost_eyes;
    delete ghost_sprite_change_timer;
    delete scared_timer;
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

        *ghost_eyes = ghost_eyes->scaled(24, 24, Qt::KeepAspectRatio);
        *ghost_body = ghost_body->scaled(24, 24, Qt::KeepAspectRatio);
    } else if (is_alive && is_scared){
        QPixmap scared_sprite_body;
        QPixmap scared_sprite_eye;
        scared_sprite_body.load(QString::fromStdString(sprite_body));
        scared_sprite_eye.load(QString::fromStdString(sprite_eye));

        *ghost_body = scared_sprite_body.copy((amount_of_sprites_body * GHOST_WEIGHT) - GHOST_WEIGHT, 0, GHOST_WEIGHT, GHOST_HEIGHT);
        *ghost_eyes = scared_sprite_eye.copy((amount_of_sprites_eye * GHOST_WEIGHT) - GHOST_WEIGHT, 0, GHOST_WEIGHT, GHOST_HEIGHT);

        *ghost_eyes = ghost_eyes->scaled(24, 24, Qt::KeepAspectRatio);
        *ghost_body = ghost_body->scaled(24, 24, Qt::KeepAspectRatio);
    } else {
        QPixmap death_sprite_eye;
        death_sprite_eye.load(QString::fromStdString(sprite_eye));

        *ghost_eyes = death_sprite_eye.copy((amount_of_sprites_eye * GHOST_WEIGHT) - GHOST_WEIGHT, 0, GHOST_WEIGHT, GHOST_HEIGHT);

        *ghost_eyes = ghost_eyes->scaled(24, 24, Qt::KeepAspectRatio);
    }
}

void Ghost::change_pixmap_color(QPixmap &pixmap)
{
    QImage image = pixmap.toImage();

    //Itera pixel
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            QColor pixel_color = image.pixelColor(x, y);
            if (pixel_color == target_color && !is_scared) {
                image.setPixelColor(x, y, replacement_color);
            } else if (pixel_color == target_color && is_scared) {
                image.setPixelColor(x, y, Qt::blue);
            }
        }
    }
    pixmap = QPixmap::fromImage(image);
}

void Ghost::auto_change_sprite() {
    if (is_alive && !is_scared) {
        if (current_ghost_body_sprite == 6) current_ghost_body_sprite = 1;
        else current_ghost_body_sprite++;

        cut_sprites(GHOST_BODY_SPRITES[0], GHOST_EYES_SPRITES[0], current_ghost_body_sprite, current_ghost_eyes_sprite);
        change_pixmap_color(*ghost_body);
        QPixmap combined_pixmaps(*ghost_body);
        QPainter painter(&combined_pixmaps);

        painter.drawPixmap(0, 0, *ghost_eyes);
        painter.end();

        setPixmap(combined_pixmaps);
    } else if (is_alive && is_scared) {
        if (current_ghost_body_sprite == 6) current_ghost_body_sprite = 1;
        else current_ghost_body_sprite++;

        current_ghost_eyes_sprite = 5;

        cut_sprites(GHOST_BODY_SPRITES[0], GHOST_EYES_SPRITES[0], current_ghost_body_sprite, current_ghost_eyes_sprite);
        change_pixmap_color(*ghost_body);
        QPixmap combined_pixmaps(*ghost_body);
        QPainter painter(&combined_pixmaps);

        painter.drawPixmap(0, 0, *ghost_eyes);
        painter.end();

        setPixmap(combined_pixmaps);
    } else if (!is_alive && !is_scared && is_eaten) {
        cut_sprites(GHOST_BODY_SPRITES[0], GHOST_EYES_SPRITES[0], current_ghost_body_sprite, current_ghost_eyes_sprite);
        *ghost_eyes = ghost_eyes->scaled(24, 24, Qt::KeepAspectRatio);
        setPixmap(*ghost_eyes);
    }
}

void Ghost::scared_mode()
{
    is_scared = true;
    ghost_sprite_change_timer->start(1000/10);
    scared_timer->start(10000);
}

void Ghost::normal_mode()
{
    is_scared = false;
    current_ghost_eyes_sprite = 1;
    ghost_sprite_change_timer->start(1000/20);
    scared_timer->stop();
}

void Ghost::eaten_mode(int ghost_id)
{
    if (this->ghost_id == ghost_id) {
        is_eaten = true;
        is_alive = false;
        is_scared = false;
        current_ghost_eyes_sprite = 1;
        scared_timer->stop();
    }
}

void Ghost::blinky_movement(int pac_x, int pac_y) {
    target_x = pac_x;
    target_y = pac_y;
}