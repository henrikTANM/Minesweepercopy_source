#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewindow.h"
#include "QString"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Minesweeper)
{
    ui->setupUi(this);
    this->setWindowTitle("Minesweeper");

    ui->comboBox->addItem("Easy");
    ui->comboBox->addItem("Normal");
    ui->comboBox->addItem("Difficult");
    ui->comboBox->addItem("Custom");

    ui->width->setMaxLength(2);
    ui->height->setMaxLength(2);
    ui->bombs->setMaxLength(3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::unHide() {
    this->show();
}

void MainWindow::on_pushButton_clicked()
{
    if (canPlay()) {
        this->hide();
        int w = ui->width->text().toInt();
        int h = ui->height->text().toInt();
        int b = ui->bombs->text().toInt();
        gameWindow = new GameWindow(this, &w, &h, &b);
        gameWindow->show();
    }
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        setSettings(8, 8, 10);
        break;
    case 1:
        setSettings(16, 16, 40);
        break;
    case 2:
        setSettings(32, 16, 80);
        break;
    default:
        break;
    }
}

void MainWindow::setSettings(int w, int h, int b) {
    ui->width->setText(QString::number(w));
    ui->height->setText(QString::number(h));
    ui->bombs->setText(QString::number(b));
}

void MainWindow::on_width_textEdited()
{
    ui->comboBox->setCurrentIndex(3);
}

void MainWindow::on_height_textEdited()
{
    ui->comboBox->setCurrentIndex(3);
}

void MainWindow::on_bombs_textEdited()
{
    ui->comboBox->setCurrentIndex(3);
}

bool MainWindow::canPlay() {
    bool widthOk;
    int w = ui->width->text().toInt(&widthOk);
    bool heightOk;
    int h = ui->height->text().toInt(&heightOk);
    bool bombsOk;
    int b = ui->bombs->text().toInt(&bombsOk);

    if (widthOk & heightOk & bombsOk){
        bool inputsMoreThanOne = (w > 1 & h > 1 & b > 1);
        bool lessThanHalfBombs = ((w * h) / 2 > b);
        return inputsMoreThanOne & lessThanHalfBombs;
    }
    else return false;
}

