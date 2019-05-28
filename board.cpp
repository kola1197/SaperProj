#include "board.h"
#include <QString>
#include <vector>
#include <ctime>
Board::Board()
{

}

void Board::setMineFlag(int x,int y)
{
    cages[x][y].mineFlag = !cages[x][y].mineFlag;
}

void Board::countFlags()
{
    flagsCounter = 0;
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if(cages[i][j].mineFlag)
                flagsCounter++;
        }
    }
}

void Board::generateField(int m,int n)
{
    srand(time(NULL));
    int delta [8][2] = {{1 ,  1}, {1 , -1},
                        {1 ,  0}, {-1,  1},
                        {-1,  0}, {-1, -1},
                        {0 , -1}, {0 ,  1}};

    for (int i=0;i<16;i++)
    {
        for (int j=0;j<16;j++)
        {
            cages[i][j] = Cage();
        }
    }
    int minesToAdd=40;
    while (minesToAdd>0)
    {
        int x = rand() % 16;
        int y = rand() % 16;
        if (!cages[x][y].mine)
        {
            if (x!=m || y!=n)
            {
                bool haveNotMineNearIt = true;
                for (int k=0;k<8;k++)
                {
                    if (m+delta[k][0]==x && n+delta[k][1]==y )
                    {
                        haveNotMineNearIt=false;
                    }
                }
                if (haveNotMineNearIt)
                {
                    cages[x][y].mine=true;
                    minesToAdd--;
                }
            }
        }
    }
    /*
    for (int i=0;i<16;i++)
    {
        for (int j=0;j<16;j++)
        {
            if (cages[i][j].mine)
            {
                for (int k=0;k<8;k++)
                {
                    if (i+delta[k][0]>-1 && i+delta[k][0]<16 && j+delta[k][1]>-1 && j+delta[k][1]<16 )
                        cages[i+delta[k][0]][j+delta[k][1]].countOfMines++;
                }
            }
        }
    }
    for (int i=0;i<16;i++)
    {
        for (int j=0;j<16;j++)
        {
            if (cages[i][j].mine)
            {
                //button[i][j]->setText("#");
                cages[i][j].text="#";
            }
            else
            {
                if (cages[i][j].countOfMines!=0)
                {
                    //button[i][j]->setText(QString::number(cages[i][j].countOfMines));
                    cages[i][j].text = QString::number(cages[i][j].countOfMines);
                }
            }
        }
    }

    normalizeBoard();
    */
    setField();
    /*
        for (int i=0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            cout << vec[i][j].toStdString();
        }
        cout<<"\n";
    }
*/
}

void Board::generateField(vector<pair<int,int>> mines)
{
    try {
        for (int i=0;i<16;i++)
        {
            for (int j=0;j<16;j++)
            {
                cages[i][j] = Cage();
            }
        }

        for(pair<int,int> i : mines)
        {
            int x = i.first;
            int y = i.second;
            if(x >= 0 && x < 16 && y >= 0 && y < 16)
            {
                cages[x][y].mine=true;
            }
            else {
                throw 1;
            }
        }
        setField();
    }
    catch (int e) {
        cout << "Caught exception № "<< e;
    }
}

/*
vector<vector<QString>> Board::generateField(vector<pair<int,int>> mines)
{
    try {

        for (int i=0;i<16;i++)
        {
            for (int j=0;j<16;j++)
            {
                cages[i][j] = Cage();
            }
        }

        for(pair<int,int> i : mines)
        {
            int x = i.first;
            int y = i.second;
            if(x >= 0 && x < 16 && y >= 0 && y < 16)
            {
                cages[x][y].mine=true;
            }
            else {
                throw 1;
            }
        }
        setField();
    }
    catch (int e) {
        cout << "Caught exception № "<< e;
        vector<vector<QString>> vec = {"239","239"};
        return vec;
    }
    vector<vector<QString>> vec(16, vector<QString>(16));
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            vec[i][j] = cages[i][j].text;
        }
    }

    return vec;
}
*/
void Board::setField()
{
    for (int i=0;i<16;i++)
    {
        for (int j=0;j<16;j++)
        {
            if (cages[i][j].mine)
            {
                int delta [8][2] = {{1 ,  1}, {1 , -1},
                                    {1 ,  0}, {-1,  1},
                                    {-1,  0}, {-1, -1},
                                    {0 , -1}, {0 ,  1}};
                for (int k=0;k<8;k++)
                {
                    if (i+delta[k][0]>-1 && i+delta[k][0]<16 && j+delta[k][1]>-1 && j+delta[k][1]<16 )
                        cages[i+delta[k][0]][j+delta[k][1]].countOfMines++;
                }
            }
        }
    }
    for (int i=0;i<16;i++)
    {
        for (int j=0;j<16;j++)
        {
            if (cages[i][j].mine)
            {
                //button[i][j]->setText("#");
                cages[i][j].text="#";
            }
            else
            {
                if (cages[i][j].countOfMines!=0)
                {
                    //button[i][j]->setText(QString::number(cages[i][j].countOfMines));
                    cages[i][j].text = QString::number(cages[i][j].countOfMines);
                }
            }
        }
    }
    normalizeBoard();
}

void Board::normalizeBoard()
{
    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 16; j++)
        {
            if(cages[i][j].text == "0")
            {
                cages[i][j].text = "";
            }
        }
    }
}



bool Board::checkWin()
{
    int minesCleared = 0;
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if(cages[i][j].mine && cages[i][j].mineFlag)
                minesCleared++;
        }
    }

    if(minesCleared == numOfMines)
        return true;
    else
        return false;
}

void Board::showAllMines()
{
    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 16; j++)
        {
            if(cages[i][j].mine)
            {
                cages[i][j].opened=true;
            }
        }
    }
}

int Board::openCage(int x,int y)
{
    if (!cages[x][y].opened)
    {
        cages[x][y].opened = true;
        cages[x][y].mineFlag = false;
        countOfOpened++;
        if (cages[x][y].text=="")
        {
            int delta [8][2] = { {1,  1}, {1,  -1},
                                 {1,  0}, {-1,  1},
                                 {-1, 0}, {-1, -1},
                                 {0, -1}, {0,   1} };
            for (int k=0;k<8;k++)
            {
                if (x+delta[k][0]>-1 && x+delta[k][0]<16 && y+delta[k][1]>-1 && y+delta[k][1]<16 )
                {
                    openCage(x+delta[k][0],y+delta[k][1]);
                }
            }
        }

        if(cages[x][y].mine)
            return 1;
        else
            return 0;
    }
    return -1;
}
