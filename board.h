#include "cage.h"
#ifndef BOARD_H
#define BOARD_H
#include <QPushButton>
#include <vector>
#include "QString"
#include <QMainWindow>
#include "QMouseEvent"
#include "qrightclickbutton.h"
using namespace std;

class Board
{
public:
    Board();
    Cage cages [16][16];
    int countOfOpened = 0;
    int flagsCounter = 0;
    int numOfMines = 40;
    void generateField();
    bool gameIsActive=false;
    void startGame();
    void redraw();
    void updateGame();

    bool checkWin();
    void showAllMines();
    void generateField(int x, int y);
    int openCage(int x, int y);
    void setMineFlag(int x, int y);
    void countFlags();
    vector<vector<QString>> generateField(vector<pair<int, int>> mines);
private:
    void normalizeBoard();
};

#endif // BOARD_H
