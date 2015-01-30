#include "winscreen.h"
#include "ui_winscreen.h"

#include <fstream>
#include <QFile>
#include <QTextStream>

WinScreen::WinScreen(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::WinScreen)
{
    ui->setupUi(this);

    parent->setEnabled(false);

    this->setEnabled(true);

    QString name = QString::fromStdString(":/textFiles/Win Screen");

    QTextEdit *textEdit = ui->winTextEdit ;

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

WinScreen::~WinScreen()
{
    delete ui;
}

void WinScreen::on_pushButton_clicked()
{
    QApplication::quit() ;
}
