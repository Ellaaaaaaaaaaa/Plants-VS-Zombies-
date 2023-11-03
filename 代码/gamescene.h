#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMovie>
#include <QTimer>
#include <QDebug>
#include <QMouseEvent>
#include <QKeyEvent>

#include "object.h"
#include "card.h"
#include "zombie.h"
#include "suncollect.h"
#include "plant.h"
#include "animation.h"
#include "bullet.h"

class Object;
class Animation;
class Plant;
class Zombie;
class Bullet;
class Card;
class sunCollect;

class gameScene : public Object
{
    Q_OBJECT
public:
    explicit gameScene(QWidget *parent = nullptr);
    ~gameScene();

    ///Divide the interface into cell
    QPoint getCell();
    QPoint m;
    QPoint cellSize=QPoint(1,1);
    QRect rect=QRect(0,0,1,1);
    QRect screen=QRect(170,0,900,600);

    ///Generate a list of each class
    QList<Plant*> Plants;
    QList<Zombie*> Zombies;
    QList<Bullet*> Bullets;
    QList<Animation*> Anims;
    QList<sunCollect*> sunCollects;
    QList<Card*> Cards;

    ///Generate a list of pointer
    QTimer* timer = nullptr;
    QLabel* SunFront = new QLabel(this);
    QLabel* SunBack = new QLabel(this);
    QMovie* sunback = new QMovie(":/PVZ_image/SunBack.png");

    void removeDeath();
    void act();
    void createZombie();
    void judge();
    void putPlant(QPoint c);
    void putZombie(int row,int type);
    virtual void uiSetup();

    bool Enemy[6];
    int sunPoint=50;
    int tempSunPoint;
    int threat=0;
    int TimerLose=0;

    QPoint currentPos;
    Card* currentCard=nullptr;
    QLabel *winLabel=new QLabel(this);
    QLabel *failLabel=new QLabel(this);
    QMovie* JudgeWin = new QMovie(":/PVZ_image/win.png");
    QMovie* JudgeFail = new QMovie(":/PVZ_image/fail.png");
protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
signals:
    void toTitle();
    void toStart();
};

class mainScene :public gameScene
{
    Q_OBJECT
public:
    explicit mainScene(QWidget *parent =0);
    ~mainScene();
protected:
    void keyPressEvent(QKeyEvent *event);
private:
    QMovie* background = new QMovie(":/PVZ_image/GameScene.jpg");
    QPushButton* exit = new QPushButton(this);
    QPoint cell;
    void uiSetup();
private slots:
    void onTimer();
    void leave();
};

class StartScene :public gameScene
{
    Q_OBJECT
public:
    explicit StartScene(QWidget* parent = 0);
    ~StartScene();
private:
    QMovie* background = new QMovie(":/PVZ_image/SelectScene.png");
    QMovie* startAdventure = new QMovie(":/PVZ_image/SelectButton.png");
    QLabel* btn1 = new QLabel(this);
    QLabel* title = new QLabel(this);
    QLabel* UserName = new QLabel(this);
    QLabel* BestTime = new QLabel(this);
protected:
    void mousePressEvent(QMouseEvent *event);
};

class StartScreen : public gameScene
{
    Q_OBJECT
public:
    explicit StartScreen(QWidget* parent = 0);
    ~StartScreen();
private:
    QMovie* background = new QMovie(":/PVZ_image/startScreen.gif");
    QWidget* front = new QWidget(this);
    int frame = 100;
private slots:
    void onTimer();
};


























#endif // GAMESCENE_H
