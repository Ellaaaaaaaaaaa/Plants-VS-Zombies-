#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include <QLabel>
#include <QMovie>
#include <QSoundEffect>>
#include <QMouseEvent>

#include "object.h"
#include "gamescene.h"

///This is the based class of card
class Card : public Object
{
    Q_OBJECT
public:
    explicit Card(QWidget *parent = nullptr);
    ~Card();
    void setIndex(int index);
    void transFront();
    virtual void act();
    QWidget* front;
    QWidget* back;
    QLabel* frontText;
    int plantIndex;
    int sunPoint=50;
    int frameMax=1,frame=1;
    //QSoundEffect* sound;
protected:
    void mousePressEvent(QMouseEvent*event);
signals:

};

///This is the derived class of sunflower card
class sunFlowerCard : public Card
{
public:
    sunFlowerCard(QWidget *parent = nullptr);
    ~sunFlowerCard();
private:
    QMovie*anim=new QMovie(":/PVZ_image/card_Sunflower.png");
};

///This is the derived class of pea shooter card
class peaShooterCard : public Card
{
public:
    peaShooterCard(QWidget *parent = nullptr);
    ~peaShooterCard();
private:
    QMovie*anim=new QMovie(":/PVZ_image/card_PeaShooter.png");
};

///This is the derived class of wallnut card
class wallNutCard : public Card
{
public:
    wallNutCard(QWidget *parent = nullptr);
    ~wallNutCard();
private:
    QMovie*anim=new QMovie(":/PVZ_image/card_WallNut.png");
};

///This is the derived class of potato mine card
class potatoMineCard : public Card
{
public:
    potatoMineCard(QWidget *parent = nullptr);
    ~potatoMineCard();
private:
    QMovie*anim=new QMovie(":/PVZ_image/card_PotatoMine.png");
};

///This is the derived class of cherry bomb card
class cherryBombCard : public Card
{
public:
    cherryBombCard(QWidget *parent = nullptr);
    ~cherryBombCard();
private:
    QMovie*anim=new QMovie(":/PVZ_image/card_CherryBomb.png");
};

///This is the derived class of ice pea shooter card
class icePeaShooterCard : public Card
{
public:
    icePeaShooterCard(QWidget *parent = nullptr);
    ~icePeaShooterCard();
private:
    QMovie*anim=new QMovie(":/PVZ_image/card_IcePeaShooter.png");
};

///This is the derived class of shovel card
class Shovel : public Card
{
public:
    Shovel(QWidget *parent = nullptr);
    ~Shovel();
private:
    QMovie*anim=new QMovie(":/PVZ_image/Shovel.png");
};
#endif // CARD_H
