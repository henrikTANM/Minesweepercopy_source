#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include <QGridLayout>
#include "game.h"
#include "endgamepopup.h"


using namespace std;

namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr, int *width = nullptr, int *heigth = nullptr, int *bombs = nullptr);
    ~GameWindow();

private:
    Ui::GameWindow *ui;
    Game *game;
    EndGamePopup *endGamePopup;
    QGridLayout *board;

    QString buttonStyle{""};

    int width;
    int heigth;
    int bombs;

    void menuButtonPushed(QWidget *);
    void newBoardButtonPushed();
    void boardButtonPushed(int, int);
    void generateButtons(int, int);
    void changeButton(QPushButton *, QString);
    void deleteButtons();

    void endGamePopUp(bool);
};

#endif // GAMEWINDOW_H
