#ifndef MESSAGES_H
#define MESSAGES_H

#include <QGraphicsTextItem>
#include <QFontDatabase>
#include <QFont>
#include "game_macros.h"

class Messages: public QGraphicsTextItem
{
public:
    Messages();
public slots:
    void show_message(std::string message);
};

#endif // MESSAGES_H
