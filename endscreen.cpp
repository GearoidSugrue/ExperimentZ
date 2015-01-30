#include "endscreen.h"
#include "ui_endscreen.h"

EndScreen::EndScreen(BattleWindow *parent, MainWindow *mainParent) :
    QDialog(parent),
    ui(new Ui::EndScreen)
{
    ui->setupUi(this);
    if(parent != 0) {
        parent->setEnabled(false);
        this->setEnabled(true);
    } else {
        mainParent->setEnabled(false);

        this->setEnabled(true);
    }
        QGraphicsScene *scene =  new QGraphicsScene;
        QPixmap pixmap("Exit.jpg" );
        scene->addPixmap(pixmap);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->show();

}

EndScreen::~EndScreen()
{
    delete ui;
}

void EndScreen::on_pushButton_clicked()
{
    QApplication::quit() ;
}
