#ifndef WINSCREEN_H
#define WINSCREEN_H

#include <QDialog>
#include "mainwindow.h"


namespace Ui {
class WinScreen;
}

class WinScreen : public QDialog
{
    Q_OBJECT

public:
    explicit WinScreen(MainWindow *parent = 0);
    ~WinScreen();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WinScreen *ui;
};

#endif // WINSCREEN_H
