#include "animation.h"

Animation::Animation(QWidget *parent)
    : Object{parent}
{}

void Animation::act()
{
    ///Set health to FALSE when the animation is finished
    if ((this->frame) > 0)
    {
        this->frame --;
    }
    else
    {
        this->life = false;
    }
}

peaHit::peaHit(QWidget* parent) : Animation(parent)
{
    ///The bullet animates 2 frames
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 2;
}

peaHit::~peaHit()
{
    delete (this->anim);
}

ZombieDie::ZombieDie(QWidget* parent) : Animation(parent)
{
    ///The bullet animates 50 frames
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 50;
}

ZombieDie::~ZombieDie()
{
    delete (this->anim);
}

BurnDie::BurnDie(QWidget* parent) : Animation(parent)
{
    ///The bullet animates 85 frames
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 85;
}

BurnDie::~BurnDie()
{
    delete (this->anim);
}

ZombieHead::ZombieHead(QWidget* parent) : Animation(parent)
{
    ///The bullet animates 40 frames
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 40;
}

ZombieHead::~ZombieHead()
{
    delete (this->anim);
}

PotatoBoom::PotatoBoom(QWidget* parent) : Animation(parent)
{
    ///The bullet animates 20 frames
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 20;
}

PotatoBoom::~PotatoBoom()
{
    delete (this->anim);
}

Boom::Boom(QWidget* parent) : Animation(parent)
{
    ///The bullet animates 40 frames
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 40;
}

Boom::~Boom()
{
    delete (this->anim);
}

PoleZombieDie::PoleZombieDie(QWidget* parent) : Animation(parent)
{
    ///The bullet animates 50 frames
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 50;
}

PoleZombieDie::~PoleZombieDie()
{
    delete (this->anim);
}

PoleZombieHead::PoleZombieHead(QWidget* parent) : Animation(parent)
{
    ///The bullet animates 40 frames
    this->setMovie(anim);
    anim->start();
    this->show();
    this->frame = 40;
}

PoleZombieHead::~PoleZombieHead()
{
    delete (this->anim);
}
