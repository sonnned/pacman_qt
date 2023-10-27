#include "game.h"
#include "ui_game.h"

game::game(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::game)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    pac = new Pac;
    const QColor ghost_target_color = QColor(255, 255, 255);
    const QColor blinky_replacement_color = QColor(255, 0, 0);
    const QColor pinky_replacement_color = QColor(250, 0, 245);
    const QColor clyde_replacement_color = QColor(250, 155, 0);
    const QColor inky_replacement_color = QColor(0, 240, 250);
    blinky = new Ghost(ghost_target_color, blinky_replacement_color);
    pinky = new Ghost(ghost_target_color, pinky_replacement_color, 192, 160);
    clyde = new Ghost(ghost_target_color, clyde_replacement_color, 224, 160);
    inky = new Ghost(ghost_target_color, inky_replacement_color, 256, 160);

    scene->setSceneRect(0, 0, ui->main_scene->width()-2, ui->main_scene->height()-2);
    scene->addItem(pac);
    scene->addItem(blinky);
    scene->addItem(pinky);
    scene->addItem(clyde);
    scene->addItem(inky);

    ui->main_scene->setScene(scene);
    this->setFixedSize(600, 800);
    this->setWindowIcon(QIcon(":/textures/Lives32.png"));
    this->setWindowTitle("Pac-Man");
    this->setStyleSheet("background-color: rgb(28,28,28)");
}

game::~game()
{
    delete ui;
    delete level;
    delete scene;
    delete pac;
    delete blinky;
    delete pinky;
    delete clyde;
    delete inky;
}

void game::keyPressEvent(QKeyEvent *event)
{
    if ((event->key() == Qt::Key_Left || event->key() == Qt::Key_A) && pac->getIs_alive()) {
        pac->setPos(pac->x() - pac->getSpeed(), pac->y());
        if (pac->x() < 0) {
            pac->setPos(0, pac->y());
        }
        pac->setTransformOriginPoint(16, 16);
        pac->setRotation(180);
        pac->setIs_moving(true);
    } else if ((event->key() == Qt::Key_Right || event->key() == Qt::Key_D) && pac->getIs_alive()) {
        pac->setPos(pac->x() + pac->getSpeed(), pac->y());
        if (pac->x() > 600 - pac->getSpeed()) {
            pac->setPos(600 - pac->getSpeed(), pac->y());
        }
        pac->setTransformOriginPoint(16, 16);
        pac->setRotation(0);
        pac->setIs_moving(true);
    } else if ((event->key() == Qt::Key_Up || event->key() == Qt::Key_W) && pac->getIs_alive()) {
        pac->setPos(pac->x(), pac->y() - pac->getSpeed());
        if (pac->y() < 0) {
            pac->setPos(pac->x(), 0);
        }
        pac->setTransformOriginPoint(16, 16);
        pac->setRotation(270);
        pac->setIs_moving(true);
    } else if ((event->key() == Qt::Key_Down || event->key() == Qt::Key_S) && pac->getIs_alive()) {
        pac->setPos(pac->x(), pac->y() + pac->getSpeed());
        if (pac->y() > 800 - pac->getSpeed()) {
            pac->setPos(pac->x(), 800 - pac->getSpeed());
        }
        pac->setTransformOriginPoint(16, 16);
        pac->setRotation(90);
        pac->setIs_moving(true);
    }
}
