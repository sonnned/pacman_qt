#include "messages.h"

Messages::Messages()
{
    QFontDatabase::addApplicationFont(":/emulogic/Emulogic-zrEw.ttf");
    setDefaultTextColor(Qt::white);
    setFont(QFont("Emulogic", 11));
    setPos(MESSAGE_X, MESSAGE_Y);
}

void Messages::show_message(std::string message)
{
    setPlainText(QString::fromStdString(message));
}
