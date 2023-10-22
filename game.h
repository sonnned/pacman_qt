#ifndef GAME_H
#define GAME_H

#include "scene.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class game; }
QT_END_NAMESPACE

class game : public QMainWindow
{
    Q_OBJECT
public:
    game(QWidget *parent = nullptr);
    ~game();
private:
    Ui::game *ui;
    Scene *level;
};
#endif // GAME_H
