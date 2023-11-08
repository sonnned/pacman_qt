#ifndef GAME_H
#define GAME_H

#include "scene.h"
#include "pac.h"
#include "ghost.h"
#include "wall.h"
#include "points.h"
#include "score.h"
#include "messages.h"
#include "lives.h"

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
    Score *score;
    Points *points;
    Messages *message;
    Lives *lives;
    std::vector<std::vector<int>> map;
    void keyPressEvent(QKeyEvent *event);
    void create_map();
    void freeze_game(bool freeze);
    void remove_pixmap();
    bool is_game_freezed = false;
private slots:
    void game_is_won();
};
#endif // GAME_H
