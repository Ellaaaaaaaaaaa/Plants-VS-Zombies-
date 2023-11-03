#ifndef OBJECT_H
#define OBJECT_H

#include <QWidget>
#include <QLabel>
#include <QMovie>
#include <QMouseEvent>

class gameScene;
class Object : public QLabel
{
    Q_OBJECT
public:
    explicit Object(QWidget *parent = nullptr);
    bool life=1;
    int strength=1;
    virtual void act()=0;
    gameScene*scene;
signals:
};

#endif // OBJECT_H
