#include "pac.h"

Pac::Pac()
{
    living_pac = new QPixmap;
    pac_sprite_change_timer = new QTimer;
    death_pac = new QPixmap;
    pac_sprite_change_timer->start(100);
    if (is_alive) {
        connect(pac_sprite_change_timer, SIGNAL(timeout()), this, SLOT(auto_change_living_sprite()));
        cut_sprites(PAC_SPRITES[0], current_living_sprite);
        setPixmap(*living_pac);
    } else {
        connect(pac_sprite_change_timer, SIGNAL(timeout()), this, SLOT(auto_change_death_sprite()));
        cut_sprites(PAC_SPRITES[1], current_death_sprite);
        setPixmap(*death_pac);
    }

    setPos(x_pos, y_pos);
    //read the keyboard events
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

Pac::~Pac() {
    delete living_pac;
    delete death_pac;
    delete pac_sprite_change_timer;
}

void Pac::cut_sprites(std::string sprite, int amount_of_sprites)
{
    if (is_alive) {
        QPixmap living_sprite;
        living_sprite.load(QString::fromStdString(sprite));
        *living_pac = living_sprite.copy((amount_of_sprites * LIVING_PAC_WEIGHT) - LIVING_PAC_HEIGHT, 0, LIVING_PAC_WEIGHT, LIVING_PAC_HEIGHT);
    } else {
        QPixmap death_sprite;
        death_sprite.load(QString::fromStdString(sprite));
        *death_pac = death_sprite.copy((amount_of_sprites * DEATH_PAC_WEIGHT) - DEATH_PAC_HEIGHT, 0, DEATH_PAC_WEIGHT, DEATH_PAC_HEIGHT);
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

void Pac::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A) {
        setPos(x() - speed, y());
        if (x() < 0) {
            setPos(0, y());
        }
        setTransformOriginPoint(16, 16);
        setRotation(180);
        is_moving = true;
    } else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D) {
        setPos(x() + speed, y());
        if (x() > 800 - 32) {
            setPos(800 - 32, y());
        }
        setTransformOriginPoint(16, 16);
        setRotation(0);
        is_moving = true;
    } else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W) {
        setPos(x(), y() - speed);
        if (y() < 0) {
            setPos(x(), 0);
        }
        setTransformOriginPoint(16, 16);
        setRotation(270);
        is_moving = true;
    } else if (event->key() == Qt::Key_Down || event->key() == Qt::Key_S) {
        setPos(x(), y() + speed);
        if (y() > 600 - 32) {
            setPos(x(), 600 - 32);
        }
        setTransformOriginPoint(16, 16);
        setRotation(90);
        is_moving = true;
    }
}