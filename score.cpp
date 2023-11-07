#include "score.h"

Score::Score()
{
    QFontDatabase::addApplicationFont(":/emulogic/Emulogic-zrEw.ttf");
    setPlainText(QString("Score: ") + QString::number(current_score));
    setDefaultTextColor(Qt::white);
    setFont(QFont("Emulogic", 14));
    setPos(SCORE_X, SCORE_Y);
}

void Score::increase_score(int points)
{
    current_score = points;
    setPlainText(QString("Score: ") + QString::number(current_score));
}
