#include "endgamepopup.h"
#include "ui_endgamepopup.h"

EndGamePopup::EndGamePopup(QWidget *parent, QString message)
    : QDialog(parent)
    , ui(new Ui::EndGamePopup)
{
    ui->setupUi(this);
    this->setWindowTitle(message);
    ui->message->setText(message);
}

EndGamePopup::~EndGamePopup()
{
    delete ui;
}

void EndGamePopup::on_pushButton_clicked()
{
    this->close();
}

