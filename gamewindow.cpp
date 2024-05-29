#include "gamewindow.h"
#include "mainwindow.h"
#include "ui_gamewindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>

GameWindow::GameWindow(QWidget *parent, int *width, int *heigth, int *bombs)
    : QDialog(parent)
    , ui(new Ui::GameWindow)
{
    this->width = *width;
    this->heigth = *heigth;
    this->bombs = *bombs;

    ui->setupUi(this);
    this->setWindowTitle("Minesweeper");
    setFixedSize(*width * 25, *heigth * 25 + 25);

    QPushButton *menuButton = new QPushButton("Back to Menu");
    menuButton->setFixedSize(100, 25);
    connect(menuButton, &QPushButton::released, this, [this, parent]{ menuButtonPushed(parent); });

    QPushButton *newBoardButton = new QPushButton("New Game");
    newBoardButton->setFixedSize(100, 25);
    connect(newBoardButton, &QPushButton::released, this, &GameWindow::newBoardButtonPushed);

    QHBoxLayout *menuBar = new QHBoxLayout;
    menuBar->addWidget(menuButton, 0, Qt::AlignLeft);
    menuBar->addWidget(newBoardButton, 0, Qt::AlignRight);

    board = new QGridLayout;
    generateButtons(*width * 25, *heigth * 25);

    QVBoxLayout *window = new QVBoxLayout;
    window->addLayout(menuBar, Qt::AlignTop);
    window->addLayout(board, Qt::AlignTop);

    setLayout(window);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::menuButtonPushed(QWidget *parent) {
    MainWindow *mainWindow = dynamic_cast<MainWindow*>(parent);
    mainWindow->show();
    this->close();
}

void GameWindow::newBoardButtonPushed() {
    generateButtons(width * 25, heigth * 25);
}

void GameWindow::boardButtonPushed(int i, int j) {
    if (!game->running) { return; }

    tuple<vector<tuple<int, int>>, bool> revealedTiles = game->reveal(i, j);
    for(tuple<int, int> revealedTile : get<0>(revealedTiles)) {
        int row = get<0>(revealedTile);
        int col = get<1>(revealedTile);

        QLayoutItem* item = board->itemAtPosition(row, col);
        QWidget* widget = item->widget();
        QPushButton* button = dynamic_cast<QPushButton*>(widget);

        QString text = QString(game->board[row][col].value);
        if (text == "0") { text = " "; }
        changeButton(button, text);
    }

    if (game->board[i][j].value == 'x') {
        endGamePopUp(false);
    } else if (game->checkAllRevealed()) {
        endGamePopUp(true);
    }
}

void GameWindow::changeButton(QPushButton* button, QString text) {
    QString color;
    if ((text != " ") && (text != "x")) {
        switch (text.toInt()) {
        case 1:
            color = "blue";
            break;
        case 2:
            color = "green";
            break;
        case 3:
            color = "red";
            break;
        case 4:
            color = "navy";
            break;
        case 5:
            color = "maroon";
            break;
        case 6:
            color = "purple";
            break;
        case 7:
            color = "lime";
            break;
        case 8:
            color = "olive";
            break;
        default:
            break;
        }
    }
    button->setText(text);
    button->setStyleSheet(buttonStyle + ";" + "font-weight: bold; color: " + color);
}

void GameWindow::generateButtons(int width, int heigth) {
    game = new Game(this->heigth, this->width, this->bombs);
    deleteButtons();
    for (int i = 0; i < game->rows; i++) {
        for (int j = 0; j < game->cols; j++) {
            QPushButton *button = new QPushButton(" ");
            button->setFixedSize(heigth/game->rows - 1, width/game->cols - 1);
            buttonStyle = button->styleSheet();
            button->setStyleSheet("background-color: rgb(210,210,210);");
            connect(button, &QPushButton::clicked, this, [this, i, j]{ boardButtonPushed(i, j); });
            board->addWidget(button, i, j);
        }
    }
}

void GameWindow::deleteButtons() {
    QLayoutItem* item;
    while ( ( item = board->layout()->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }
}

void GameWindow::endGamePopUp(bool won) {
    QString message = won ? "You Won! :)" : "You Lost! :(";
    endGamePopup = new EndGamePopup(this, message);
    endGamePopup->show();
    game->running = !game->running;
}

