#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>
#include <QFontDatabase>
#include <QFont>
#include "game_macros.h"

class Score: public QGraphicsTextItem
{
public:
    Score();
private:
    int current_score = 0;
public slots:
    void increase_score(int points);
};

#endif // SCORE_H
