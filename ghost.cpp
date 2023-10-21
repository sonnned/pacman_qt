#include "ghost.h"

Ghost::Ghost()
{
    living_ghost = new QPixmap;
    ghost_sprite_change_timer = new QTimer;
    death_ghost = new QPixmap;
    ghost_sprite_change_timer->start(200);
}

Ghost::~Ghost()
{
    delete living_ghost;
    delete death_ghost;
    delete ghost_sprite_change_timer;
}

