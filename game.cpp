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
    blinky = new Ghost(ghost_target_color, blinky_replacement_color, 240, 312);
    pinky = new Ghost(ghost_target_color, pinky_replacement_color, 288, 312);
    clyde = new Ghost(ghost_target_color, clyde_replacement_color, 240, 336);
    inky = new Ghost(ghost_target_color, inky_replacement_color, 288, 336);

    scene->setSceneRect(0, 0, ui->main_scene->width()-2, ui->main_scene->height()-2);
    scene->addItem(pac);
    scene->addItem(blinky);
    scene->addItem(pinky);
    scene->addItem(clyde);
    scene->addItem(inky);

    create_map();

    ui->main_scene->setScene(scene);
    this->setFixedSize(552, 696);
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
    delete wall;
}

void game::keyPressEvent(QKeyEvent *event)
{
    if ((event->key() == Qt::Key_Left || event->key() == Qt::Key_A) && pac->getIs_alive()) {
        pac->setPos(pac->x() - pac->getSpeed(), pac->y());
        if (pac->x() < 0) {
            pac->setPos(0, pac->y());
        }
        pac->setTransformOriginPoint(12, 12);
        pac->setRotation(180);
        pac->setIs_moving(true);
    } else if ((event->key() == Qt::Key_Right || event->key() == Qt::Key_D) && pac->getIs_alive()) {
        pac->setPos(pac->x() + pac->getSpeed(), pac->y());
        if (pac->x() > 600 - pac->getSpeed()) {
            pac->setPos(600 - pac->getSpeed(), pac->y());
        }
        pac->setTransformOriginPoint(12, 12);
        pac->setRotation(0);
        pac->setIs_moving(true);
    } else if ((event->key() == Qt::Key_Up || event->key() == Qt::Key_W) && pac->getIs_alive()) {
        pac->setPos(pac->x(), pac->y() - pac->getSpeed());
        if (pac->y() < 0) {
            pac->setPos(pac->x(), 0);
        }
        pac->setTransformOriginPoint(12, 12);
        pac->setRotation(270);
        pac->setIs_moving(true);
    } else if ((event->key() == Qt::Key_Down || event->key() == Qt::Key_S) && pac->getIs_alive()) {
        pac->setPos(pac->x(), pac->y() + pac->getSpeed());
        if (pac->y() > 800 - pac->getSpeed()) {
            pac->setPos(pac->x(), 800 - pac->getSpeed());
        }
        pac->setTransformOriginPoint(12, 12);
        pac->setRotation(90);
        pac->setIs_moving(true);
    }
}

void game::create_map()
{
    std::vector<std::vector<int>> map = {
        { 6, 10, 10, 10, 10, 10, 10, 10, 10, 10, 14, 10, 10, 10, 10, 10, 10, 10, 10, 10, 12 },
        { 5, 15, 15, 15, 15, 15, 15, 15, 15, 15,  5, 15, 15, 15, 15, 15, 15, 15, 15, 15, 5 },
        { 5, 15,  6, 10, 12, 15,  6, 10, 12, 15,  5, 15,  6, 10, 12, 15,  6, 10, 12, 15, 5 },
        { 5, 16,  5,  0,  5, 15,  5,  0,  5, 15,  5, 15,  5,  0,  5, 15,  5,  0,  5, 16, 5 },
        { 5, 15,  3, 10,  9, 15,  3, 10,  9, 15,  1, 15,  3, 10,  9, 15,  3, 10,  9, 15, 5 },
        { 5, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 5 },
        { 5, 15,  6, 14, 12, 15,  4, 15,  6, 14, 14, 14, 12, 15,  4, 15,  6, 14, 12, 15, 5 },
        { 5, 15,  3, 11,  9, 15,  5, 15,  3, 11,  0, 11,  9, 15,  5, 15,  3, 11,  9, 15, 5 },
        { 5, 15, 15, 15, 15, 15,  5, 15, 15, 15,  5, 15, 15, 15,  5, 15, 15, 15, 15, 15, 5 },
        { 3, 10, 10, 10, 12, 15,  7, 10,  8,  0,  1,  0,  2, 10, 13, 15,  6, 10, 10, 10, 9 },
        { 0,  0,  0,  0,  5, 15,  5,  0,  0,  0,  0,  0,  0,  0,  4, 15,  5,  0,  0,  0, 0 },
        { 0,  0,  0,  0,  5, 15,  5,  0,  6,  8, 17,  2, 12,  0,  5, 15,  5,  0,  0,  0, 0 },
        { 2, 10, 10, 10,  9, 15,  1,  0,  5,  0,  0,  0,  5,  0,  1, 15,  3, 10, 10, 10, 8 },
        { 0,  0,  0,  0,  0, 15,  0,  0,  5,  0,  0,  0,  5,  0,  0, 15,  0,  0,  0,  0, 0 },
        { 2, 10, 10, 10, 12, 15,  4,  0,  3, 10, 10, 10,  9,  0,  4, 15,  6, 10, 10, 10, 8 },
        { 0,  0,  0,  0,  5, 15,  5,  0,  0,  0,  0,  0,  0,  0,  5, 15,  5,  0,  0,  0, 0 },
        { 0,  0,  0,  0,  5, 15,  5,  0,  6, 14, 14, 14, 12,  0,  5, 15,  5,  0,  0,  0, 0 },
        { 6, 10, 10, 10,  9, 15,  1,  0,  3, 11,  0, 11,  9,  0,  1, 15,  3, 10, 10, 10,12 },
        { 5, 15, 15, 15, 15, 15, 15, 15, 15, 15,  5, 15, 15, 15, 15, 15, 15, 15, 15, 15, 5 },
        { 5, 15,  2, 10, 12, 15,  2, 10,  8, 15,  1, 15,  2, 10,  8, 15,  6, 10,  8, 15, 5 },
        { 5, 16, 15, 15,  5, 15, 15, 15, 15, 15,  0, 15, 15, 15, 15, 15,  5, 15, 15, 16, 5 },
        { 7, 14, 12, 15,  5, 15,  4, 15,  6, 14, 14, 14, 12, 15,  4, 15,  5, 15,  6, 14,13 },
        { 7, 11,  9, 15,  1, 15,  5, 15,  3, 11,  0, 11,  9, 15,  5, 15,  1, 15,  3, 11,13 },
        { 5, 15, 15, 15, 15, 15,  5, 15, 15, 15,  5, 15, 15, 15,  5, 15, 15, 15, 15, 15, 5 },
        { 5, 15,  2, 10, 10, 10, 11, 10,  8, 15,  1, 15,  2, 10, 11, 10, 10, 10,  8, 15, 5 },
        { 5, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 5 },
        { 3, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9 },
    };

    int current_x = 24;
    int current_y = 24;

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] == 99) std::cout << "X: " << current_x << " Y: " << current_y << std::endl;
            scene->addItem(new Wall(current_x, current_y, map[i][j] + 1));
            current_x += 24;
        }
        current_x = 24;
        current_y += 24;
    }
}
