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
    int numOfRows = 16, numOfColumns = 16;
    int countOfOpened = 0;
    int flagsCounter = 0;
    int numOfMines = 40;
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
    void generateField(vector<pair<int, int>> mines);

    inline bool boardsAreEqual (const Board &that) const
    {
        for (int i = 0; i < numOfRows; i++)
            for(int j = 0; j < numOfColumns; j++)
            {
                Cage cage_1 = that.cages[i][j];
                Cage cage_2 = cages[i][j];
                if(cage_1.text == cage_2.text &&
                   cage_1.opened == cage_2.opened &&
                   cage_1.mineFlag == cage_2.mineFlag)
                    return true;
                else
                    return false;
            }
        return false;
    }
private:
    void normalizeBoard();
    void setField();
};

#endif // BOARD_H
