#include "qtevent.h"
#include "ui_qtevent.h"


QTEvent::QTEvent (MainWindow *parent, Character *myCharacter) :
    QDialog(parent),
    ui(new Ui::QTEvent)
{
    parentWindow = parent;
    ui->setupUi(this);
    parentWindow->setEnabled(false);
    this->setEnabled(true);



    string roomName = parentWindow->getCurrentRoom()->shortDescription() ;
    playerChara = myCharacter ;

    timer = new QTimer(this);

    QObject::connect(timer ,  SIGNAL(timeout ()),this,SLOT(setNumber()));
    //ui->lcdNumber->setDigitCount(2);
    timer->start(1000);

    ui->lcdNumber->display(number--);
    myChar = myCharacter;

    ui->progressBar->setValue(0);

    QGraphicsScene *scene =  new QGraphicsScene;

    if(roomName == "Laser Room") {

        QPixmap pixmap("Laser Room.jpg" );
        scene->addPixmap(pixmap);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->show();
        ui->lcdNumber->display(number--);
        ui->pushButton->setText("Dodge!");
    } else {
        QPixmap pixmap("ZorkImage.jpg" );
        scene->addPixmap(pixmap);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->show();
    }
}


QTEvent::~QTEvent()
{
    delete ui;
}

void QTEvent::on_pushButton_clicked()
{
    progress += 7;
    ui->progressBar->setValue(progress);

    if(progress >= 100){
        parentWindow->setEnabled(true);
        this->close();        
        timer->stop();
    }
}


void QTEvent::setNumber()
{
     if(counter == 0){
            if(number < 0)
            {
                 myChar->setHealthPoints(0.5*(playerChara->getHealthPoints()));
                 parentWindow->displayPlayerHP();
                 parentWindow->setEnabled(true);

                 this->close();
                 counter++;

             }  else {
                 ui->lcdNumber->display(number--);
             }
     }
}
