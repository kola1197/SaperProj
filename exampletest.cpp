#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "board.h"
#include "mainwindow.h"
#include "cage.h"
#include "iostream"
using namespace ::testing;
// Simple test, does not use gmock
TEST(Dummy, foobar)
{
    EXPECT_EQ(1, 1);
}

bool AreVectorsEq(vector<vector<QString>> vec_1, vector<vector<QString>> vec_2)
{
    for (int i = 0; i < vec_1.size(); i++) {
        for (int j = 0; j < vec_1[i].size(); j++) {
            if(vec_1[i][j] != vec_2[i][j])
                return false;
        }
    }
    return true;
}



TEST(SaperTest, TestGame)
{
    Board testBoard;
    vector<pair<int,int>> mines = {
        {0,0},{0,3},{0,9},
        {1,5},{1,11},{1,14},
        {2,1},{2,7},{2,12},
        {3,15},
        {4,2},{4,4},{4,6},{4,10},
        {5,13},
        {6,0},{6,3},{6,11},{6,15},
        {7,6},{7,8},{7,10},
        {8,2},{8,4},{8,13},
        {10,6},{10,11},{10,15},
        {11,0},{11,4},
        {12,2},{12,13},
        {13,3},{13,7},{13,15},
        {14,10},
        {15,0},{15,3},{15,7},{15,13}};

    /** Generating board test **/
    vector<vector<QString>> testBoardText(16, vector<QString>(16));
    testBoard.generateField(mines);

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            testBoardText[i][j] = testBoard.cages[i][j].text;
        }
    }

    vector<vector<QString>> expectedBoardText = {
         {"#","1","1","#","2","1","1","" ,"1","#","2","1","1","1","1","1"},
         {"2","2","2","1","2","#","2","1","2","1","2","#","2","2","#","1"},
         {"1","#","1","" ,"1","1","2","#","1","" ,"1","2","#","2","2","2"},
         {"1","2","2","2","1","2","2","2","1","1","1","2","1","1","1","#"},
         {"" ,"1","#","2","#","2","#","1","" ,"1","#","1","1","1","2","1"},
         {"1","2","2","3","2","2","1","1","" ,"1","2","2","2","#","2","1"},
         {"#","1","1","#","1","1","1","2","1","2","2","#","2","1","2","#"},
         {"1","2","2","3","2","2","#","2","#","2","#","2","2","1","2","1"},
         {"" ,"1","#","2","#","2","1","2","1","2","1","1","1","#","1","" },
         {"" ,"1","1","2","1","2","1","1","" ,"" ,"1","1","2","1","2","1"},
         {"1","1","" ,"1","1","2","#","1","" ,"" ,"1","#","1","" ,"1","#"},
         {"#","2","1","2","#","2","1","1","" ,"" ,"1","1","2","1","2","1"},
         {"1","2","#","3","2","1","1","1","1","" ,"" ,"" ,"1","#","2","1"},
         {"" ,"1","2","#","1","" ,"1","#","1","1","1","1","1","1","2","#"},
         {"1","1","2","2","2","" ,"2","2","2","1","#","1","1","1","2","1"},
         {"#","1","1","#","1","" ,"1","#","1","1","1","1","1","#","1","" }};

    for (int i = 0; i < 16; i++) {
        EXPECT_THAT(testBoardText[i],ElementsAreArray(expectedBoardText[i]));
    }

    /** Left click test **/
    EXPECT_EQ(testBoard.openCage(11,9), 0);
    Board expectedBoard;
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            expectedBoard.cages[i][j].text = expectedBoardText[i][j];
        }
    }

    for (int i = 8; i < 13; i++) {
        for (int j = 7; j < 11; j++) {
            expectedBoard.cages[i][j].opened = true;
        }
    }

    for (int i = 8; i < 13; i++) {
        expectedBoard.cages[13][i].opened = true;
    }

    for (int i = 11; i < 13; i++) {
        for (int j = 11; j < 14; j++) {
            expectedBoard.cages[i][j].opened = true;
        }
    }
    EXPECT_TRUE(testBoard.boardsAreEqual(expectedBoard));

    //1 more click
    for (int i = 14; i < 16; i++) {
        for (int j = 14; j < 16; j++) {
            expectedBoard.cages[i][j].opened = true;
        }
    }
    testBoard.openCage(15, 15);
    EXPECT_TRUE(testBoard.boardsAreEqual(expectedBoard));

    /** Right click test **/
    testBoard.setMineFlag(4, 2);
    testBoard.setMineFlag(2, 12);
    testBoard.setMineFlag(13, 15);
    testBoard.setMineFlag(15, 0);

    expectedBoard.cages[4][2].mineFlag = true;
    expectedBoard.cages[2][12].mineFlag = true;
    expectedBoard.cages[13][15].mineFlag = true;
    expectedBoard.cages[15][0].mineFlag = true;

    EXPECT_TRUE(testBoard.boardsAreEqual(expectedBoard));

    /** You Win Test **/
    testBoard.setMineFlag(0, 0);    testBoard.setMineFlag(0, 3);
    testBoard.setMineFlag(0, 9);    testBoard.setMineFlag(1, 5);
    testBoard.setMineFlag(1, 11);   testBoard.setMineFlag(1, 14);
    testBoard.setMineFlag(2, 1);    testBoard.setMineFlag(2, 7);
    testBoard.setMineFlag(3, 15);   testBoard.setMineFlag(4, 4);
    testBoard.setMineFlag(4, 6);    testBoard.setMineFlag(4, 10);
    testBoard.setMineFlag(5, 13);   testBoard.setMineFlag(6, 0);
    testBoard.setMineFlag(6, 3);    testBoard.setMineFlag(6, 11);
    testBoard.setMineFlag(6, 15);   testBoard.setMineFlag(7, 6);
    testBoard.setMineFlag(7, 8);    testBoard.setMineFlag(7, 10);
    testBoard.setMineFlag(8, 2);    testBoard.setMineFlag(8, 4);
    testBoard.setMineFlag(8, 13);   testBoard.setMineFlag(10, 6);
    testBoard.setMineFlag(10, 11);  testBoard.setMineFlag(10, 15);
    testBoard.setMineFlag(11, 0);   testBoard.setMineFlag(11, 4);
    testBoard.setMineFlag(12, 2);   testBoard.setMineFlag(12, 13);
    testBoard.setMineFlag(13, 3);   testBoard.setMineFlag(13, 7);
    testBoard.setMineFlag(14, 10);  testBoard.setMineFlag(15, 3);
    testBoard.setMineFlag(15, 7);   testBoard.setMineFlag(15, 13);
    EXPECT_TRUE(testBoard.checkWin());
}
