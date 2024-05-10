#include "GameModel.h"
#include <utility>
#include <time.h>
#include "mainwindow.h"
#include <QPainter>
#include <QTimer>

#include <QMouseEvent>
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>
#include <QDebug>
#include <math.h>

GameModel::GameModel()
{

}

extern const int kBoardMargin = 270; // 棋盘边缘空隙
extern const int kRadius = 15; // 棋子半径
extern const int kMarkSize = 6; // 落子标记边长
extern const int kBlockSize = 40; // 格子的大小
extern const int kPosDelta = 20; // 鼠标点击的模糊距离上限
extern const int kAIDelay = 700; // AI下棋的思考时间

void GameModel::startGame(GameType type)//
{
    gameType = type;
    gameround=0;
    ddl=50;
    capturesign=0;
    lastcaptureround=0;
    for(int i=0;i<kBoardSize;i++)
    {
        for(int j=0;j<kBoardSize;j++)
        {
            if(i<=1)gameMap[i][j]=-1;
            else if(i>=4)gameMap[i][j]=1;
            else gameMap[i][j]=0;
        }
    }//初始化gamemap 二维 第一维为行(y) 第二维为列（x)

    if(gameType==bot)
    {
        scoreMap.clear();

        for(int i=0;i<kBoardSize;i++)
        {
            std::vector<int> lineScores;
            for(int j=0;j<kBoardSize;j++)
            {
                lineScores.push_back(0);
            }
            scoreMap.push_back(lineScores);
        }
    }
    playerFlag=true;//white 1 black 0
}

void GameModel::updateMap(int row, int col)
{
    if(playerFlag)
        gameMap[row][col]=1;
    else
        gameMap[row][col]=-1;

    playerFlag=!playerFlag;//换手

    // mine:
    // QWidget::repaint(0,0,size().width(),size().height(),bool erase = TRUE)
    // {
    //     QPainter painter(this);
    // for (int i = 0;i < 6; i++)
    //     for (int j = 0;  j < 6; j++)

    //     {
    //         PieceColor color = (*board_)[i][j]->GetColor();
    //             if (color == PieceColor::NONE)
    //                 continue;
    //             else if(color==PieceColor::BLACK)

    //             {    QBrush brush;
    //                 brush.setColor(Qt::black);
    //                 painter.setBrush(brush);
    //                 painter.drawEllipse(kBoardMargin+kBlockSize*2+kBlockSize*i-kRadius,kBoardMargin+kBlockSize*2+kBlockSize*j-kRadius,kRadius*2,kRadius*2);}


    //             }
    //             else
    //             {
    //                 brush.setColor(Qt::white);
    //                 painter.setBrush(brush);
    //                 painter.drawEllipse(kBoardMargin+kBlockSize*2+kBlockSize*i-kRadius,kBoardMargin+kBlockSize*2+kBlockSize*j-kRadius,kRadius*2,kRadius*2);}
    //             }
    //     }
    // }

}
void GameModel::updateGame()
{
    if(playerFlag==0)gameround++;
    playerFlag=!playerFlag;
    ddl=50;
}
void GameModel::actionByPerson(int row, int col)
{
    updateMap(row,col);
}

void GameModel::actionByAi(int &crow, int &ccol)
{
    calculateScore();
    int maxScore=0;
    std::vector<std::pair<int,int>> maxPoint;

    for(int i=1;i<kBoardSize;i++)
        for(int j=1;j<kBoardSize;j++)
        {
            if(gameMap[i][j]==0)
            {
                if(scoreMap[i][j]>maxScore)
                {
                    maxPoint.clear();
                    maxScore=scoreMap[i][j];
                    maxPoint.push_back(std::make_pair(i,j));
                }
                else if(scoreMap[i][j]==maxScore)
                    maxPoint.push_back(std::make_pair(i,j));
            }
        }
    srand((unsigned)time(0));
    int index=rand()%maxPoint.size();
    std::pair<int,int> pointPair=maxPoint.at(index);

    crow=pointPair.first;
    ccol=pointPair.second;
    updateMap(crow,ccol);
}

void GameModel::calculateScore()
{
    int personNum=0;
    int botNum=0;
    int emptyNum=0;

    scoreMap.clear();
    for(int i=0;i<kBoardSize;i++)
    {
        std::vector<int> lineScore;
        for(int j=0;j<kBoardSize;j++)
            lineScore.push_back(0);
        scoreMap.push_back(lineScore);
    }

    for(int row=0;row<kBoardSize;row++)
        for(int col=0;col<kBoardSize;col++)
        {
            if(row>0&&col>0&&gameMap[row][col]==0)
            {
                for(int y=-1;y<=1;y++)
                    for(int x=-1;x<=1;x++)
                    {
                        int personNum=0;
                        int botNum=0;
                        int emptyNum=0;

                        if(!(y==0&&x==0))
                        {
                            for(int i=1;i<=4;i++)
                            {
                                if(row+i*y>0&&row+i*y<kBoardSize&&col+i*x>0&&col+i*x<kBoardSize&&gameMap[row+i*y][col+i*x]==1)
                                {
                                    personNum++;
                                }
                                else if(row+i*y>0&&row+i*y<kBoardSize&&col+i*x>0&&col+i*x<kBoardSize&&gameMap[row+i*y][col+i*x]==0)
                                {
                                    emptyNum++;
                                    break;
                                }
                                else
                                    break;
                            }
                            for(int i=1;i<=4;i++)
                            {
                                if(row-i*y>0&&row-i*y<kBoardSize&&col-i*x>0&&col-i*x<kBoardSize&&gameMap[row-i*y][col-i*x]==1)
                                {
                                    personNum++;
                                }
                                else if(row-i*y>0&&row-i*y<kBoardSize&&col-i*x>0&&col-i*x<kBoardSize&&gameMap[row-i*y][col-i*x]==0)
                                {
                                    emptyNum++;
                                    break;
                                }
                                else
                                    break;
                            }
                            if(personNum==1)
                                scoreMap[row][col]+=10;
                            else if(personNum==2)
                            {
                                if(emptyNum==1)
                                    scoreMap[row][col]+=30;
                                else if(emptyNum==2)
                                    scoreMap[row][col]+=40;
                            }
                            else if(personNum==3)
                            {
                                if(emptyNum==1)
                                    scoreMap[row][col]+=60;
                                else if(emptyNum==2)
                                    scoreMap[row][col]+=110;
                            }
                            else if(personNum==4)
                                scoreMap[row][col]+=10000;
                            emptyNum=0;


                            for(int i=1;i<=4;i++)
                            {
                                if(row+i*y>0&&row+i*y<kBoardSize&&col+i*x>0&&col+i*x<kBoardSize&&gameMap[row+i*y][col+i*x]==1)
                                {
                                    botNum++;
                                }
                                else if(row+i*y>0&&row+i*y<kBoardSize&&col+i*x>0&&col+i*x<kBoardSize&&gameMap[row+i*y][col+i*x]==0)
                                {
                                    emptyNum++;
                                    break;
                                }
                                else
                                    break;
                            }
                            for(int i=1;i<=4;i++)
                            {
                                if(row-i*y>0&&row-i*y<kBoardSize&&col-i*x>0&&col-i*x<kBoardSize&&gameMap[row-i*y][col-i*x]==-1)
                                {
                                    botNum++;
                                }
                                else if(row-i*y>0&&row-i*y<kBoardSize&&col-i*x>0&&col-i*x<kBoardSize&&gameMap[row-i*y][col-i*x]==0)
                                {
                                    emptyNum++;
                                    break;
                                }
                                else
                                    break;
                            }
                            if(botNum==0)
                                scoreMap[row][col]+=5;
                            else if(botNum==1)
                                scoreMap[row][col]+=10;
                            else if(botNum==2)
                            {
                                if(emptyNum==1)
                                    scoreMap[row][col]+=25;
                                else if(emptyNum==2)
                                    scoreMap[row][col]+=50;

                            }
                            else if(botNum==3)
                            {
                                if(emptyNum==1)
                                    scoreMap[row][col]+=50;
                                else if(emptyNum==2)
                                    scoreMap[row][col]+=110;
                            }
                            else if(botNum==4)
                                scoreMap[row][col]+=10000;
                        }
                    }
            }
        }
}

bool GameModel::isWin(int row, int col)
{
    // SurakartaIllegalMoveReason move_reason = rule_manager_->JudgeMove(move);
    // SurakartaEndReason end_reason=rule_manager->JudgeEnd(move_reason);

    // if((move_reason==SurakartaIllegalMoveReason::LEGAL_NON_CAPTURE_MOVE||move_reason==SurakartaIllegalMoveReason::LEGAL_CAPTURE_MOVE)&&IsEndReason((end_reason)))
    // {
    //     return true;
    // }
    //     return false;
    for(int i=0;i<5;i++)
    {
        if(col-i>0&&col-i+4<kBoardSize&&gameMap[row][col-i]==gameMap[row][col-i+1]&&gameMap[row][col-i]==gameMap[row][col-i+2]&&gameMap[row][col-i]==gameMap[row][col-i+3]&&gameMap[row][col-i]==gameMap[row][col-i+4])
            return true;
    }
    for(int i=0;i<5;i++)
    {
        if(row-i>0&&row-i+4<kBoardSize&&gameMap[row-i][col]==gameMap[row-i+1][col]&&gameMap[row-i][col]==gameMap[row-i+2][col]&&gameMap[row-i][col]==gameMap[row-i+3][col]&&gameMap[row-i][col]==gameMap[row-i+4][col])
            return true;
    }
    for(int i=0;i<5;i++)
    {
        if(row+i<kBoardSize&&row+i-4>0&&col-i>0&&col-i+4<kBoardSize&&gameMap[row+i][col-i]==gameMap[row+i-1][col-i+1]&&gameMap[row+i][col-i]==gameMap[row+i-2][col-i+2]&&gameMap[row+i][col-i]==gameMap[row+i-3][col-i+3]&&gameMap[row+i][col-i]==gameMap[row+i-4][col-i+4])
            return true;
    }
    for(int i=0;i<5;i++)
    {
        if(row-i>0&&row-i+4<kBoardSize&&col-i>0&&col-i+4<kBoardSize&&gameMap[row-i][col-i]==gameMap[row-i+1][col-i+1]&&gameMap[row-i][col-i]==gameMap[row-i+2][col-i+2]&&gameMap[row-i][col-i]==gameMap[row-i+3][col-i+3]&&gameMap[row-i][col-i]==gameMap[row-i+4][col-i+4])
            return true;
    }
    return false;

}

bool GameModel::isDeadGame()
{

    for(int i=1;i<kBoardSize;i++)
        for(int j=1;j<kBoardSize;j++)
        {
            if(!(gameMap[i][j]==1||gameMap[i][j]==-1))
                return false;
        }
    return true;
}

