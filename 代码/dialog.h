#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include "gamescene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT
public:
    Dialog(QWidget *parent = nullptr);
    gameScene* scene;
    ~Dialog();
private:
    Ui::Dialog *ui;
public slots:
    void startGame();
    void back();

};
#endif // DIALOG_H
