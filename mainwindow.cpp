#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGLWidget>
#include <iostream>
#include <string>
#include <QtMultimedia/QMediaPlayer>
#include "qtevent.h"
#include "battlewindow.h"
#include "endscreen.h"
#include "winscreen.h"

#include <fstream>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();
    setUp currentSetUp = setUp() ;

    ui->interactButton->setEnabled(false);
    ui->countdownLcdNumber->setVisible(false);
    ui->countdownLabel->setVisible(false);

     currentRoom = currentSetUp.getCurrentRoom() ;//Gets the room that you start in.
     playerCharacter = new Character("Rick James", 1, 10, 100);

     ui->horizontalSlider->setValue(Volume);
     ui->textEdit->append(QString::fromStdString(currentRoom->longDescription()));

     showRoomGraphics() ;
     playRoomMusic() ;
     displayPlayerHP() ;
     displayPlayerAttack();
     displayPlayerItems() ;
     displayItemsInRoom() ;
     displayCharactersInRoom() ;
     setDirectionButtons() ;
     displayTextFromFile(currentRoom->shortDescription()) ;

}

MainWindow::~MainWindow()
{
    delete ui;
}

Character* MainWindow::getPlayer() {

    return playerCharacter ;
}

Room* MainWindow::getCurrentRoom() {
    return currentRoom ;
}

void MainWindow::displayPlayerHP() {
    QLCDNumber *lcd = ui->playerHPLcdNumber;
    lcd->display(playerCharacter->getHealthPoints());
}

void MainWindow::displayPlayerAttack() {
    QLCDNumber *lcd = ui->attackLcdNumber;
    Item *weaponEquiped = playerCharacter->getEquipedWeapon() ;

    if(weaponEquiped != NULL) {
        lcd->display(playerCharacter->getAttackStrength() + weaponEquiped->getAttackDamVal());
    } else {
        lcd->display(playerCharacter->getAttackStrength());
    }
}

string MainWindow::goRoom(string direction) {

    Room* nextRoom = currentRoom->nextRoom(direction);

    string nextRoomName = nextRoom->shortDescription() ;

    if(currentRoom->isEnemysInRoom() == false || previousRoom == nextRoom) {
        if (nextRoom == NULL){
            ui->textEdit->append(QString::fromStdString("Can't go that way! \n"));
            return "null";
        }
        previousRoom = currentRoom ;
        currentRoom = nextRoom;

        if(nextRoomName == "Cold Room" || nextRoomName == "Storage Room" || nextRoomName == "Laser Room"){
             QTEvent *event = new QTEvent(this,playerCharacter );
             event->show();
        } else if(nextRoomName == "Armoury" && number == 90) {

                ui->countdownLcdNumber->setVisible(true);
                ui->countdownLabel->setVisible(true);
                timer = new QTimer(this);
                QObject::connect(timer ,  SIGNAL(timeout ()),this,SLOT(setNumber()));
                timer->start(1000);
                ui->countdownLcdNumber->display(number--);
        } else if(nextRoomName == "Exit") {
            playerCharacter->setHealthPoints(0);
            checkHealth();
        }

         ui->textEdit->append(QString::fromStdString(currentRoom->longDescription()));
         ui->interactButton->setEnabled(false);

         setInteractiveObjects() ;
         playRoomMusic() ;
         showRoomGraphics() ;
         displayItemsInRoom() ;
         displayCharactersInRoom() ;
         displayPlayerHP() ;
         disableActionButs();
         displayTextFromFile(currentRoom->shortDescription()) ;

         return "successfull";

    } else {
        return "null" ;
    }
}

void MainWindow::playRoomMusic() {

    QMediaPlayer *player = new QMediaPlayer(this);
    QString roomName = QString::fromStdString(currentRoom->shortDescription());
    player->setMedia(QUrl::fromLocalFile(roomName + ".wav"));
    if(roomName == "Cold Room" || roomName == "Storage Room"){
    player->setVolume(100);
    }else{
     player->setVolume(Volume);
    }
    player->play();
}

void MainWindow::showRoomGraphics() {

    QGraphicsScene *scene =  new QGraphicsScene;
    QString roomName = QString::fromStdString(currentRoom->shortDescription());
    QPixmap pixmap(roomName + ".jpg" );
        scene->addPixmap(pixmap);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->fitInView(scene->itemsBoundingRect() ,Qt::KeepAspectRatio);
        ui->graphicsView->show();
}

void MainWindow::setInteractiveObjects() {

    QTreeWidget *tree = ui->interactiveObjectsTreeWidget;//Gets the tree view
    if(currentRoom->shortDescription()=="Control Room"){

        tree->clear();
        QTreeWidgetItem *Detonator = new QTreeWidgetItem() ;
        QTreeWidgetItem *Key = new QTreeWidgetItem() ;

        Detonator->setText(0, QString::fromStdString("Countdown Controller"));
        Key->setText(0, QString::fromStdString("Key"));
        tree->addTopLevelItem(Key);
        tree->addTopLevelItem(Detonator);
     }else if(currentRoom->shortDescription()=="East Wing Middle"){
        QTreeWidgetItem *Door = new QTreeWidgetItem();
        Door->setText(0, QString::fromStdString("West Door"));
        tree->addTopLevelItem(Door);
     } else if(currentRoom->shortDescription()=="Restroom"){
                        QTreeWidgetItem *Body = new QTreeWidgetItem();
                        Body->setText(0, QString::fromStdString("Body"));
                        tree->addTopLevelItem(Body);
    }else if(currentRoom->shortDescription() == "Reactor Room"){
        QTreeWidgetItem *controlPanel = new QTreeWidgetItem();
        controlPanel->setText(0, QString::fromStdString("Control Panel"));
        tree->addTopLevelItem(controlPanel);

    } else {
            tree->clear();
    }

}

void MainWindow::displayItemsInRoom(){

    vector<Item> listOfItems = currentRoom->getItemsInRoom() ;
    QTreeWidget *tree = ui->itemsInRoomTreeWidget; //Gets the tree view
    tree->clear(); //Clears whatever is in the view already

    for(int i=0; i < listOfItems.size(); i++) {
        QTreeWidgetItem *itemTreeElement = new QTreeWidgetItem() ;

        Item itemObj = listOfItems[i] ;
        itemTreeElement->setText(0, QString::fromStdString(itemObj.getShortDescription()));
        itemTreeElement->setText(1, QString::number(itemObj.getWeight()) + "");
        tree->addTopLevelItem(itemTreeElement);
    }

    tree->expandAll();
}

void MainWindow::displayCharactersInRoom(){

    QTreeWidget *tree = ui->charaInRoomTreeWidget; //Gets the tree view
        tree->clear(); //Clears whatever is in the view already
        int i = 0 ;

        while(i < currentRoom->getCharactersInRoom().size()) {
            vector<Character> listOfCharacters = currentRoom->getCharactersInRoom() ;

            QTreeWidgetItem *charaTreeElement = new QTreeWidgetItem() ;

            Character *charaObj = &listOfCharacters[i] ;
            if(charaObj->getHealthPoints() > 0) {
                 charaTreeElement->setText(0, QString::fromStdString(charaObj->shortDescription()));
                 charaTreeElement->setText(1, QString::number(charaObj->getHealthPoints()) + "");
                 if(charaObj->getEquipedWeapon() != NULL) {
                        charaTreeElement->setText(2, QString::fromStdString(charaObj->getEquipedWeapon()->getShortDescription()));
                 }
                 tree->addTopLevelItem(charaTreeElement);
                 i++ ;
            } else {
                addCharaItemsToRoom(charaObj) ;
                currentRoom->removeCharacter(i);
            }
        }
        tree->expandAll();
}


void MainWindow::displayPlayerItems() {

    vector<Item> listOfItems = playerCharacter->getItemsInCharacter() ;
    QTreeWidget *tree = ui->playerItemsTreeWidget; //Gets the tree view
    tree->clear(); //Clears whatever is in the view already
    for(int i=0; i < listOfItems.size(); i++) {
        QTreeWidgetItem *itemTreeElement = new QTreeWidgetItem() ;

        Item itemObj = listOfItems[i] ;
        itemTreeElement->setText(0, QString::fromStdString(itemObj.getShortDescription()));
        itemTreeElement->setText(1, QString::number(itemObj.getWeight()) + "");
        itemTreeElement->setText(2, QString::number(itemObj.getAttackDamVal()) + "");
        itemTreeElement->setText(3, QString::number(itemObj.getHP_RestoreVal()) + "");
        tree->addTopLevelItem(itemTreeElement);
    }

    tree->expandAll();
}

void MainWindow::addCharaItemsToRoom(Character *chara) {

    vector<Item> charaItems = chara->getItemsInCharacter() ;

    for(int i = 0; i < charaItems.size(); i++) {
        currentRoom->addItem(&charaItems[i]);
    }
}

void MainWindow::on_goNorthButton_clicked()
{
    if(goRoom("north")!="null"){
        ui->widget_2->setCount(ui->widget_2->getCount() +1);
        ui->widget_2->update();
    } else {
        ui->textEdit->append("Enemies are blocking your path!!!\nDefeat them or turn back.\n");
    }
     setDirectionButtons() ;
}

void MainWindow::on_goWestButton_clicked()
{
    if(goRoom("west")!="null"){
        ui->widget_2->setCount1(ui->widget_2->getCount1() -1);
        ui->widget_2->update();
    } else {
        ui->textEdit->append("Enemies are blocking your path!!!\nDefeat them or turn back.\n");
    }
    setDirectionButtons() ;
}

void MainWindow::on_goSouthButton_clicked()
{
    if(goRoom("south")!="null"){
         ui->widget_2->setCount(ui->widget_2->getCount() -1);
         ui->widget_2->update();
    } else {
        ui->textEdit->append("Enemies are blocking your path!!!\nDefeat them or turn back.\n");
    }
    setDirectionButtons() ;
}

void MainWindow::on_goEastButton_clicked()
{
    if(goRoom("east")!="null"){
        ui->widget_2->setCount1(ui->widget_2->getCount1() +1);
        ui->widget_2->update();
    } else {
        ui->textEdit->append("Enemies are blocking your path!!!\nDefeat them or turn back.\n");
    }
    setDirectionButtons() ;
}

void MainWindow::on_goUpButton_clicked()
{
    goRoom("up") ;
    setDirectionButtons() ;
}

void MainWindow::on_goDownButton_clicked()
{
    goRoom("down") ;
    setDirectionButtons() ;
}

void MainWindow::on_itemsInRoomTreeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
        vector<Item> listOfItems = playerCharacter->getItemsInCharacter();

        int weight = 0;
        QString itemQText = item->text(0) ;
        int position = ui->itemsInRoomTreeWidget->indexOfTopLevelItem(item) ;
        Item *selectedItem = currentRoom->getItemAtPos(position) ;

        for(int i=0; i < listOfItems.size(); i++) {
            Item tempItem = listOfItems.at(i);
            weight += tempItem.getWeight();
        }
        if((weight + selectedItem->getWeight()) <= 20){
            playerCharacter->addItem(selectedItem);
            ui->textEdit->append(itemQText + " removed from room and added to inventory.\n");

            currentRoom->removeItemFromRoom(position);
            displayItemsInRoom() ;
            displayPlayerItems() ;
        }else{
            ui->textEdit->append("You are carrying too much! Better drop or use some items to make room!") ;
        }
}

void MainWindow::on_charaInRoomTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    vector< Character>  charactersInRoom = currentRoom->getCharactersInRoom() ;
    int indexOfChara = ui->charaInRoomTreeWidget->indexOfTopLevelItem(item) ;

    Character charaObj = charactersInRoom[indexOfChara] ;

    if(charaObj.getEnemyCheck() == 0) {
        ui->attackButton->setEnabled(1);
        ui->talkButton->setEnabled(1);
    } else {
        ui->attackButton->setEnabled(0);
        ui->talkButton->setEnabled(1);
    }
}

void MainWindow::on_interactiveObjectsTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->interactButton->setEnabled(true);
    disableActionButs() ;
}
void MainWindow::on_playerItemsTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    int indexOfItem= ui->playerItemsTreeWidget->indexOfTopLevelItem(item) ;
    Item *selectedItem = playerCharacter->getItemAtPos(indexOfItem) ;
    ui->widget_2->setVisible(false);
    if(selectedItem->getShortDescription()== "Machine Gun"){
        ui->widget->setImageCounter(0);
        ui->widget->updateGL();
    }else if(selectedItem->getShortDescription()== "Knife"){
        ui->widget->setImageCounter(1);
        ui->widget->updateGL();
    }else if(selectedItem->getShortDescription()== "Beer"){
        ui->widget->setImageCounter(2);
        ui->widget->updateGL();
     }else{
        ui->widget_2->setVisible(true);
    }
    if(selectedItem->getWeaponCheck() == 0) {
        ui->equipButton->setEnabled(1);
        ui->readButton->setEnabled(0);
        ui->eatButton->setEnabled(0);

        if(selectedItem == playerCharacter->getEquipedWeapon()) {
          ui->removeButton->setEnabled(0);
        } else {
          ui->removeButton->setEnabled(1);
        }
    } else if(selectedItem->getEdibleCheck() == 0) {
        ui->equipButton->setEnabled(0);
        ui->eatButton->setEnabled(1);
        ui->readButton->setEnabled(0);
        ui->removeButton->setEnabled(1);
    } else {
        ui->equipButton->setEnabled(0);
        ui->eatButton->setEnabled(0);
        ui->readButton->setEnabled(1);
        ui->removeButton->setEnabled(1);
    }
}

void MainWindow::setDirectionButtons() {

    if(currentRoom->nextRoom("north") != NULL) {
        ui->goNorthButton->setEnabled(1);
    } else {
        ui->goNorthButton->setEnabled(0);
    }
    if(currentRoom->nextRoom("south") != NULL) {
        ui->goSouthButton->setEnabled(1);
    } else {
        ui->goSouthButton->setEnabled(0);
    }
    if(currentRoom->nextRoom("east") != NULL) {
        ui->goEastButton->setEnabled(1);
    } else {
        ui->goEastButton->setEnabled(0);
    }
    if(currentRoom->nextRoom("west") != NULL) {
        ui->goWestButton->setEnabled(1);
    } else {
        ui->goWestButton->setEnabled(0);
    }
    if(currentRoom->nextRoom("up") != NULL) {
        ui->goUpButton->setEnabled(1);
    } else {
        ui->goUpButton->setEnabled(0);
    }
    if(currentRoom->nextRoom("down") != NULL) {
        ui->goDownButton->setEnabled(1);
    } else {
        ui->goDownButton->setEnabled(0);
    }
    if(currentRoom->shortDescription()=="East Wing Middle"){
        ui->goWestButton->setEnabled(0);
    }
}


void MainWindow::on_attackButton_clicked()
{
    QTreeWidgetItem *character = ui->charaInRoomTreeWidget->currentItem() ;
    int indexOfChara= ui->charaInRoomTreeWidget->indexOfTopLevelItem(character) ;
    Character *selectedCharacter = currentRoom->getCharacterAtPos(indexOfChara) ;

    BattleWindow dialog(playerCharacter, selectedCharacter,this);
    dialog.exec();
}

void MainWindow::on_talkButton_clicked()
{
    QTreeWidgetItem *character = ui->charaInRoomTreeWidget->currentItem() ;

         int indexOfChara= ui->charaInRoomTreeWidget->indexOfTopLevelItem(character), charaHP = 0 ;
         Character *selectedCharacter = currentRoom->getCharacterAtPos(indexOfChara) ;

         string filename = selectedCharacter->shortDescription() ;

         if(selectedCharacter->getEnemyCheck() == 0) {
            charaHP = playerCharacter->getHealthPoints() ;
            charaHP = charaHP - 10 ;
             playerCharacter->setHealthPoints(charaHP);
             checkHealth() ;
             displayTextFromFile("Talk To Enemy");
         } else {

            displayTextFromFile(filename) ;
         }
         displayPlayerHP() ;
}

void MainWindow::on_equipButton_clicked()
{    
    playMusic("Equip Item Sound.wav") ;

    QTreeWidgetItem *item = ui->playerItemsTreeWidget->currentItem() ;

    int indexOfItem= ui->playerItemsTreeWidget->indexOfTopLevelItem(item) ;
    Item *selectedItem = playerCharacter->getItemAtPos(indexOfItem) ;

    Item *weaponEquiped = playerCharacter->getEquipedWeapon() ;

    if(weaponEquiped != selectedItem) {
        playerCharacter->setEquipedWeapon(selectedItem) ;

        ui->eatButton->setEnabled(0);
        ui->removeButton->setEnabled(0);
        ui->eqWeaponLabel->setText(QString::fromStdString(selectedItem->getShortDescription()));
    } else {
        playerCharacter->setEquipedWeapon(NULL) ;
        ui->eqWeaponLabel->setText(QString::fromStdString("No Weapon Equiped"));
        ui->removeButton->setEnabled(1);
    }
    displayPlayerAttack();
}

void MainWindow::on_eatButton_clicked()
{    
    QTreeWidgetItem *item = ui->playerItemsTreeWidget->currentItem() ;

    int indexOfItem= ui->playerItemsTreeWidget->indexOfTopLevelItem(item) ;
    Item *selectedItem = playerCharacter->getItemAtPos(indexOfItem) ;

    playMusic(QString::fromStdString(selectedItem->getShortDescription()) + ".wav");
    ui->textEdit->append("You feel much better after restoring your health with " + QString::fromStdString(selectedItem->getShortDescription()) + "\n") ;

    playerCharacter->restoreHealth(selectedItem->getHP_RestoreVal());

    playerCharacter->removeItemFromCharacter(indexOfItem);

    displayPlayerHP() ;
    displayPlayerItems() ;
    disableInventoryButs() ;
}

void MainWindow::on_readButton_clicked()
{
    playMusic(QString::fromStdString("page-flip-1.wav")) ;

    QTreeWidgetItem *item = ui->playerItemsTreeWidget->currentItem() ;

    int indexOfItem= ui->playerItemsTreeWidget->indexOfTopLevelItem(item) ;
    Item *selectedItem = playerCharacter->getItemAtPos(indexOfItem) ;

    string filename = selectedItem->getShortDescription() ;

    ui->textEdit->append(QString::fromStdString(filename + " reads:\n"));
    displayTextFromFile(filename) ;
}

void MainWindow::on_removeButton_clicked()
{
    playMusic(QString::fromStdString("Drop Item Sound.wav")) ;

    QTreeWidgetItem *item = ui->playerItemsTreeWidget->currentItem() ;

    int indexOfItem= ui->playerItemsTreeWidget->indexOfTopLevelItem(item) ;
    Item *selectedItem = playerCharacter->getItemAtPos(indexOfItem) ;

    currentRoom->addItem(selectedItem);
    playerCharacter->removeItemFromCharacter(indexOfItem);

    ui->textEdit->append(QString::fromStdString(selectedItem->getShortDescription()) + " removed from inventory and added to room.\n");

    displayPlayerItems() ;
    displayItemsInRoom() ;
    disableInventoryButs() ;
}

void MainWindow::playMusic(QString soundName) {

    QMediaPlayer *player = new QMediaPlayer(this);
    player->setMedia(QUrl::fromLocalFile(soundName));
    player->setVolume(Volume);
    player->play();
}

void MainWindow::disableInventoryButs() {
    ui->equipButton->setEnabled(0);
    ui->eatButton->setEnabled(0);
    ui->readButton->setEnabled(0);
    ui->removeButton->setEnabled(0);
}

void MainWindow::disableActionButs() {
    ui->attackButton->setEnabled(0) ;
    ui->talkButton->setEnabled(0) ;
}

void MainWindow::displayTextFromFile(string filename) {

    QString name = QString::fromStdString(":/textFiles/" + filename);

    QTextEdit *textEdit = ui->textEdit ;

    QFile file(name);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {

    } else {
         QTextStream stream (&file);

         while (!stream.atEnd()) {
             QString line = stream.readLine();
             textEdit->append(line);
         }
    }
}

void MainWindow::checkHealth() {

    if(playerCharacter->getHealthPoints() <= 0) {
        EndScreen *newWindow = new EndScreen(0, this);
        newWindow->show();
    }
}

void MainWindow::on_mapButton_clicked()
{
    ui->widget_2->setVisible(true);
}

int MainWindow::getVolume()
{
    return Volume;
}

void MainWindow::setVolume(int volume)
{
    Volume = volume;
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    if(ui->checkBox->isChecked() == false)
        Volume = position;
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    if(checked)
        setVolume(0);
    else {
        Volume = 50;
    }
}

void MainWindow::setNumber()
{
      if(number < 0)
      {
            playerCharacter->setHealthPoints(0);
            timer->stop();
            checkHealth();
      }
      else
      {
          ui->countdownLcdNumber->display(number--);
      }

      if(number <= 10 && (number % 2 == 0)) {
          playMusic(QString::fromStdString("Armoury.wav")) ;
      }
}

void MainWindow::on_interactButton_clicked()
{
    QTreeWidgetItem *interactiveObj = ui->interactiveObjectsTreeWidget->currentItem();

    QString text = interactiveObj->text(0) ;

    if(text == "Countdown Controller"){
       timer->stop();
        ui->textEdit->append("You rush over to the control panel and start smashing buttons until the countdown stops. Looks like you made it just in time!\n") ;
    }else if(text == "Key"){
       keyCount = 1;
       ui->textEdit->append("You find a key, could this be for the door you found earlier!?") ;
    } else if(text == "Body"){
       ui->textEdit->append("'Bullet wounds? Curious...Looks like he was alive until awhile ago!'\nWho could have done this!?") ;

    }else if(text == "Control Panel"){
        if(currentRoom->getCharactersInRoom().size() > 0) {
            ui->textEdit->append("There are enemies blocking the way to the Control Panel!!!") ;
        } else {
            WinScreen *newWindow = new WinScreen(this);
            newWindow->show();
        }
    } else if(text == "West Door") {

        if(keyCount >= 1){
            if(goRoom("west")!= "null" ){

                ui->widget_2->setCount1(ui->widget_2->getCount1() -1);
                playMusic(QString::fromStdString("BIGDOOR.wav")) ;

                ui->widget_2->update();
                setDirectionButtons() ;
            }

            ui->textEdit->append("Door is now unlocked!\n") ;

        }else{
            ui->textEdit->append("Door is locked. Maybe there's a key for it somewhere?\n") ;
        }
    }

}


