#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStatusBar>
#include <QLabel>
#include "GameModel.h"
#include <networksocket.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   // void init(bool bRedSide);//

    NetworkSocket *socket;
    QString ipaddress;
    quint16 q16;

protected:
    void paintEvent(QPaintEvent *event);

    void mouseMoveEvent(QMouseEvent *event);//鼠标监听

    void mouseReleaseEvent(QMouseEvent *event);
    void drawPlate(QPainter &p);
    void drawPiece(QPainter &painter);
    void drawInitPosition(QPainter &p);

private:

    GameModel *game;
    GameType game_type;
    int clickPosRow,clickPosCol,selectPosRow,selectPosCol,select[7][7]={0};
    void initGame();
    void checkGame(int y,int x);

    bool selectPos=false;
    QStatusBar *statusBar;//
    QLabel *turnLabel;
    QLabel *playerLabel;
    QLabel *ddlLabel;
    int turn;
    bool judge_move(int ux,int uy,int vx,int vy,int now_player);
    void judge_end();

private slots:
    void chessOneByPerson();
    void chessOneByAi();
    void initPVPGame();
    void initPVCGame();
    void playagain()
    {
        game_type=person;
        game->gameStatus=playing;
        game->startGame(game_type);
        update();
    }
    void admitlose();
    void whitewin();
    void blackwin();
    void nonewin();
    void updateTurn()
    {
        turn++;
        turnLabel->setText(QString("Turn:%1").arg(game->gameround));
    }
    void updatePlayer()
    {
        if(game->playerFlag==0)playerLabel->setText(QString("Turn:BLACK"));
        if(game->playerFlag==1)playerLabel->setText(QString("Turn:WHITE"));
    }
    void updateDdl()
    {
        game->ddl--;
        ddlLabel->setText(QString("Time Left :%1").arg(game->ddl));
        if(game->ddl==0)admitlose();
    }
    void receive()
    {
        ;
    }
    void displayError()
    {
        statusBar->showMessage("displayError",5000);
    }
    void connected()
    {
        statusBar->showMessage("connected",5000);
    }

};
#endif // MAINWINDOW_H

