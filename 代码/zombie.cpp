#include "zombie.h"

Zombie::Zombie(QWidget *parent)
    : Object{parent}
{}

void Zombie::act()
{}

void Zombie::hit(int damage, bool silence)
{}

void Zombie::ice()
{}


/**
 * @brief Type: 0 for CommonZombie
 *
 *              1 for FlagZombie
 *
 *              2 for HatZombie
 *
 *              3 for BucketZombie
 * @param iron  whether it contain iron
 * @param prop  whether it contain prop
 */
CommonZombie::CommonZombie(QWidget* parent, int type) : Zombie(parent)
{
    switch (rand()%2)///<Random play gives zombies a dynamic effect
    {
    case 0:
        this->walk=new QMovie(":/PVZ_image/Zombie.gif");
        break;
    case 1:
        this->walk=new QMovie(":/PVZ_image/Zombie_2.gif");
        break;
    }
    this->attack=new QMovie(":/PVZ_image/ZombieAttack.gif");
    switch(type)
    {
    case 0:
        this->prop=false;
        this->iron=false;
        break;
    case 1:
        this->prop=false;
        this->iron=false;
        this->offset=20;
        delete this->walk;
        delete this->attack;
        this->walk=new QMovie(":/PVZ_image/FlagZombie.gif");
        this->attack=new QMovie(":/PVZ_image/FlagZombieAttack.gif");
        break;
    case 2:
        this->prop=true;
        this->iron=false;
        this->proptrSength=300;
        this->propWalk=new QMovie(":/PVZ_image/HatZombie.gif");
        this->propAttack=new QMovie(":/PVZ_image/HatZombieAttack.gif");
        this->offset = 20;
        break;
    case 3:
        this->prop=true;
        this->iron=true;
        this->proptrSength=600;
        this->propWalk=new QMovie(":/PVZ_image/BucketZombie.gif");
        this->propAttack=new QMovie(":/PVZ_image/BucketZombieAttack.gif");
        break;
    }
    this->speed=0.25;
    this->strength=200;
    this->xpos=950;
    if(this->prop)
    {
        this->setMovie(this->propWalk);
        this->walk->start();
        this->propWalk->start();
        this->attack->start();
        this->propAttack->start();
    }
    else
    {
        this->setMovie(this->walk);
        this->walk->start();
        this->attack->start();
    }
    this->show();
}

CommonZombie::~CommonZombie()
{
    delete (this->walk);
    delete (this->attack);
}

void CommonZombie::act()
{
    this->raise();
    Plant* plant;
    foreach(plant,this->scene->Plants)
    {//100/s
        if((qAbs(plant->x()-this->x()-55-this->offset)<40)&&((this->row)==(plant->row))&&(this->life))
        {   ///Zombie distance from plant && on the same line && zombie alive
            if(this->eatFrame<=0)
            {
                //QSoundEffect* sound=new QSoundEffect(this);
                //sound->setSource(QUrl::fromLocalFile("qrc:/PVZ_image/Eat.wav"));
                //sound->play();
                this->eatFrame=20;
            }
            this->eatFrame--;
            if(this->prop)
            {
                this->setMovie(this->propAttack);
            }
            else
            {
                this->setMovie(this->attack);
            }
            plant->hit(2);
            return;
        }
    }
    ///Determine if there are props
    if(this->prop)
    {
        this->setMovie(this->propWalk);
    }
    else
    {
        this->setMovie(this->walk);
    }
    this->xpos-=this->speed;
    this->move(this->xpos,this->y());
}

/**
 * @brief set CommonZombie hit animation
 * @param damage
 * @param silence
 */
void CommonZombie::hit(int damage, bool silence)
{
    if(damage>=200)
    {
        this->life=false;
        Animation*deathAnim=new BurnDie(scene);
        deathAnim->setGeometry(this->x()-30,this->y()+25,180,150);
        this->scene->Anims.append(deathAnim);
        if(!(this->propWalk==nullptr))
        {
            delete this->propWalk;
        }
        if(!(this->propAttack==nullptr))
        {
            delete this->propAttack;
        }
        return;
    }
    if(!(silence))
    {
        if((this->prop)&&(this->iron))
        {
            //QSoundEffect* sound=new QSoundEffect(this);
            //sound->setSource(QUrl::fromLocalFile(":qrc/PVZ_image/ShieldHit.wav"));
            //sound->play();
        }
        else
        {
            //QSoundEffect* sound=new QSoundEffect(this);
            //sound->setSource(QUrl::fromLocalFile(":qrc/PVZ_image/Pea.wav"));
            //sound->play();
        }
    }
    if(this->prop)
    {
        this->proptrSength-=damage;
        if(this->proptrSength<=0)
        {
            this->prop=false;
            this->xpos+=this->offset;
            this->act();
            this->setMovie(this->walk);
            this->walk->start();
            delete this->propWalk;
            delete this->propAttack;
            this->propWalk=nullptr;
            this->propAttack=nullptr;
        }
    }
    else
    {
        this->strength-=damage;
    }
    if(this->strength<=0)
    {
        this->life=false;
        Animation*deathAnim=new ZombieDie(scene);
        deathAnim->setGeometry(this->x() - 30, this->y() + 25, 180, 150);
        this->scene->Anims.append(deathAnim);
        Animation* deathHead = new ZombieHead(scene);
        deathHead->setGeometry(this->x() + 50, this->y() + 25, 180, 200);
        this->scene->Anims.append(deathHead);
    }
}

/**
 * @brief when CommonZombie is iced, its speed and strength will half weaken
 */
void CommonZombie::ice()
{
    if(!iced)
    {
        this->iced=true;
        this->speed/=2;
        if(!(this->walk==nullptr))
        {
           this->walk->setSpeed(50);
        }
        if(!(this->attack==nullptr))
        {
            this->attack->setSpeed(50);
        }
        if(!(this->propWalk==nullptr))
        {
            this->propWalk->setSpeed(50);
        }
        if(!(this->propAttack==nullptr))
        {
            this->propAttack->setSpeed(50);
        }
    }
}

/**
 * @brief PoleZombie's basic elements
 */
PoleZombie::PoleZombie(QWidget* parent) : Zombie(parent)
{
    this->setMovie(this->run);
    this->run->start();
    this->walk->start();
    this->attack->start();
    this->speed = 0.5;
    this->strength = 200;
    this->xpos = 950;
    this->show();
    this->offset = 145;
}

PoleZombie::~PoleZombie()
{
    delete this->walk;
    delete this->attack;
    delete this->run;
    delete this->jump1;
    delete this->jump2;
}

/**
 * @brief PoleZombie's act is different from others
 */
void PoleZombie::act()
{
    this->raise();
    Plant* plant;
    if (this->jumping_1)
    {
        if (this->jump2->currentFrameNumber() >= (this->jump2->frameCount() - 1))
        {   ///Check whether jump2 runs out of frames
            this->jump2->stop();
            this->jumping_1 = false;
            this->speed /= 2;
        }
        return;
    }
    else if ((this->jumping) && (this->jump1->currentFrameNumber() == (this->jump1->frameCount() - 1)) && !(this->jumping_1))
    {   ///Check whether jump1 runs out of frames
        this->jump1->stop();
        this->setMovie(this->jump2);
        this->jump2->start();
        this->xpos -= 110;
        this->move(this->xpos, this->y());
        this->jumping_1 = true;
        this->jumping = false;
        return;
    }
    else if (this->jumping)
    {
        return;
    }
    foreach (plant, this->scene->Plants)
    {
        if ((qAbs(plant->x() - this->x() - 55 - this->offset) < 40) && ((this->row) == (plant->row)) && (this->life))
        {   ///Jump over the first plant you touch
            if (this->poled)
            {
                this->poled = false;
                this->jumping = true;
                this->setMovie(this->jump1);
                this->jump1->start();
                //QSoundEffect* sound=new QSoundEffect(this);
                //sound->setSource(QUrl::fromLocalFile("qrc:/PVZ_image/Pole.wav"));
                //sound->play();
                return;
            }
            else
            {
                if (this->eatFrame <= 0)
                {
                    //QSoundEffect* sound=new QSoundEffect(this);
                    //sound->setSource(QUrl::fromLocalFile("qrc:/PVZ_image/Eat.wav"));
                    //sound->play();
                    this->eatFrame = 20;
                }
                this->eatFrame --;
                this->setMovie(this->attack);
                plant->hit(2);
                return;
            }
        }
    }
    if (this->poled)
    {
        this->setMovie(this->run);
    }
    else
    {
        this->setMovie(this->walk);
    }
    this->xpos -= this->speed;
    this->move(this->xpos, this->y());
}

/**
 * @brief PoleZombie's hit animation
 * @param damage
 * @param silence
 */
void PoleZombie::hit(int damage, bool silence)
{
    if (damage >= 200)
    {
        this->life = false;
        Animation* deathAnim = new BurnDie(scene);
        deathAnim->setGeometry(this->x() - 20 + this->offset, this->y() + 25, 180, 150);
        this->scene->Anims.append(deathAnim);
        return;
    }
    if (!(silence))
    {
        //QSoundEffect* sound=new QSoundEffect(this);
        //sound->setSource(QUrl::fromLocalFile("qrc:/PVZ_image/Pea.wav"));
        //sound->play();
    }
    this->strength -= damage;
    if (this->strength <= 0)
    {
        this->life = false;
        Animation* deathAnim = new PoleZombieDie(scene);
        deathAnim->setGeometry(this->x() - 30, this->y(), 300, 200);
        this->scene->Anims.append(deathAnim);
        Animation* deathHead = new PoleZombieHead(scene);
        deathHead->setGeometry(this->x(), this->y() - 50, 300, 300);
        this->scene->Anims.append(deathHead);
    }
}

/**
 * @brief when PoleZombie is iced, its speed and strength will half weaken
 */
void PoleZombie::ice()
{
    if (!iced)
    {
        this->iced = true;
        this->speed /= 2;
        this->walk->setSpeed(50);
        this->attack->setSpeed(50);
        this->jump1->setSpeed(50);
        this->jump2->setSpeed(50);
        this->run->setSpeed(50);
    }
}


