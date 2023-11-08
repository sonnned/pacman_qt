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
    blinky = new Ghost(ghost_target_color, blinky_replacement_color, 240, 336, 1);
    pinky = new Ghost(ghost_target_color, pinky_replacement_color, 288, 336, 2);
    clyde = new Ghost(ghost_target_color, clyde_replacement_color, 240, 360, 3);
    inky = new Ghost(ghost_target_color, inky_replacement_color, 288, 360, 4);
    score = new Score;
    message = new Messages;
    lives = new Lives;

    scene->setSceneRect(0, 0, ui->main_scene->width()-2, ui->main_scene->height()-2);
    scene->addItem(pac);
    scene->addItem(blinky);
    scene->addItem(pinky);
    scene->addItem(clyde);
    scene->addItem(inky);
    scene->addItem(score);
    scene->addItem(message);
    scene->addItem(lives);

    create_map();

    ui->main_scene->setScene(scene);
    this->setFixedSize(552, 720);
    this->setWindowIcon(QIcon(":/textures/Lives32.png"));
    this->setWindowTitle("Pac-Man");
    this->setStyleSheet("background-color: rgb(28,28,28)");

    connect(pac, &Pac::game_won, this, &game::game_is_won);
    connect(pac, &Pac::points_eaten, score, &Score::increase_score);
    connect(pac, &Pac::scare_ghosts, blinky, &Ghost::scared_mode);
    connect(pac, &Pac::scare_ghosts, pinky, &Ghost::scared_mode);
    connect(pac, &Pac::scare_ghosts, clyde, &Ghost::scared_mode);
    connect(pac, &Pac::scare_ghosts, inky, &Ghost::scared_mode);
    connect(pac, &Pac::ghost_eaten, blinky, &Ghost::eaten_mode);
    connect(pac, &Pac::ghost_eaten, pinky, &Ghost::eaten_mode);
    connect(pac, &Pac::ghost_eaten, clyde, &Ghost::eaten_mode);
    connect(pac, &Pac::ghost_eaten, inky, &Ghost::eaten_mode);
    connect(pac, &Pac::game_over_message, message, &Messages::show_message);
    connect(pac, &Pac::lost_life, lives, &Lives::decrease_lives);
    connect(pac, &Pac::pacman_position, blinky, &Ghost::update_target);
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
    delete points;
    delete score;
    delete message;
    delete lives;
}


    void game::keyPressEvent(QKeyEvent *event)
{
    if (( event->key() == Qt::Key_Left || event->key() == Qt::Key_A) && pac->getIs_alive() && !is_game_freezed) {

        pac->setPos(pac->x() - pac->getSpeed(), pac->y());


        if (pac->getIs_wall_collision()) {

            pac->setPos(pac->x() + pac->getSpeed(), pac->y());
           pac->setIs_wall_collision(false);
            return;
        }
        if (pac->x() < 0) {
            pac->setPos(0, pac->y());
        } else if (pac->x() == 24 && pac->y() == 360) {
            pac->setPos(504, 360);
        }
        pac->setTransformOriginPoint(12, 12);
        pac->setRotation(180);
        pac->setIs_moving(true);
    }
    else if ((event->key() == Qt::Key_Right || event->key() == Qt::Key_D) && pac->getIs_alive() && !is_game_freezed) {

        pac->setPos(pac->x() + pac->getSpeed(), pac->y());
        if (pac->getIs_wall_collision()) {

            pac->setPos(pac->x() - pac->getSpeed(), pac->y());
            pac->setIs_wall_collision(false);
            return;
        }
        if (pac->x() > 552 - 24 - pac->getSpeed()) {
            pac->setPos(552 - 24 - pac->getSpeed(), pac->y());
        } else if (pac->x() == 504 && pac->y() == 360) {
            pac->setPos(24, 360);
        }
        pac->setTransformOriginPoint(12, 12);
        pac->setRotation(0);
        pac->setIs_moving(true);
    } else if ((event->key() == Qt::Key_Up || event->key() == Qt::Key_W) && pac->getIs_alive() && !is_game_freezed) {

        pac->setPos(pac->x(), pac->y() - pac->getSpeed());

        if (pac->getIs_wall_collision()) {
           pac->setPos(pac->x(), pac->y() + pac->getSpeed());
            pac->setIs_wall_collision(false);
            return;

        }


        if (pac->y() < 0) {
            pac->setPos(pac->x(), 0);
        }
        pac->setTransformOriginPoint(12, 12);
        pac->setRotation(270);
        pac->setIs_moving(true);
    } else if ((event->key() == Qt::Key_Down || event->key() == Qt::Key_S) && pac->getIs_alive() && !is_game_freezed) {

        pac->setPos(pac->x(), pac->y() + pac->getSpeed());
        if (pac->getIs_wall_collision()) {

         pac->setPos(pac->x(), pac->y() - pac->getSpeed());
            pac->setIs_wall_collision(false);
            return;
        }
        if (pac->y() > 720 - 24 - pac->getSpeed()) {
            pac->setPos(pac->x(), 720 - 24 - pac->getSpeed());
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
                                         { 0,  0,  0,  0,  5, 15,  5,  0,  0,  0,  0,  0,  0,  0,  5, 15,  5,  0,  0,  0, 0 },
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
//21*27
    int current_x = 24;
    int current_y = 48;

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] == 99) std::cout << "X: " << current_x << " Y: " << current_y << std::endl;
            else if (map[i][j] == 15 || map[i][j] == 16) scene->addItem(new Points(current_x, current_y, map[i][j] + 1));
            else scene->addItem(new Wall(current_x, current_y, map[i][j] + 1));
            current_x += 24;
        }
        current_x = 24;
        current_y += 24;
    }
}






/*
void game::keyPressEvent(QKeyEvent *event)
{
    if ((event->key() == Qt::Key_Left || event->key() == Qt::Key_A) && pac->getIs_alive() && !is_game_freezed) {
          pac->setPos(pac->x() - pac->getSpeed(), pac->y());





        if (pac->x() < 0) {
            pac->setPos(0, pac->y());
        } else if (pac->x() == 24 && pac->y() == 360) {
            pac->setPos(504, 360);
        }
        pac->setTransformOriginPoint(12, 12);
        pac->setRotation(180);
        pac->setIs_moving(true);
    }
    else if ((event->key() == Qt::Key_Right || event->key() == Qt::Key_D) && pac->getIs_alive() && !is_game_freezed) {
        pac->setPos(pac->x() + pac->getSpeed(), pac->y());
        if(pac->colision_right()==false){
            pac->incrx(5);
        }



        if (pac->x() > 552 - 24 - pac->getSpeed()) {
            pac->setPos(552 - 24 - pac->getSpeed(), pac->y());
        } else if (pac->x() == 504 && pac->y() == 360) {
            pac->setPos(24, 360);
        }
        pac->setTransformOriginPoint(12, 12);
        pac->setRotation(0);
        pac->setIs_moving(true);
    } else if ((event->key() == Qt::Key_Up || event->key() == Qt::Key_W) && pac->getIs_alive() && !is_game_freezed) {
        pac->setPos(pac->x(), pac->y() - pac->getSpeed());



        if (pac->y() < 0) {
            pac->setPos(pac->x(), 0);
        }
        pac->setTransformOriginPoint(12, 12);
        pac->setRotation(270);
        pac->setIs_moving(true);
    } else if ((event->key() == Qt::Key_Down || event->key() == Qt::Key_S) && pac->getIs_alive() && !is_game_freezed) {
        pac->setPos(pac->x(), pac->y() + pac->getSpeed());






        if (pac->y() > 720 - 24 - pac->getSpeed()) {
            pac->setPos(pac->x(), 720 - 24 - pac->getSpeed());
        }
        pac->setTransformOriginPoint(12, 12);
        pac->setRotation(90);
        pac->setIs_moving(true);
    }
}

*/

























void game::game_is_won()
{
    freeze_game(true);
    remove_pixmap();
}

void game::remove_pixmap() {
    scene->removeItem(pinky);
    scene->removeItem(blinky);
    scene->removeItem(clyde);
    scene->removeItem(inky);
}

void game::freeze_game(bool freeze) {
    pinky->set_freeze(freeze);
    blinky->set_freeze(freeze);
    clyde->set_freeze(freeze);
    inky->set_freeze(freeze);
    pac->set_freeze(freeze);
    is_game_freezed = freeze;
}
