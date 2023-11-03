#ifndef BULLET_H
#define BULLET_H

#include <QWidget>
#include <QMovie>

#include "object.h"
#include "gamescene.h"
#include "animation.h"

///This is the based class of bullet
class Bullet : public Object
{
    Q_OBJECT
public:
    explicit Bullet(QWidget *parent = nullptr);
    virtual void act();
    int row;
    bool shoot=false;
signals:
};

///This is a derived class of bullet about the bullets of Pea Shooter
class Pea : public Bullet
{
public:
    Pea(QWidget* parent =0);
    ~Pea();
    void act();
private:
    QMovie* anim = new QMovie(":/PVZ_image/Pea.gif");
    int speed;
};

///This is a derived class of bullet about the bullets of Ice Pea Shooter
class IcePea : public Bullet
{
public:
    IcePea(QWidget* parent = 0);
    ~IcePea();
    void act();
private:
    QMovie* anim = new QMovie(":/PVZ_image/IcePea.gif");
    int speed;
};

#endif // BULLET_H
