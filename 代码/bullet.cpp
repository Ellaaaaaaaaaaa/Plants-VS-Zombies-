#include "bullet.h"

Bullet::Bullet(QWidget *parent)
    : Object{parent}
{}

void Bullet::act()
{}

///Set the bullet speed to 10 and start shooting
Pea::Pea(QWidget* parent) : Bullet(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->speed=10;
    this->shoot=true;
}

void Pea::act()
{
    this->raise();
    ///Determine whether the current position is within the boundary
    if(!(this->scene->screen.contains(this->pos())))
    {
         this->life=false;
    }
    ///shoot at given speed
    this->move(this->x()+this->speed,this->y());
    Zombie* zombie;
    foreach (zombie, this->scene->Zombies)
        {
            ///Judge the distance between the zombie and the bullet, pass the zombie will stop
            ///Determine if zombies are in line with bullets
            ///Determine if its live is true
            if ((qAbs(zombie->x() - this->x() + zombie->offset + 60) < 20) && ((this->row) == (zombie->row)) && (this->life))
            {
                this->life = false;
                Animation* peaAnim = new peaHit(scene);
                peaAnim->setGeometry(this->x() + 20, this->y(), 40, 40);
                this->scene->Anims.append(peaAnim);
                zombie->hit(20);///<Damage is 20
                return;
            }
        }
}

Pea::~Pea()
{
    delete this->anim;
}

///Set the bullet speed to 10 and start shooting
IcePea::IcePea(QWidget* parent) : Bullet(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->speed = 10;
    this->shoot = true;
}

void IcePea::act()
{
    this->raise();
    ///Determine whether the current position is within the boundary
    if (!(this->scene->screen.contains(this->pos())))
    {
        this->life = false;
    }
    this->move(this->x() + this->speed , this->y());
    Zombie* zombie;
    ///Judge the distance between the zombie and the bullet, pass the zombie will stop
    ///Determine if zombies are in line with bullets
    ///Determine if its live is true
    foreach (zombie, this->scene->Zombies)
    {
        if ((qAbs(zombie->x() - this->x() + zombie->offset + 60) < 20) && ((this->row) == (zombie->row)) && (this->life))
        {
            this->life = false;
            Animation* peaAnim = new peaHit(scene);
            peaAnim->setGeometry(this->x() + 20, this->y(), 40, 40);
            this->scene->Anims.append(peaAnim);
            zombie->ice();
            zombie->hit(20);
            return;
        }
    }
}

IcePea::~IcePea()
{
    delete this->anim;
}

