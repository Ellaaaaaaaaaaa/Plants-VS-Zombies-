#include "suncollect.h"
#include <QRandomGenerator>

sunCollect::sunCollect(QWidget *parent)
    : Object{parent}
{}

void sunCollect::act()
{}

/**
 * @brief set sun's falling speed and position
 */
Sun::Sun(QWidget* parent) : sunCollect(parent)
{
    this->setGeometry(260,80,80,80);
    this->setMovie(anim);
    anim->start();
    this->show();
    this->speed=-(rand()%5+7);
    this->accelerate=2;
    this->level=200;
    this->X_speed=rand()%5-2;
    this->frame=500;
}

Sun::~Sun()
{
    delete (this->anim);
}

void Sun::act()
{
    this->raise();
    this->frame--;///<sun exists only 10s
    if(this->frame<=0)
    {
        this->life=false;
    }
    if(this->y()<=this->level)
    {
        this->speed+=this->accelerate;
        this->move(this->x()+this->X_speed, this->y()+this->speed);
    }
}

/**
 * @brief After clicking on sunshine, add 25 sunshine to sunshine bar
 */
void Sun::mousePressEvent(QMouseEvent* event)
{
    this->life=false;
    scene->sunPoint +=25;
}

sunFall::sunFall(QWidget* parent) : sunCollect(parent)
{
    this->setGeometry(rand() % 600 + 320, 0, 80, 80);///Randomly into each column
    this->setMovie(anim);
    anim->start();
    this->show();
    this->speed = 2;
    this->level = rand() % 400 + 100;///Random to row
    this->frame = 750;
}

sunFall::~sunFall()
{
    delete (this->anim);
}

void sunFall::act()
{   ///falling straight
    this->raise();
    this->frame --;
    if (this->frame <= 0)
    {
        this->life = false;
    }
    if (this->y() <= this->level)
    {
        this->move(this->x(), this->y() + this->speed);
    }
}

/**
 * @brief After clicking on sunshine, add 25 sunshine to sunshine bar
 */
void sunFall::mousePressEvent(QMouseEvent* event)
{
    this->life = false;
    scene->sunPoint += 25;
}


