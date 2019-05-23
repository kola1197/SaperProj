#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cage.h"
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void drawField();
    Cage cages [16][16];
    void generateField();
    bool gameIsActive=false;
    void startGame();
    bool generateField(const int mines[40][2]);
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
    void openCage(int x, int y);
    void setMineFlag(int x, int y);
    void redraw();
    void updateGame();
};

#endif // MAINWINDOW_H
