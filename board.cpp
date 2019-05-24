#include "board.h"
#include <QString>

Board::Board()
{

}

void Board::setMineFlag(int x,int y)
{
    cages[x][y].mineFlag = !cages[x][y].mineFlag;
}

bool Board::generateField(int m,int n)
{
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
        int x = std::rand() % 16;
        int y = std::rand() % 16;
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
                    cages[i][j].text = QString::number(cages[i][j].countOfMines).toStdString();
                }
            }
        }
    }
}

void Board::generateField()
{
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
        int x = std::rand() % 16;
        int y = std::rand() % 16;
        if (!cages[x][y].mine)
        {
            cages[x][y].mine=true;
            minesToAdd--;
        }
    }
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
                    cages[i][j].text = QString::number(cages[i][j].countOfMines).toStdString();
                }
            }
        }
    }
}

bool Board::generateField(const int mines[40][2])
{
    try {

        for (int i=0;i<16;i++)
        {
            for (int j=0;j<16;j++)
            {
                cages[i][j] = Cage();
            }
        }

        for(int i = 0; i < 40; i++)
        {
            int x = mines[i][0];
            int y = mines[i][1];
            if(x >= 0 && x < 16 && y >= 0 && y < 16)
            {
                cages[mines[i][0]][mines[i][1]].mine=true;
            }
            else {
                throw 1;
            }
        }

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
                        cages[i][j].text = QString::number(cages[i][j].countOfMines).toStdString();
                    }
                }
            }
        }
    }
    catch (int e) {
        std::cout << "Caught exception № "<< e;
        return false;
    }
    return true;
}

bool Board::openCage(int x,int y)
{
    if (!cages[x][y].opened)
    {
        cages[x][y].opened=true;
        countOfOpened++;
        if (cages[x][y].text=="0")
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
        return cages[x][y].mine;
    }
}
