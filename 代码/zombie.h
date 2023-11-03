#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QWidget>
#include <QMovie>
#include <QDebug>
#include <QMouseEvent>
#include <QSoundEffect>
#include "object.h"
#include "gamescene.h"

/**
 * @brief The Zombie base class
 */
class Zombie : public Object
{
    Q_OBJECT
public:
    explicit Zombie(QWidget *parent = nullptr);
    virtual void act();
    virtual void hit(int damage,bool silence=false);
    virtual void ice();
    int row;
    int offset=0;
    int eatFrame=0;
    bool iced=false;
    double speed;
signals:
};

/**
 * @brief The CommonZombie derived class
 */
class CommonZombie : public Zombie
{
    Q_OBJECT
public:
    CommonZombie(QWidget* parent =0, int type=0);
    ~CommonZombie();
    void act();
    void hit(int damage,bool silence=false);
    void ice();
private:
    QMovie* walk = nullptr;
    QMovie* attack = nullptr;
    QMovie* propWalk = nullptr;
    QMovie* propAttack = nullptr;
    bool prop, iron;
    int proptrSength;
    double xpos;

};

/**
 * @brief The PoleZombie derived class
 */
class PoleZombie : public Zombie
{
    Q_OBJECT
public:
    PoleZombie(QWidget* parent = 0);
    ~PoleZombie();
    void act();
    void hit(int damage, bool silence = false);
    void ice();
private:
    QMovie* walk = new QMovie(":/PVZ_image/PoleZombieWalk.gif");
    QMovie* attack = new QMovie(":/PVZ_image/PoleZombieAttack.gif");
    QMovie* run = new QMovie(":/PVZ_image/PoleZombie.gif");
    QMovie* jump1 = new QMovie(":/PVZ_image/PoleZombieJump.gif");
    QMovie* jump2 = new QMovie(":/PVZ_image/PoleZombieJump2.gif");
    bool poled = true;
    bool jumping = false, jumping_1 = false;
    float xpos;
};



#endif // ZOMBIE_H
