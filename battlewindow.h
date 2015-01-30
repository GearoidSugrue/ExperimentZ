#ifndef BATTLEWINDOW_H
#define BATTLEWINDOW_H

#include <QDialog>
#include "character.h"
#include "item.h"
//#include "endscreen.h"
#include "mainwindow.h"




namespace Ui {
class BattleWindow;
}

class BattleWindow : public QDialog
{
    Q_OBJECT

public:
    explicit BattleWindow(Character* playerCharacter, Character* selectedCharacter, MainWindow *parent = 0);
    ~BattleWindow();

private slots:
    void on_attackBut_clicked();

    void on_runAwayBut_clicked();

    void on_headRadioBut_toggled(bool checked);

    void on_torsoRadioBut_toggled(bool checked);

    void on_armsRadioBut_toggled(bool checked);

    void on_legsRadioBut_toggled(bool checked);

private:
    Ui::BattleWindow *ui;

    MainWindow *parentWindow ;

    Character *playerChara, *enemyChara ;
    int playerAcc = 90, enemyAcc = 75, playerAttack, enemyAttack;

    void playWeaponSound(QString soundName) ;
    void battleEnemyTurn() ;
    void battlePlayerTurn() ;
    void updateMainWindow() ;
    void checkHealth() ;
    void displayEquipedWeapons() ;
    void setUp() ;
    void resetPlayerValues() ;
    void refreshDisplay() ;
    void displayHP() ;
    void displayAttack() ;
    void displayAccuracy() ;
    int Volume = 50;

};

#endif // BATTLEWINDOW_H
