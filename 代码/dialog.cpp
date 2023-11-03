#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(QStringLiteral(":/PVZ_image/mainlogo.png")));
    setWindowTitle("Plants V.S. Zombies");
    this->setMouseTracking(true);
    this->setFixedSize(800,600);
    scene=new StartScreen(this);
    connect(this->scene, SIGNAL(toTitle()), this, SLOT(back()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::startGame()
{
    this->setFixedSize(900, 600);
    delete scene;                            ///remeber to delete !!!
    scene = new mainScene(this);
    connect(this->scene, SIGNAL(toTitle()), this, SLOT(back()));
}

void Dialog::back()
{
    this->setFixedSize(800, 600);
    delete scene;
    scene = new StartScene(this);
    connect(this->scene, SIGNAL(toStart()), this, SLOT(startGame()));
}
