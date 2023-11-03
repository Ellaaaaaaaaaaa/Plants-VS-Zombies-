#include "plant.h"

Plant::Plant(QWidget *parent)
    : Object{parent}
{}

void Plant::act()
{}
/**
 * @param damage Judge attack damage
 */
void Plant::hit(int damage)
{
    this->strength-=damage;
    if(this->strength<=0)
    {
        this->life=false;
    }
}

///Set up some basic elements
peaShooter::peaShooter(QWidget *parent) : Plant(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->TimerShoot_max = 50;
    this->TimerShoot = this->TimerShoot_max;
    this->strength = 300;
}

/**
 * @brief peaShooter shoot one bullet per 1s
 */
void peaShooter::act()
{
    if (this->TimerShoot <= 0)
    {
        if (!(scene->Enemy[this->row]))
        {
            this->TimerShoot = rand() % 20;// not to shoot too many peas in a single timer event
            return;
        }
        this->TimerShoot = this->TimerShoot_max;
        Pea* pea = new Pea(scene);
        ///prevent bullets overlap
        pea->setGeometry(this->x() + 20, this->y() + 15 - (rand() % 5), 80, 40);
        pea->row = this->row;
        scene->Bullets.append(pea);
    }
    else
    {
        this->TimerShoot --;
    }
}

peaShooter::~peaShooter()
{
    delete this->anim;
}

sunFlower::sunFlower(QWidget *parent) : Plant(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->TimerSun_max = 500;
    this->TimerSun = rand() % this->TimerSun_max;
    this->strength = 300;
}

/**
 * @brief sunFlower generate one sun per 10s
 */
void sunFlower::act()
{
    if (this->TimerSun <= 0)
    {
        this->TimerSun = this->TimerSun_max;
        Sun* sun = new Sun(scene);
        sun->setGeometry(this->x(), this->y() + 15 - (rand() % 5), 80, 80);
        sun->level = this->y() + 40;///fall to the ground
        scene->sunCollects.append(sun);
    }
    else
    {
        this->TimerSun --;
    }
}

sunFlower::~sunFlower()
{
    delete this->anim;
}

wallNut::wallNut(QWidget *parent) : Plant(parent)
{
    this->setMovie(anim);
    anim->start();
    anim1->start();
    anim2->start();
    this->show();
    this->strength = 4000;
}

/**
 * @brief wallNut will change animation states as strength
 */
void wallNut::act()
{
    if (this->strength < 2666)
    {
        this->setMovie(anim1);
    }
    else if (this->strength < 1333)
    {
        this->setMovie(anim2);
    }
}

wallNut::~wallNut()
{
    delete this->anim;
    delete this->anim1;
    delete this->anim2;
}

potatoMine::potatoMine(QWidget *parent) : Plant(parent)
{
    this->setMovie(anim);
    anim->start();
    anim1->start();
    this->show();
    this->strength = 300;
    this->TimerGrow = 750;
}

/**
 * @brief potatoMine takes 15s to ripen after planting
 */
void potatoMine::act()
{
    if (this->TimerGrow > 0)
    {
        this->TimerGrow --;
    }
    else
    {
        this->setMovie(anim1);
        Zombie* zombie;
        foreach (zombie, this->scene->Zombies)
        {
            ///It can only attack a certain range and on the same row
            if ((qAbs(zombie->x() - this->x() + zombie->offset + 50) < 40) && ((this->row) == (zombie->row)))
            {
                if (this->life)
                {
                    Animation* mashedPotato = new PotatoBoom(scene);
                    mashedPotato->setGeometry(this->x() - 40, this->y(), 150, 100);
                    this->scene->Anims.append(mashedPotato);
                    //QSoundEffect* sound=new QSoundEffect(this);
                    //sound->setSource(QUrl::fromLocalFile(":/PVZ_image/Boom.wav"));
                    //sound->play();
                }
                this->life = false;
                zombie->hit(1800);
            }
        }
    }
}

potatoMine::~potatoMine()
{
    delete this->anim;
    delete this->anim1;
}

cherryBomb::cherryBomb(QWidget *parent) : Plant(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->strength = 2000;
    this->TimerBoom = 30;
}

/**
 * @brief cherryBomb bomb after 0.6s
 */
void cherryBomb::act()
{
    if (this->TimerBoom > 0)
    {
        this->TimerBoom --;
    }
    else
    {
        Zombie* zombie;
        ///It can only attack a certain range and on three rows
        foreach (zombie, this->scene->Zombies)
        {
            if ((qAbs(zombie->x() - this->x() + zombie->offset + 50) < 140) && (qAbs(this->row - zombie->row) <= 1))
            {
                zombie->hit(1800);
            }
        }
        Animation* boom = new Boom(scene);
        boom->setGeometry(this->x() - 60, this->y() - 50, 200, 150);
        scene->Anims.append(boom);
        //QSoundEffect* sound=new QSoundEffect(this);
        //sound->setSource(QUrl::fromLocalFile(":/PVZ_image/Boom.wav"));
        //sound->play();
        this->life = false;
    }
}

cherryBomb::~cherryBomb()
{
    delete this->anim;
}

IcePeaShooter::IcePeaShooter(QWidget *parent) : Plant(parent)
{
    this->setMovie(anim);
    anim->start();
    this->show();
    this->TimerShoot_max = 50;
    this->TimerShoot = this->TimerShoot_max;
    this->strength = 300;
}

/**
 * @brief IcePeaShooter weakens zombie's speed and attack
 */
void IcePeaShooter::act()
{
    if (this->TimerShoot <= 0)
    {
        if (!(scene->Enemy[this->row]))
        {
            this->TimerShoot = rand() % 20;///<not to shoot too many peas in a single timer event
            return;
        }
        this->TimerShoot = this->TimerShoot_max;
        IcePea* pea = new IcePea(scene);
        pea->setGeometry(this->x() + 20, this->y() + 15 - (rand() % 5), 80, 40);
        pea->row = this->row;
        scene->Bullets.append(pea);
    }
    else
    {
        this->TimerShoot --;
    }
}

IcePeaShooter::~IcePeaShooter()
{
    delete this->anim;
}

