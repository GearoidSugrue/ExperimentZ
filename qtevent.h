#ifndef QTEVENT_H
#define QTEVENT_H

#include <QDialog>
#include <QLCDNumber>
#include <QTimer>
#include "character.h"
#include "mainwindow.h"

namespace Ui {
class QTEvent;
}

class QTEvent : public QDialog
{
    Q_OBJECT

public:
    explicit QTEvent(MainWindow *parent = 0, Character* myCharacter = NULL);
    ~QTEvent();
    QTimer *timer;
    int number = 4;
    Character *myChar;
    MainWindow *parentWindow;
    int counter = 0;
private slots:
    void on_pushButton_clicked();
    void setNumber();

private:
    Ui::QTEvent *ui;
    int progress = 0;
    Character *playerChara ;

};

#endif // QTEVENT_H
