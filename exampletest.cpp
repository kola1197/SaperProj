#include "gtest/gtest.h"
#include "mainwindow.h"
// Simple test, does not use gmock
TEST(Dummy, foobar)
{
    EXPECT_EQ(1, 1);
}

TEST(SaperTest, TestGame)
{
    MainWindow w;
    int mines[40][2] = {{0,0},{0,3},{0,9},
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
    EXPECT_TRUE(w.generateField(mines));
}
