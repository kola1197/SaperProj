#include "cage.h"
#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "QString"
using namespace std;

class Board
{
public:
    Board();
    Cage cages [16][16];
    int countOfOpened=0;
    void generateField();
    bool gameIsActive=false;
    void startGame();
    void redraw();
    void updateGame();

    bool generateField(int x, int y);
    bool openCage(int x, int y);
    void setMineFlag(int x, int y);
    vector<vector<QString>> generateField(vector<pair<int, int>> mines);
};

#endif // BOARD_H
