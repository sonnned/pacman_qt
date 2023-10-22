#ifndef GAME_H
#define GAME_H

#include "scene.h"
#include "pac.h"
#include "ghost.h"

#include <QMainWindow>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QColor>
#include <QPixmap>
#include <QString>

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
    QGraphicsScene *scene;
    Scene *level;
    Pac *pac;
    Ghost *blinky;
    Ghost *pinky;
    Ghost *clyde;
    Ghost *inky;
    void keyPressEvent(QKeyEvent *event);
};
#endif // GAME_H
