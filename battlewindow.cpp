#include "battlewindow.h"
#include "ui_battlewindow.h"
#include "endscreen.h"
#include <QtMultimedia/QMediaPlayer>

BattleWindow::BattleWindow(Character *playerCharacter, Character *selectedCharacter, MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::BattleWindow)
{    
    ui->setupUi(this);

    playerChara = playerCharacter ;
    enemyChara = selectedCharacter ;

    ui->playerNameLabel->setText(QString::fromStdString(playerCharacter->shortDescription()));
    ui->enemyName->setText(QString::fromStdString(enemyChara->shortDescription()));
    setUp() ;
    refreshDisplay() ;
    parentWindow = parent ;
    parent->setEnabled(false);
    this->setEnabled(true);

}

BattleWindow::~BattleWindow()
{
    delete ui;
}

void BattleWindow::setUp() {
    Item *playerWeapon = playerChara->getEquipedWeapon() ;
    Item *enemyWeapon = enemyChara->getEquipedWeapon() ;

    if(playerWeapon != NULL) {
         playerAttack = playerChara->getAttackStrength() + playerWeapon->getAttackDamVal() ;
    } else {
         playerAttack = playerChara->getAttackStrength() ;
    }
    if(enemyWeapon != NULL) {
         enemyAttack = playerChara->getAttackStrength() + enemyWeapon->getAttackDamVal() ;
    } else {
         enemyAttack = enemyChara->getAttackStrength() ;
    }

    QGraphicsScene *playerScene =  new QGraphicsScene;
    QPixmap playerPixmap(QString::fromStdString(playerChara->shortDescription()));
        playerScene->addPixmap(playerPixmap);
        ui->playerGraphicsView->setScene(playerScene);
        ui->playerGraphicsView->show();

    QGraphicsScene *enemyScene =  new QGraphicsScene;
    QPixmap enemyPixmap(QString::fromStdString(enemyChara->shortDescription()));
        enemyScene->addPixmap(enemyPixmap);
        ui->enemyGraphicsView->setScene(enemyScene);
        ui->enemyGraphicsView->show();
}

void BattleWindow::updateMainWindow() {
    parentWindow->setEnabled(true);
    parentWindow->displayCharactersInRoom();
    parentWindow->displayItemsInRoom();
    parentWindow->displayPlayerHP();
    parentWindow->disableActionButs();
}

void BattleWindow::checkHealth() {

    if(enemyChara->getHealthPoints() <= 0) {

            updateMainWindow() ;
            this->close();

    } else if(playerChara->getHealthPoints() <= 0) {

            parentWindow->displayPlayerHP();
            EndScreen *newWindow = new EndScreen(this);
            newWindow->show();
    }
}

void BattleWindow::refreshDisplay() {

    displayHP() ;
    displayAttack() ;
    displayAccuracy() ;
    displayEquipedWeapons() ;
}

void BattleWindow::resetPlayerValues() {
    playerAcc = 90 ;

    if(playerChara->getEquipedWeapon() != NULL) {
        playerAttack = playerChara->getAttackStrength() + playerChara->getEquipedWeapon()->getAttackDamVal() ;
    } else {
        playerAttack = playerChara->getAttackStrength() ;
    }
}

void BattleWindow::displayEquipedWeapons() {
    Item *playerWeapon = playerChara->getEquipedWeapon() ;
    Item *enemyWeapon = enemyChara->getEquipedWeapon() ;

    if(playerWeapon != NULL) {
        ui->playerWeaponLabel->setText(QString::fromStdString(playerWeapon->getShortDescription()));
    } else {
        ui->playerWeaponLabel->setText("None") ;
    }
    if(enemyWeapon != NULL) {
        ui->enemyWeaponLabel->setText(QString::fromStdString(enemyWeapon->getShortDescription()));
    } else {
        ui->enemyWeaponLabel->setText("None") ;
    }
}

void BattleWindow::displayAttack() {
    ui->playerAttLcdNum->display(playerAttack);
    ui->enemyAttLcdNum->display(enemyAttack);

}

void BattleWindow::displayAccuracy() {
     ui->enemyAccBar->setValue(enemyAcc);
     ui->playerAccuracyBar->setValue(playerAcc);
}

void BattleWindow::displayHP() {
    ui->enemyLcdNumber->display(enemyChara->getHealthPoints());
    ui->playerHpLcdNumber->display(playerChara->getHealthPoints());
}

void BattleWindow::battlePlayerTurn() {

    int randNumber = rand() % 100 + 1, enemyAccuracy = enemyAcc, playerAccuracy = playerAcc ;
        bool isArms = ui->armsRadioBut->isChecked(), isLegs = ui->legsRadioBut->isChecked() ;

        if(randNumber <= playerAccuracy) {
            int enemyHp = enemyChara->getHealthPoints() ;
            enemyHp = enemyHp - playerAttack ;
            if(enemyHp < 0) {
                enemyHp = 0 ;
            }
            enemyChara->setHealthPoints(enemyHp);
            ui->hitMissLabel->setText("HIT!!!");

        if(isArms == true) {
            randNumber = rand() %100 + 1 ;
            if(randNumber <= (playerAccuracy)) {
                enemyAccuracy = enemyAccuracy - 5 ;
                if(enemyAccuracy < 0) {
                enemyAccuracy = 0 ;
                }
                enemyChara->setEquipedWeapon(NULL);
                enemyAcc = enemyAccuracy ;
                enemyAttack = enemyChara->getAttackStrength() ;
            }
        } else if(isLegs == true) {
            randNumber = rand() %100 + 1 ;

            if(randNumber <= (playerAccuracy / 1.1)) {
                ui->runAwayBut->setEnabled(true);
            }
        }
        } else {
            ui->hitMissLabel->setText("MISS!!!");
        }

        checkHealth();
}

void BattleWindow::battleEnemyTurn() {

    int randNumber = rand() % 100 + 1, enemyAccuracy = enemyAcc ;

    if(randNumber <= enemyAccuracy) {
        int playerHp = playerChara->getHealthPoints() ;
        playerHp = playerHp - enemyAttack ;
        if(playerHp < 0) {
            playerHp = 0 ;
        }
        playerChara->setHealthPoints(playerHp);

    }
    checkHealth();
}

void BattleWindow::playWeaponSound(QString soundName) {

    QMediaPlayer *player = new QMediaPlayer(this);

        player->setMedia(QUrl::fromLocalFile(soundName + ".wav"));
        player->setVolume(Volume);
        player->play();
}

void BattleWindow::on_attackBut_clicked()
{     
    playWeaponSound(ui->playerWeaponLabel->text()) ;
    battlePlayerTurn() ;
    if(enemyChara->getHealthPoints() > 0) {
            battleEnemyTurn() ;
    }
    refreshDisplay() ;

    QMediaPlayer *player = new QMediaPlayer(this);
        if(ui->playerWeaponLabel->text()=="Machine Gun"){
        player->setMedia(QUrl::fromLocalFile("machine-gun-01.wav"));
        }else if(ui->playerWeaponLabel->text()=="Handgun"){
        player->setMedia(QUrl::fromLocalFile("gun-gunshot-02.wav"));
        }else if(ui->playerWeaponLabel->text()=="Baseball Bat"){
        player->setMedia(QUrl::fromLocalFile("Baseball Bat"));
        }else if(ui->playerWeaponLabel->text()=="Knife"){
        player->setMedia(QUrl::fromLocalFile("Knife"));
        }
        player->setVolume(Volume);
        player->play();
}

void BattleWindow::on_runAwayBut_clicked()
{
    updateMainWindow() ;
    this->close();
}

void BattleWindow::on_headRadioBut_toggled(bool checked)
{
    if(checked == true) {
        ui->attackBut->setEnabled(true);

        playerAcc = playerAcc / 2 ;
        playerAttack = playerAttack * 2 ;
        refreshDisplay() ;
    } else {
        resetPlayerValues() ;
        refreshDisplay() ;
    }
}

void BattleWindow::on_torsoRadioBut_toggled(bool checked)
{
    if(checked == true) {
        ui->attackBut->setEnabled(true);

        playerAcc = playerAcc + 5 ;
        if(playerAcc > 100) {
            playerAcc = 100 ;
        }
        refreshDisplay() ;
    } else {
        resetPlayerValues() ;
        refreshDisplay() ;
    }

}

void BattleWindow::on_armsRadioBut_toggled(bool checked)
{
    if(checked == true) {
        ui->attackBut->setEnabled(true);

        playerAcc = playerAcc / 1.2 ;
        playerAttack = playerAttack / 1.2  ;
        refreshDisplay() ;
    } else {
        resetPlayerValues() ;
        refreshDisplay() ;
    }
}

void BattleWindow::on_legsRadioBut_toggled(bool checked)
{
    if(checked == true) {
        ui->attackBut->setEnabled(true);

        playerAcc = playerAcc / 1.2 ;
        playerAttack = playerAttack / 1.2 ;
        refreshDisplay() ;
    } else {
        resetPlayerValues();
        refreshDisplay() ;
    }
}
