#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cage.h"
#include <QPushButton>
#include "board.h"
#include "QMouseEvent"
#include "qrightclickbutton.h"
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
    bool gameIsActive=false;
    bool wasFirstClick=false;
    void startGame();
    std::pair<int,int> findXYInButton();
    void newGame();

signals:
    void rightClicked();
    void leftClicked();

//protected:
    //void mouseReleaseEvent(QMouseEvent *e);

private:
    QIcon iconDefault;
    QRightClickButton *button[16][16];
    pair<int,int> failedAt = {-1, -1};


public slots:
    void mouseReleaseEvent(QMouseEvent *e);
    void onRightClick();
    void onLeftClick();

private slots:
    void on_actionExit_triggered();


    void on_pushButton_released();

private:
    Ui::MainWindow *ui;
    void redraw();
    void updateGame();
};

#endif // MAINWINDOW_H
