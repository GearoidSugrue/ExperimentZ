#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>

#include <iostream>
#include <string>

#include "room.h"
#include "setup.h"
#include "item.h"
#include "character.h"

#include <QLCDNumber>
#include <QTimer>
#include <vector>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int getVolume();    
    QTimer *timer;
    int number = 90;
    int keyCount = 0;

    Room* getCurrentRoom() ;

    void setVolume(int);
    void disableActionButs() ;
    void addCharaItemsToRoom(Character *chara) ;
    void displayPlayerHP() ;
    Character* getPlayer() ;
    void displayItemsInRoom() ;
    void displayCharactersInRoom() ;
    Character *playerCharacter ;

public slots:


    
private slots:

    void setNumber();

    void on_goNorthButton_clicked();

    void on_goWestButton_clicked();

    void on_goSouthButton_clicked();

    void on_goEastButton_clicked();

    void on_goUpButton_clicked();

    void on_goDownButton_clicked();

    void on_itemsInRoomTreeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_charaInRoomTreeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_interactiveObjectsTreeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_attackButton_clicked();

    void on_talkButton_clicked();

    void on_playerItemsTreeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_equipButton_clicked();

    void on_eatButton_clicked();

    void on_readButton_clicked();

    void on_removeButton_clicked();

    void on_mapButton_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_checkBox_toggled(bool checked);

    void on_interactButton_clicked();


private:
    Ui::MainWindow *ui;

     Room *currentRoom;
     Room *previousRoom ;
     int Volume = 50;

     void displayPlayerAttack() ;
     void displayPlayerItems() ;
     void disableInventoryButs() ;
     void setDirectionButtons() ;
     string goRoom(string direction) ;
     void playRoomMusic() ;
     void showRoomGraphics() ;
     void setInteractiveObjects() ;
     void playMusic(QString soundName) ;
     void displayTextFromFile(string filename) ;
     void checkHealth() ;


};

#endif // MAINWINDOW_H
