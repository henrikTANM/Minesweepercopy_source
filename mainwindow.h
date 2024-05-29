#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gamewindow.h>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui {
    class Minesweeper;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void unHide();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_width_textEdited();

    void on_height_textEdited();

    void on_bombs_textEdited();

private:
    Ui::Minesweeper *ui;
    GameWindow *gameWindow;

    bool canPlay();

    void setSettings(int, int, int);
};
#endif // MAINWINDOW_H
