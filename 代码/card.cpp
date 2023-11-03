#include "card.h"

Card::Card(QWidget *parent)
    : Object{parent}
{
    this->setCursor(Qt::PointingHandCursor);///set cusor
    back=new QWidget(this);
    back->setStyleSheet("background-color:rgba(0,0,0,50%);");///set back card to be half transparent
    back->show();
    back->raise();
    front = new QWidget(this);
    front->setStyleSheet("background-color: rgba(0, 0, 0, 50%);");///set front card to be half transparent
    front->show();
    front->raise();
    frontText=new QLabel(this);
    frontText->setText("50");
    frontText->setGeometry(60,33,40,20);
    frontText->setAlignment(Qt::AlignHCenter);///set Horizontal Alignment
    frontText->setFont(QFont("Calibri",11));///set text size
    frontText->show();
    frontText->raise();
    this->show();
    this->raise();
}

void Card::act()
{
    if(this->frame>0)
    {
        this->frame--;
    }
    this->transFront();///Make it transparent to simulate a cooldown
    this->raise();
}

void Card::setIndex(int index)
{
    this->setGeometry(125,40+60*index,100,60);
}

///Set up the effect of the card cooling
void Card::transFront()
{
    ///The front cards are presented one part at a time according to the number of frames, faked to have a cool time
    front->setGeometry(0,6,100,54*this->frame/this->frameMax);
    if(scene->sunPoint>=this->sunPoint)
    {
        back->setGeometry(0,0,0,0);
    }
    else
    {
        back->setGeometry(0,6,100,54);
    }
}

/// get the mouse cursor
void Card::mousePressEvent(QMouseEvent* event)
{
    if (scene->currentCard != nullptr)
    {
        scene->currentCard->move(scene->currentPos);
    }
    ///Determine whether the sun is sufficient and whether the card cooldown is over
    if (event->button() == Qt::LeftButton)
    {
        if (this->front->height() > 0)
        {
            QSoundEffect* sound=new QSoundEffect(this);
            sound->setSource(QUrl::fromLocalFile(":/PVZ_image/NotEnoughSun.wav"));
            sound->play();
            scene->currentCard = nullptr;
            return;
        }
        if (this->scene->sunPoint < this->sunPoint)
        {
            QSoundEffect* sound=new QSoundEffect(this);
            sound->setSource(QUrl::fromLocalFile(":/PVZ_image/NotEnoughSun.wav"));
            sound->play();
            scene->currentCard = nullptr;
            return;
        }
        scene->currentPos = this->pos();///The card moves to the cursor position
        scene->currentCard = this;
    }
    else
    {
        scene->currentCard = nullptr;
    }
}

Card::~Card()
{
    delete (this->back);
    delete (this->front);
    delete (this->frontText);
}

///Cooling time 2s
sunFlowerCard::sunFlowerCard(QWidget* parent) : Card(parent)
{
    this->setMovie(anim);
    anim->start();
    this->frontText->setText("50");
    this->frameMax=100;
    this->frame=100;
    this->plantIndex=1;
    this->sunPoint=50;
}

sunFlowerCard::~sunFlowerCard()
{
    delete this->anim;
}

///Cooling time 2s
peaShooterCard::peaShooterCard(QWidget* parent) : Card(parent)
{
    this->setMovie(anim);
    anim->start();
    this->frontText->setText("100");
    this->frameMax=100;
    this->frame=100;
    this->plantIndex=2;
    this->sunPoint=100;
}

peaShooterCard::~peaShooterCard()
{
    delete this->anim;
}

///Cooling time 8s
wallNutCard::wallNutCard(QWidget* parent) : Card(parent)
{
    this->setMovie(anim);
    anim->start();
    this->frontText->setText("50");
    this->frameMax=400;
    this->frame=400;
    this->plantIndex=3;
    this->sunPoint=50;
}

wallNutCard::~wallNutCard()
{
    delete this->anim;
}

///Cooling time 8s
potatoMineCard::potatoMineCard(QWidget* parent) : Card(parent)
{
    this->setMovie(anim);
    anim->start();
    this->frontText->setText("25");
    this->frameMax=400;
    this->frame=400;
    this->plantIndex=4;
    this->sunPoint=25;
}

potatoMineCard::~potatoMineCard()
{
    delete this->anim;
}

///Cooling time 10s
cherryBombCard::cherryBombCard(QWidget* parent) : Card(parent)
{
    this->setMovie(anim);
    anim->start();
    this->frontText->setText("150");
    this->frameMax=500;
    this->frame=500;
    this->plantIndex=5;
    this->sunPoint=150;
}

cherryBombCard::~cherryBombCard()
{
    delete this->anim;
}

///Cooling time 2s
icePeaShooterCard::icePeaShooterCard(QWidget* parent) : Card(parent)
{
    this->setMovie(anim);
    anim->start();
    this->frontText->setText("175");
    this->frameMax=100;
    this->frame=100;
    this->plantIndex=6;
    this->sunPoint=175;
}

icePeaShooterCard::~icePeaShooterCard()
{
    delete this->anim;
}

Shovel::Shovel(QWidget* parent) : Card(parent)
{
    this->setMovie(anim);
    this->setGeometry(250,5,76,34);
    anim->start();
    this->frontText->setText("");
    this->frameMax=1;
    this->frame=0;
    this->plantIndex=0;
    this->sunPoint=0;
}

Shovel::~Shovel()
{
    delete this->anim;
}
