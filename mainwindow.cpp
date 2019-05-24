#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "qrightclickbutton.h"

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
    this->setWindowTitle("Сапер");
    drawField();
    mainBoard = Board();
    gameIsActive=true;
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
                else {
                    x+=s[i];
                }
            }
        }
        std::cout<<x.toStdString()<<" -x, and y = "<<y.toStdString()<<std::endl;
        if (!wasFirstClick)
        {
            wasFirstClick=true;
            mainBoard.generateField(x.toInt(),y.toInt());
        }
        if (mainBoard.openCage(x.toInt(),y.toInt()))
        {
            gameIsActive=false;
            this->setWindowTitle("Game over");
        }
    }
    redraw();
}

void MainWindow::onRightClick()
{
    if (gameIsActive)
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
                else {
                    x+=s[i];
                }
            }
        }
        std::cout<<x.toStdString()<<" -x, and y = "<<y.toStdString()<<std::endl;
        if (!wasFirstClick)
        {
            wasFirstClick=true;
            mainBoard.generateField(x.toInt(),y.toInt());
        }
        setMineFlag(x.toInt(),y.toInt());
    }
    redraw();
}

void MainWindow::setMineFlag(int x,int y)
{
    cages[x][y].mineFlag = true;
    cages[x][y].text = "10";
    updateGame();
}

void MainWindow::updateGame()
{
    if (countOfOpened==16*16-40 && gameIsActive)
    {
        gameIsActive=false;
        this->setWindowTitle("You win!!!");
    }
    redraw();
}

void MainWindow::redraw()
{
    for (int i=0;i<16;i++)
    {
        for (int j=0;j<16;j++)
        {
            if (mainBoard.cages[i][j].opened || mainBoard.cages[i][j].mineFlag)
            {
                button[i][j]->setText(mainBoard.cages[i][j].text.c_str());
            }
            if (mainBoard.cages[i][j].mineFlag)
            {
                button[i][j]->setText("@");
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
/*
    connect(this, SIGNAL(rightClicked), this, SLOT(onRightClick));
    connect(this, SIGNAL(leftClicked), this, SLOT(onLeftClick));
*/
}

