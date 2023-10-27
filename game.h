#ifndef GAME_H
#define GAME_H

#include "scene.h"
#include "pac.h"
#include "ghost.h"
#include "wall.h"

#include <QMainWindow>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QColor>
#include <QPixmap>
#include <QString>
#include <vector>
#include <string>

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
    Wall *wall;
    void keyPressEvent(QKeyEvent *event);
    void create_map();
};
#endif // GAME_H
