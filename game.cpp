#include "game.h"
#include "ui_game.h"

game::game(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::game)
{
    ui->setupUi(this);
    level = new Scene;
    level->set_graphicsview(ui->main_scene);

    //set the size of the window
    this->setFixedSize(800,600);
    //set the title of the window
    this->setWindowTitle("Pac-Man");
    //set the icon of the window
    this->setWindowIcon(QIcon(":/textures/Lives32.png"));
    //set the background color
    this->setStyleSheet("background-color: rgb(28,28,28);");
}

game::~game()
{
    delete ui;
    delete level;
}

