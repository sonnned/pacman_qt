#include "lives.h"

Lives::Lives()
{
    QFontDatabase::addApplicationFont(":/emulogic/Emulogic-zrEw.ttf");
    setPlainText(QString("Lives: ") + QString::number(current_lives));
    setDefaultTextColor(Qt::white);
    setFont(QFont("Emulogic", 14));
    setPos(LIVES_X, LIVES_Y);
}

void Lives::decrease_lives()
{
    current_lives--;
    setPlainText(QString("Lives: ") + QString::number(current_lives));
}
