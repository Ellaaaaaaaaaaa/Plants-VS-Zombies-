#include "object.h"

Object::Object(QWidget *parent)
    : QLabel{parent}
{
    this->setMouseTracking(1);
    this->scene=(gameScene*)this->parent();
}
