#ifndef ANIMATION_H
#define ANIMATION_H

#include <QWidget>
#include <QMovie>
#include "object.h"
#include "gamescene.h"

///This is the based class of animation
class Animation : public Object
{
    Q_OBJECT
public:
    explicit Animation(QWidget *parent = nullptr);
    void act();
    int frame;///The number of frames for the animation to play
signals:

};

///This is a derived class of animation about setting the bullets fired by the Pea Shooter
class peaHit : public Animation
{
public:
    peaHit(QWidget* parent = nullptr);
    ~peaHit();
private:
    QMovie* anim=new QMovie(":/PVZ_image/PeaShooted.gif");
};

///This is a derived class of animation about setting when to fire the bullets
class Fire : public Animation
{
public:
    Fire(QWidget* parent = 0);
    ~Fire();
private:
    QMovie* anim = new QMovie(":/PVZ_image/Fire.gif");
};

///This is a derived class of animation about zombie's common death
class ZombieDie : public Animation
{
public:
    ZombieDie(QWidget* parent = 0);
    ~ZombieDie();
private:
    QMovie* anim = new QMovie(":/PVZ_image/ZombieDie.gif");
};

///This is a derived class of animation about zombie's death caused by burning
class BurnDie : public Animation
{
public:
    explicit BurnDie(QWidget* parent = 0);
    ~BurnDie();
private:
    QMovie* anim = new QMovie(":/PVZ_image/BurnDie.gif");
};

///This is a derived class of animation about zombie's common death
class ZombieHead : public Animation
{
public:
    ZombieHead(QWidget* parent = 0);
    ~ZombieHead();
private:
    QMovie* anim = new QMovie(":/PVZ_image/ZombieHead.gif");
};

///This is a derived class of animation about Potato Mine's explosion
class PotatoBoom : public Animation
{
public:
    PotatoBoom(QWidget* parent = 0);
    ~PotatoBoom();
private:
    QMovie* anim = new QMovie(":/PVZ_image/PotatoBoom.gif");
};

///This is a derived class of animation about Cherry Bomb's explosion
class Boom : public Animation
{
public:
    Boom(QWidget* parent = 0);
    ~Boom();
private:
    QMovie* anim = new QMovie(":/PVZ_image/Boom.gif");
};

///This is a derived class of animation about pole zombie's common death
class PoleZombieDie : public Animation
{
public:
    PoleZombieDie(QWidget* parent = 0);
    ~PoleZombieDie();
private:
    QMovie* anim = new QMovie(":/PVZ_image/PoleZombieDie.gif");
};

///This is a derived class of animation about pole zombie's common death
class PoleZombieHead : public Animation
{
public:
    PoleZombieHead(QWidget* parent = 0);
    ~PoleZombieHead();
private:
    QMovie* anim = new QMovie(":/PVZ_image/PoleZombieHead.gif");
};


#endif // ANIMATION_H
