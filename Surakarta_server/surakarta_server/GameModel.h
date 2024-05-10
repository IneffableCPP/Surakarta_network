#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include <vector>
//游戏类型
enum GameType
{
    person,
    bot
};

//游戏状态
enum GameStatus
{
    playing,
    win,
    dead
};


const int kBoardSize=6;

class GameModel
{
public:
    GameModel();

public:
    int gameMap[6][6];//二维数组
    std::vector<std::vector<int>> scoreMap;//各点位评分情况
    bool playerFlag;//标识下棋方 ture为white false black为白棋
    int gameround;
    int lastcaptureround;
    int capturesign;
    int ddl;
    GameType gameType;
    GameStatus gameStatus;

    void startGame(GameType type);
    void calculateScore();
    void actionByPerson(int row,int col);
    void actionByAi(int &row,int &col);
    void updateMap(int row,int col);
    void updateGame();
    bool isWin(int row,int col);
    bool isDeadGame();

signals:

};
#endif // GAMEMODEL_H
