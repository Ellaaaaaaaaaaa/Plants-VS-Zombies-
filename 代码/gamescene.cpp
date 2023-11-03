#include "gamescene.h"
#include<QFile>
#include<QTextStream>

///track the mouse action
gameScene::gameScene(QWidget *parent)
    : Object{parent}
{
    this->setMouseTracking(true);
    this->grabKeyboard();
}

gameScene::~gameScene()
{
    while (!Zombies.empty())
    {
        delete Zombies[0];                 //delete QList
        Zombies.removeAt(0);
    }
    while (!Plants.empty())
    {
        delete Plants[0];
        Plants.removeAt(0);
    }
    while (!Bullets.empty())
    {
        delete Bullets[0];
        Bullets.removeAt(0);
    }
    while (!Anims.empty())
    {
        delete Anims[0];
        Anims.removeAt(0);
    }
    while (!sunCollects.empty())
    {
        delete sunCollects[0];
        sunCollects.removeAt(0);
    }
    while (!Cards.empty())
    {
        delete Cards[0];
        Cards.removeAt(0);
    }
    if (!(this->SunFront == nullptr))
        delete this->SunFront;
    if (!(this->SunBack == nullptr))
        delete this->SunBack;
    if (!(this->sunback == nullptr))
        delete this->sunback;
    if (!(this->winLabel == nullptr))
        delete this->winLabel;
    if (!(this->failLabel == nullptr))
        delete this->failLabel;
    if (!(this->timer == nullptr))
        delete this->timer;
}

QPoint gameScene::getCell()
{
    if (this->rect.contains(this->m))///Determine if the point is inside
    {
        ///return the position of cell
        return QPoint((this->m.x() - this->rect.left()) / this->cellSize.x(),
                      (this->m.y() - this->rect.top()) / this->cellSize.y());
    }
    else
    {
        return QPoint(-1, -1);
    }
}

///clear the object from screen which life is false
void gameScene::removeDeath()
{
    int p = 0;
    while (p < Plants.count())
    {
        if (!(Plants[p]->life))
        {
            delete (Plants[p]);
            Plants.removeAt(p);
        }
        else
        {
            p++;
        }
    }
    for (int i = 0; i < 6; i++)
    {
        this->Enemy[i] = false;
    }
    p = 0;
    while (p < Zombies.count())
    {
        if (!(Zombies[p]->life))
        {
            delete (Zombies[p]);
            Zombies.removeAt(p);
        }
        else
        {
            ///Determine which lines have zombies
            this->Enemy[Zombies[p]->row] = true;
            p++;
        }
    }
    p = 0;
    while (p < Bullets.count())
    {
        if (!(Bullets[p]->life))
        {
            delete (Bullets[p]);
            Bullets.removeAt(p);
        }
        else
        {
            p++;
        }
    }
    p = 0;
    while (p < Anims.count())
    {
        if (!(Anims[p]->life))
        {
            delete (Anims[p]);
            Anims.removeAt(p);
        }
        else
        {
            p++;
        }
    }
    p = 0;
    while (p < sunCollects.count())
    {
        if (!(sunCollects[p]->life))
        {
            delete (sunCollects[p]);
            sunCollects.removeAt(p);
        }
        else
        {
            p++;
        }
    }
}

///All created objects call act()
void gameScene::act()
{
    Object* i;
    foreach(i, Zombies)
    {
        i->act();
    }
    foreach(i, Plants)
    {
        i->act();
    }
    foreach(i, Bullets)
    {
        i->act();
    }
    foreach(i, Anims)
    {
        i->act();
    }
    foreach(i, sunCollects)
    {
        i->act();
    }
    foreach(i, Cards)
    {
        i->act();
    }
}

///create zombie and determine if you win
void gameScene::createZombie()
{
    if (this->threat < 9001 && this->threat>-1)///The entire game lasts three minutes
    {
        this->threat ++;
        if (this->Zombies.count() < (this->threat / 600))///It takes 12 seconds to start creating zombies
        {
            if (this->threat < 5000)
            {
                this->putZombie(rand() % 5, 0);///Create normal zombies before 100s
            }
            else
            {
                this->putZombie(rand() % 5, rand() % 5);///Create all zombies after 100s
            }
        }
    }
    else if(this->threat>9000)
    {
        ///No more create zombies, determine the number of zombies at this time
        if(this->Zombies.count()==0)///When the number of zombies reaches zero
        {
            this->currentCard = nullptr;///the card screen is cleared and the winner is judged
            while (!Cards.empty())
            {
                delete Cards[0];
                Cards.removeAt(0);
            }
            this->SunBack->hide();
            this->SunFront->hide();
            this->move(0, 0);
            this->TimerLose = 100;
            this->threat = -200;
            JudgeWin->start();
            winLabel->setMovie(JudgeWin);
            winLabel->setGeometry(70,36,664,536);
            winLabel->show();
            return;
        }
    }
    else if(this->threat<-1)///Not so fast to jump back
    {
        this->threat++;
    }
    if(this->threat==-1)
    {
        emit toTitle();///Returns the selection scene at the beginning
    }
}

///Determine if you fail
void gameScene::judge()
{
    if (this->TimerLose > 1)///Not so fast to jump back
    {
        this->TimerLose --;
    }
    else
    {
        if (this->TimerLose == 1)
        {
            emit toTitle();///Returns the selection scene at the beginning
        }
        else
        {
            Zombie* zombie;
            foreach(zombie, Zombies)
            {
                ///The game is judged to fail when a zombie reaches the door
                if (zombie->x() + zombie->offset < 130)
                {
                    this->currentCard = nullptr;///the card screen is cleared and the failure is judged
                    while (!Cards.empty())
                    {
                        delete Cards[0];
                        Cards.removeAt(0);
                    }
                    this->SunBack->hide();
                    this->SunFront->hide();
                    this->move(0, 0);
                    this->TimerLose = 100;
                    JudgeFail->start();
                    failLabel->setMovie(JudgeFail);
                    failLabel->setGeometry(120,66,564,468);
                    failLabel->show();
                    return;
                }
            }
        }
    }
}

void gameScene::uiSetup()
{}

void gameScene::putPlant(QPoint t_cell)
{
    Plant* plant;
    switch (this->currentCard->plantIndex)
    {
    case 0:///Choose a shovel to remove plants
        for (int i = 0; i < Plants.count(); i++)
        {
            if ((Plants[i]->row == t_cell.y()) && (Plants[i]->column == t_cell.x()))
            {
                delete Plants[i];
                Plants.removeAt(i);
                this->currentCard->move(this->currentPos);
                this->currentCard = nullptr;
                return;
            }
        }
        this->currentCard = nullptr;
        return;
        break;
    case 1:///choose sunflower
        plant = new sunFlower(this);
        break;
    case 2:///choose pea shooter
        plant = new peaShooter(this);
        break;
    case 3:///choose wallnut
        plant = new wallNut(this);
        break;
    case 4:///choose potato mine
        plant = new potatoMine(this);
        break;
    case 5:///choose cherry bomb
        plant = new cherryBomb(this);
        break;
    case 6:///choose ice pea shooter
        plant = new IcePeaShooter(this);
        break;
    }
    ///plant plants in cell
    plant->setGeometry(this->rect.x() + 10 + this->cellSize.x() * t_cell.x(), this->rect.y() - 15 + this->cellSize.y() * t_cell.y(), 120, 100);
    plant->row = t_cell.y();
    plant->column = t_cell.x();
    this->Plants.append(plant);
    this->sunPoint -= this->currentCard->sunPoint;
    this->currentCard->frame = this->currentCard->frameMax;
    this->currentCard = nullptr;
}

void gameScene::putZombie(int row, int type)
{
    Zombie* zombie;
    ///choose types of zombies
    switch(type)
    {
    case 0:
        zombie = new CommonZombie(this, 0);
        break;
    case 1:
        zombie = new CommonZombie(this, 1);
        break;
    case 2:
        zombie = new CommonZombie(this, 2);
        break;
    case 3:
        zombie = new CommonZombie(this, 3);
        break;
    case 4:
        zombie = new PoleZombie(this);
        break;
    }
    zombie->row = row;
    zombie->setGeometry(950, zombie->row * 100 - 25 + rand() % 5, 340, 200);///prevent zombies overlap
    this->Zombies.append(zombie);
}

void gameScene::mouseMoveEvent(QMouseEvent* event)
{
    m = event->pos();
    if (this->currentCard != nullptr)
    {
        this->currentCard->move(m + QPoint(-40, 1));
    }
}

///Judge the position correctly, the card is not empty
void gameScene::mousePressEvent(QMouseEvent *event)
{
    QPoint m_cell = this->getCell();
    if (event->button() == Qt::LeftButton)
    {
        ///Judge the position correctly, the card is not empty
        if ((m_cell.x() > -1) && (this->currentCard != nullptr))
        {
            for (int i = 0; i < Plants.count(); i++)
            {
                ///Determine if the right plants are in place
                if ((Plants[i]->row == m_cell.y()) && (Plants[i]->column == m_cell.x()) && this->currentCard->plantIndex > 0)
                {
                    //sound->setSource(QUrl::fromLocalFile(":/PVZ_image/NotEnoughSun.wav"));
                    //sound->play();
                    return;
                }
            }
            this->currentCard->move(this->currentPos);
            this->putPlant(m_cell);
        }
    }
    else
    {
        if (this->currentCard != nullptr)
        {
            this->currentCard->move(this->currentPos);
        }
        this->currentCard = nullptr;
    }
}

///Basic configuration of the scenario
mainScene::mainScene(QWidget* parent) : gameScene(parent)
{
    this->setGeometry(-120, 0, 1400, 600);///The background of the entire game is 1400*600, but the first 120*600 is hidden
    this->cellSize = QPoint(81, 100);///A block is 81 x 100 in size
    this->rect = QRect(250, 85, 729, 500);///Lawn size 729*500
    this->setMovie(this->background);
    this->background->start();
    this->show();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(20);///20ms update once
    this->uiSetup();
}

mainScene::~mainScene()
{
    delete this->background;
}

void mainScene::uiSetup()
{
    ///Set the sunback position
    SunBack->setGeometry(120, 0, 123, 34);
    sunback->start();
    SunBack->show();
    SunBack->setMovie(sunback);
    ///Set the sunfront position
    SunFront->setGeometry(160, 0, 65, 30);
    SunFront->setFont(QFont("Calibri", 16));
    SunFront->setText("50");
    SunFront->setAlignment(Qt::AlignHCenter);
    SunFront->show();
    SunFront->raise();
    ///Set the exit position
    exit->setGeometry(950, 0, 60, 60);
    exit->setFlat(true);
    exit->setIcon(QIcon(":/PVZ_image/Leave.png"));
    exit->setIconSize(QSize(60,60));
    exit->setStyleSheet("background: transparent");
    exit->setCursor(Qt::PointingHandCursor);
    connect(exit, SIGNAL(clicked()), this, SLOT(leave()));
    exit->show();
    exit->raise();
    ///initial card
    Card *card = new sunFlowerCard(this);
    card->setIndex(0);
    Cards.append(card);
    Card *card_2 = new peaShooterCard(this);
    card_2->setIndex(1);
    Cards.append(card_2);
    Card *card_3 = new wallNutCard(this);
    card_3->setIndex(2);
    Cards.append(card_3);
    Card *card_4 = new potatoMineCard(this);
    card_4->setIndex(3);
    Cards.append(card_4);
    Card *card_5 = new cherryBombCard(this);
    card_5->setIndex(4);
    Cards.append(card_5);
    Card *card_6 = new icePeaShooterCard(this);
    card_6->setIndex(5);
    Cards.append(card_6);
    Card *shovel = new Shovel(this);
    Cards.append(shovel);
    ///play background music
    QSoundEffect* sound=new QSoundEffect(this);
    sound->setSource(QUrl::fromLocalFile(":/PVZ_image/start.wav"));
    sound->setLoopCount(QSoundEffect::Infinite);
    sound->play();
}

/**
 * test key
 * */
void mainScene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_1:
        this->putZombie(rand() % 5, 0);
        break;
    case Qt::Key_2:
        this->putZombie(rand() % 5, 1);
        break;
    case Qt::Key_3:
        this->putZombie(rand() % 5, 2);
        break;
    case Qt::Key_4:
        this->putZombie(rand() % 5, 3);
        break;
    case Qt::Key_5:
        this->putZombie(rand() % 5, 4);
        break;
    case Qt::Key_6:
        this->sunPoint += 100;
        break;
    case Qt::Key_7:
        this->threat = 6001;///A bunch of zombies
        break;
    case Qt::Key_8:
        this->threat = 9001;///stop quickly
        break;
    case Qt::Key_Escape:
        emit toTitle();
        break;
    }
}

/**
 * @brief Timer
 */
void mainScene::onTimer()
{
    this->removeDeath();
    this->act();
    this->SunFront->setText(QString::number(this->sunPoint));
    this->createZombie();
    if (rand() % 450 < 1)///Naturally falling sunlight ramdomly
    {
        sunCollect* sun = new sunFall(this);
        sunCollects.append(sun);
    }
    this->exit->raise();
    this->judge();
}

void mainScene::leave()
{
    emit toTitle();
}

/**
 * @brief set start scene
 */
StartScene::StartScene(QWidget* parent) : gameScene(parent)
{
    this->setGeometry(0, 0, 800, 600);
    this->setMovie(this->background);
    this->background->start();
    this->show();
    btn1->setMovie(startAdventure);
    startAdventure->start();
    btn1->setGeometry(403, 67, 331, 146);
    btn1->show();
}

StartScene::~StartScene()
{
    delete this->background;
    delete this->startAdventure;
    delete this->btn1;
}

/**
 * @brief Jump to the game interface after pressing the button
 */
void StartScene::mousePressEvent(QMouseEvent *event)
{
    if (QRect(403, 67, 331, 146).contains(event->pos()))
    {
        emit toStart();
    }
}

/**
 * @brief Set the play of the beginning animation
 */
StartScreen::StartScreen(QWidget* parent) : gameScene(parent)
{
    this->setGeometry(0, 0, 800, 600);
    this->setMovie(this->background);
    this->background->start();
    this->show();
    this->front->setGeometry(0, 0, 800, 600);
    this->front->show();
    this->front->setStyleSheet("background: rgba(0,0,0,1)");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    timer->start(20);
}

StartScreen::~StartScreen()
{
    delete this->background;
    delete this->front;
}

/**
 * @brief Set a grayscale change
 */
void StartScreen::onTimer()
{
    if (frame > 0)
    {
        frame --;
        if (frame > 50)
        {
            this->front->setStyleSheet("background: rgba(0,0,0," + QString::number((frame - 50) / 50.0) +")");
        }
        if (frame < 30)
        {
            this->front->setStyleSheet("background: rgba(0,0,0," + QString::number((30 - frame) / 30.0) +")");
        }
    }
    else
    {
        emit toTitle();
    }
}
