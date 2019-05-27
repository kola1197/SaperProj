#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "qrightclickbutton.h"
#include "stdio.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::startGame()
{
    drawField();
    mainBoard = Board();
    gameIsActive=true;
    this->setWindowTitle("Flags Left: " + QString::number(mainBoard.numOfMines));
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton) emit rightClicked();
    else if (e->button() == Qt::LeftButton) emit leftClicked();
}

void MainWindow::onLeftClick()
{
    if (gameIsActive)
    {
        std::pair<int,int> pair = findXYInButton();
        if(!mainBoard.cages[pair.first][pair.second].mineFlag)
        {
            if (mainBoard.openCage(pair.first, pair.second) == 1)
            {
                gameIsActive=false;
                this->setWindowTitle("Game over");
                mainBoard.showAllMines();
                failedAt = pair;
            }
        }
    }
    redraw();
}

void MainWindow::onRightClick()
{
    if (gameIsActive && mainBoard.flagsCounter != mainBoard.numOfMines)
    {
        std::pair<int,int> pair = findXYInButton();
        mainBoard.setMineFlag(pair.first, pair.second);
    }
    updateGame();
    redraw();
}

std::pair<int,int> MainWindow::findXYInButton()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    QString s = buttonSender->toolTip();

    QString x = "";
    QString y = "";
    bool wasDelimiter=false;
    for (int i=0;i<s.length();i++)
    {
        if (s[i]=='_')
        {
            wasDelimiter=true;
        }
        else {
            if (wasDelimiter)
            {
                y+=s[i];
            }
            else
            {
                x+=s[i];
            }
        }
    }
    std::cout<<"x = "<<x.toStdString()<<" and y = "<<y.toStdString()<<std::endl;

    if (!wasFirstClick)
    {
        wasFirstClick=true;
        mainBoard.generateField(x.toInt(),y.toInt());
        /*
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
        mainBoard.generateField(mines);
        */
    }

    return std::pair<int,int>(x.toInt(), y.toInt());
}

void MainWindow::newGame()
{

    if(failedAt.first != -1)
        button[failedAt.first][failedAt.second]->setStyleSheet("QPushButton{border: none background-color: rgb(221,221,221)}");

    failedAt={-1, -1};
    wasFirstClick=false;
    startGame();
}



void MainWindow::updateGame()
{
    mainBoard.countFlags();
    int flagsLeft = mainBoard.numOfMines - mainBoard.flagsCounter;
    this->setWindowTitle("Flags Left: " + QString::number(flagsLeft));
    if ((mainBoard.countOfOpened == (16*16 - mainBoard.numOfMines) || mainBoard.checkWin()) && gameIsActive)
    {
        gameIsActive=false;
        this->setWindowTitle("You win!!!");
        mainBoard.showAllMines();
    }
    redraw();
}

void MainWindow::redraw()
{
    QPalette grayPal;

    if(failedAt != pair<int,int> {-1,-1})
    {
        button[failedAt.first][failedAt.second]->setStyleSheet("QPushButton{background-color: red}");
        button[failedAt.first][failedAt.second]->setIcon(QIcon(":/resources/mine1_red.jpg"));
    }

    for (int i=0;i<16;i++)
    {
        for (int j=0;j<16;j++)
        {
            if (mainBoard.cages[i][j].opened)
            {
                if(mainBoard.cages[i][j].text == "#")
                {
                    if(pair<int,int> {i, j} != failedAt)
                        button[i][j]->setIcon(QIcon(":/resources/mine1.png"));
                }
                else
                {
                    button[i][j]->setText(mainBoard.cages[i][j].text);
                    button[i][j]->setIcon(QIcon());
                }
                if(mainBoard.cages[i][j].text == "")
                {
                    //button[i][j]->setStyleSheet("QPushButton{ border: none; solid #ffff00; background-color: gray}");
                    button[i][j]->setEnabled(false);
                    //grayPal = button[i][j]->palette();
                    //grayPal.setColor(QPalette::Button, QColor(Qt::darkGray));
                    //button[i][j]->setAutoFillBackground(true);
                    //button[i][j]->setPalette(grayPal);
                    //button[i][j]->update();

                }
            }
            else
            {
                if (mainBoard.cages[i][j].mineFlag)
                {
                    //button[i][j]->setText("@");
                    button[i][j]->setIcon(QIcon(":/resources/flag.png"));
                }
                else
                {
                    button[i][j]->setIcon(QIcon());
                    button[i][j]->setText("");
                }
            }
        }
    }
}

void MainWindow::drawField()
{
    ui->gridLayout_2->setSpacing(0);
    for (int i=0;i<16;i++)
    {
        for (int j = 0; j < 16; j++)
        {
            QString name = QString::number(i)+"_"+QString::number(j);
            //button[i][j]->setObjectName( "PPPPPP");
            button[i][j] = new QRightClickButton();

            button[i][j]->setFixedSize(40,40);
            button[i][j]->move(40*i,40*j);

            button[i][j]->setToolTip(name);
            button[i][j]->setToolTipDuration(1);
            connect(button[i][j], &QRightClickButton::rightClicked, this, &MainWindow::onRightClick);
            connect(button[i][j], &QRightClickButton::leftClicked, this, &MainWindow::onLeftClick);
            button[i][j]->show();
            ui->gridLayout_2->addWidget(button[i][j],i,j);
        }
    }
}


void MainWindow::on_pushButton_released()
{
    newGame();
}
