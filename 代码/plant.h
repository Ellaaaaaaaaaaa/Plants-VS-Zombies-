#ifndef PLANT_H
#define PLANT_H

#include <QWidget>
#include <QLabel>
#include <QMovie>
#include <QDebug>
#include <QSoundEffect>>
#include <QMouseEvent>

#include "object.h"
#include "gamescene.h"
#include "bullet.h"

/**
 * @brief The Plant base class
 */
class Plant : public Object
{
    Q_OBJECT
public:
    explicit Plant(QWidget *parent = nullptr);
    virtual void act();
    virtual void hit(int damage);
    int row,column;
    //QSoundEffect* sound;
signals:
};

/**
 * @brief The peaShooter derived class
 */
class peaShooter : public Plant
{
    Q_OBJECT
public:
    peaShooter(QWidget* parent = 0);
    ~peaShooter();
    void act();
private:
    QMovie* anim = new QMovie(":/PVZ_image/Peashooter.gif");
    int TimerShoot, TimerShoot_max;
};

/**
 * @brief The sunFlower derived class
 */
class sunFlower : public Plant
{
    Q_OBJECT
public:
    sunFlower(QWidget* parent = 0);
    ~sunFlower();
    void act();
private:
    QMovie* anim = new QMovie(":/PVZ_image/SunFlower.gif");
    int TimerSun, TimerSun_max;
};

/**
 * @brief The wallNut derived class
 */
class wallNut : public Plant
{
    Q_OBJECT
public:
    wallNut(QWidget* parent = 0);
    ~wallNut();
    void act();
private:
    QMovie* anim = new QMovie(":/PVZ_image/Wallnut.gif");
    QMovie* anim1 = new QMovie(":/PVZ_image/Wallnut1.gif");
    QMovie* anim2 = new QMovie(":/PVZ_image/Wallnut2.gif");
};

/**
 * @brief The potatoMine derived class
 */
class potatoMine : public Plant
{
    Q_OBJECT
public:
    potatoMine(QWidget* parent = 0);
    ~potatoMine();
    void act();
private:
    QMovie* anim = new QMovie(":/PVZ_image/PotatoMine1.gif");
    QMovie* anim1 = new QMovie(":/PVZ_image/PotatoMine.gif");
    int TimerGrow;
};

/**
 * @brief The cherryBomb derived class
 */
class cherryBomb : public Plant
{
    Q_OBJECT
public:
    cherryBomb(QWidget* parent = 0);
    ~cherryBomb();
    void act();
private:
    QMovie* anim = new QMovie(":/PVZ_image/CherryBomb.gif");
    int TimerBoom;
};

/**
 * @brief The IcePeaShooter derived class
 */
class IcePeaShooter : public Plant
{
    Q_OBJECT
public:
    IcePeaShooter(QWidget* parent = 0);
    ~IcePeaShooter();
    void act();
private:
    QMovie* anim = new QMovie(":/PVZ_image/IcePeaShooter.gif");
    int TimerShoot, TimerShoot_max;
};

#endif // PLANT_H
