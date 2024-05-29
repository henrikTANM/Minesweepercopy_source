#ifndef ENDGAMEPOPUP_H
#define ENDGAMEPOPUP_H

#include <QDialog>

namespace Ui {
class EndGamePopup;
}

class EndGamePopup : public QDialog
{
    Q_OBJECT

public:
    explicit EndGamePopup(QWidget *parent = nullptr, QString message = nullptr);
    ~EndGamePopup();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EndGamePopup *ui;
};

#endif // ENDGAMEPOPUP_H
