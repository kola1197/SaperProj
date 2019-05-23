#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cage.h"
#include <QPushButton>
#include "board.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Board mainBoard;
    void drawField();
    Cage cages [16][16];
    bool gameIsActive=false;
    bool wasFirstClick=false;
    void startGame();
private:
    QIcon iconDefault;
    QPushButton *button[16][16];
    int countOfOpened=0;
public slots:

    void onClick();
private slots:
    void on_actionExit_triggered();


private:
    Ui::MainWindow *ui;
    void setMineFlag(int x, int y);
    void redraw();
    void updateGame();
};

#endif // MAINWINDOW_H
