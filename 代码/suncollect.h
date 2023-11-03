#ifndef SUNCOLLECT_H
#define SUNCOLLECT_H

#include <QWidget>
#include <QMovie>
#include <QMouseEvent>
#include <QSoundEffect>
#include "object.h"
#include "gamescene.h"

/**
 * @brief The sunCollect base class
 */
class sunCollect : public Object
{
    Q_OBJECT
public:
    explicit sunCollect(QWidget *parent = nullptr);
    virtual void act();
signals:
};

/**
 * @brief The Sun derived class
 */
class Sun : public sunCollect
{
public:
    Sun(QWidget* parent=0);
    ~Sun();
    void act();
    int frame;
    double level,speed,accelerate,X_speed=0;
protected:
    void mousePressEvent(QMouseEvent* event);
private:
    QMovie* anim=new QMovie(":/PVZ_image/Sun.gif");
};

/**
 * @brief The sunFall derived class
 */
class sunFall : public sunCollect
{
public:
    sunFall(QWidget* parent=0);
    ~sunFall();
    void act();
    int frame;
    double level, speed;
protected:
    void mousePressEvent(QMouseEvent* event);
private:
    QMovie* anim=new QMovie(":/PVZ_image/Sun.gif");
};


#endif // SUNCOLLECT_H
