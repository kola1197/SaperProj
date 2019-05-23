#include "cage.h"
#ifndef BOARD_H
#define BOARD_H


class Board
{
public:
    Board();
    Cage cages [16][16];
    int countOfOpened=0;
    void generateField();
    bool gameIsActive=false;
    void startGame();
    bool generateField(const int mines[40][2]);
    void setMineFlag(int x, int y);
    void redraw();
    void updateGame();

    bool generateField(int x, int y);
    bool openCage(int x, int y);
};

#endif // BOARD_H
