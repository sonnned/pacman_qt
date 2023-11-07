#ifndef LIVES_H
#define LIVES_H

#include <QGraphicsTextItem>
#include <QFontDatabase>
#include <QFont>
#include "game_macros.h"

class Lives: public QGraphicsTextItem
{
public:
    Lives();
private:
    int current_lives = 3;
public slots:
    void decrease_lives();
};

#endif // LIVES_H
