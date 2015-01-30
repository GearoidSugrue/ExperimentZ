#include "exit.h"
#include "ui_exit.h"

Exit::Exit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Exit)
{
    ui->setupUi(this);
}

Exit::~Exit()
{
    delete ui;
}
