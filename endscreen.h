#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include <QDialog>
#include "battlewindow.h"
#include "mainwindow.h"

namespace Ui {
class EndScreen;
}

class EndScreen : public QDialog
{
    Q_OBJECT

public:
    explicit EndScreen(BattleWindow *parent = 0, MainWindow *mainParent = 0);
    ~EndScreen();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EndScreen *ui;
};

#endif // ENDSCREEN_H
