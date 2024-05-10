
#include "mainwindow.h"
#include <QPainter>
#include <QTimer>

#include <QMouseEvent>
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>
#include <QDebug>
#include <math.h>

#define CHESS_ONE_SOUND ":/res/chessone.wav"
#define WIN_SOUND ":/res/win.wav"
#define LOSE_SOUND ":/res/lose.wav"

const int kBoardMargin = 270; // 棋盘边缘空隙
const int kRadius = 15; // 棋子半径
const int kMarkSize = 6; // 落子标记边长
const int kBlockSize = 40; // 格子的大小
const int kPosDelta = 15; // 鼠标点击的模糊距离上限
int flag=0;
const int kAIDelay = 700; // AI下棋的思考时间 过了700再下棋

MainWindow::MainWindow(QWidget *parent)//构造函数 窗口一创建就调用该函数i
    : QMainWindow(parent)
{



    //ui->setupUi(this);
    setMouseTracking(true);

    setFixedSize(kBoardMargin*2+(kBlockSize+4)*kBoardSize,kBoardMargin*2+(kBlockSize+4)*kBoardSize);//设置窗口大小
    //setStyleSheet("background-color:white;");
    //setStyleSheet("background-color:transparent;");



    QMenu *gameMenu = menuBar()->addMenu(tr("Game Model:"));
    QAction *actionPVP = new QAction("PVP",this);
    connect(actionPVP,SIGNAL(triggered()),this,SLOT(initPVPGame()));
    menuBar()->addAction(actionPVP);
    //gameMenu->addAction(actionPVP);


    QAction *actionPVC = new QAction("PVC",this);
    connect(actionPVC,SIGNAL(triggered()),this,SLOT(initPVCGame()));
    menuBar()->addAction(actionPVC);

    QAction *admitlose = new QAction("admitlose",this);
    connect(admitlose,SIGNAL(triggered()),this,SLOT(admitlose()));
    menuBar()->addAction(admitlose);

    //gameMenu->addAction(actionPVC);

    //QLturnlabel=new QLabel("Turn:1",this);



    statusBar =new QStatusBar(this);
    setStatusBar(statusBar);

    QFont font;
    font.setPointSize(16);


    //turnLabel->setFont(font);
    turnLabel=new QLabel("Turn:0",this);
    turnLabel->setAlignment(Qt::AlignCenter);
    statusBar->addWidget(turnLabel);

    QTimer *timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,updateTurn);
    timer->start(1000);

    //playerLabel->setFont(font);
    playerLabel=new QLabel("Player:WHITE",this);
    playerLabel->setAlignment(Qt::AlignCenter);
    statusBar->addWidget(playerLabel);
    connect(timer,&QTimer::timeout,this,updatePlayer);

    ddlLabel=new QLabel("Time Left :50",this);
    playerLabel->setAlignment(Qt::AlignCenter);
    statusBar->addWidget(ddlLabel);
    connect(timer,&QTimer::timeout,this,updateDdl);


    //QStatusBar* sb=statusBar;

   // QLabel* l=new QLabel("hello");
    //sb->addWidget(l);
   // statusBar->showMessage("Ready");
    //QLabel *locationLabel=new QLabel(this);



    initGame();
    //初始化游戏

    this->socket = new NetworkSocket(new QTcpSocket(), this);

    connect(socket, &NetworkSocket::receive, this, receive);
    connect(socket->base(), &QAbstractSocket::disconnected, [=]() {
        QMessageBox::critical(this, tr("Connection lost"), tr("Connection to server has closed"));
    });

    connect(socket->base(), &QAbstractSocket::errorOccurred, this, displayError);
    connect(socket->base(), &QAbstractSocket::connected, this, connected);
    ipaddress="192.168.43.32";
    q16=3389;
    socket->hello(ipaddress,q16);
}

MainWindow::~MainWindow()
{

    if(game)
    {
        delete game;
        game=nullptr;
    }
}

/*void MainWindow::init(bool bRedSide)
{
    for(int i=0; i<32; ++i)
    {
        _s[i].init(i);
    }
    if(bRedSide)
    {
        for(int i=0; i<32; ++i)
        {
            _s[i].rotate();
        }
    }

    _selectid = -1;
    _bRedTurn = true;
    _bSide = bRedSide;
    update();
}
*/
void MainWindow::initGame()
{
   // _selectid = -1;

    game = new GameModel;//初始化游戏模型

    initPVPGame();
}

void MainWindow::initPVPGame()
{
    game_type=person;
    game->gameStatus=playing;
    game->startGame(game_type);//开始游戏
    update();
}

void MainWindow::admitlose()
{
    if(game->playerFlag==1)statusBar->showMessage("BLACK WIN",5000);
    else statusBar->showMessage("WHITE WIN",5000);
    QTimer *timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,playagain);
    timer->setSingleShot(true);
    timer->setInterval(5000);
    timer->start();
}
void MainWindow::whitewin()
{
    statusBar->showMessage("WHITE WIN",5000);
    /*QTimer timer;
    timer.setInterval(5000);
    QObject::connect(&timer,&QTimer::timeout,this,playagain);
    timer.start();*/
    /*game_type=person;
    game->gameStatus=playing;
    game->startGame(game_type);//开始游戏
    update();*/
}
void MainWindow::blackwin()
{
    statusBar->showMessage("BLACK WIN",5000);
    /*QTimer timer;
    timer.setInterval(5000);
    QObject::connect(&timer,&QTimer::timeout,this,playagain);
    timer.start();*/
   /* game_type=person;
    game->gameStatus=playing;
    game->startGame(game_type);//开始游戏
    update();*/
}
void MainWindow::nonewin()
{
    statusBar->showMessage("NONE WIN",5000);
    /*QTimer timer;
    timer.setInterval(5000);
    QObject::connect(&timer,&QTimer::timeout,this,playagain);
    timer.start();*/
    /*game_type=person;
    game->gameStatus=playing;
    game->startGame(game_type);//开始游戏
    update();*/
}
void MainWindow::initPVCGame()
{
    game_type=bot;
    game->gameStatus=playing;
    game->startGame(game_type);
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{  // 绘制棋盘线条
    QPainter painter(this);
painter.setRenderHint(QPainter::Antialiasing,true);

    painter.save();
drawPlate(painter);
    painter.restore();

    //if(!flag){painter.save();drawInitPosition(painter);painter.restore();flag=1;}

    painter.save();
    drawPiece(painter);
    painter.restore();
}

    //鼠标阴影
    // QBrush brush;
    //  brush.setStyle(Qt::SolidPattern);
    // if(clickPosRow>=0&&clickPosCol>=0&&clickPosCol<=kBoardSize&&clickPosRow<=kBoardSize&&game->gameMap[clickPosRow][clickPosCol]==0)
    //  {
    //      if(game->playerFlag)
    //     {
    //         brush.setColor(Qt::black);
    //     }
    //      else brush.setColor(Qt::white);
    //     painter.setBrush(brush);
    //     painter.drawEllipse(kBoardMargin+kBoardSize*2+kBoardSize*clickPosCol,kBoardMargin+kBoardSize*2+kBoardSize*clickPosRow,kBlockSize/2,kBlockSize/2);
    //  }
    // drawPiece(painter);

    // if(clickPosRow>0&&clickPosRow<kBoardSize&&clickPosCol>0&&clickPosCol<kBoardSize&&game->gameMap[clickPosRow][clickPosCol]==0)
    // {
    //     if(game->playerFlag)
    //         brush.setColor(Qt::white);
    //     else
    //         brush.setColor(Qt::black);
    //     painter.setBrush(brush);
    //     painter.drawRect(kBoardMargin+kBlockSize*clickPosCol-kMarkSize/2,kBoardMargin+kBlockSize*clickPosRow-kMarkSize/2,kMarkSize,kMarkSize);
    // }




    // brush.setColor(Qt::black);
    // painter.setBrush(brush);
    // painter.drawEllipse(kBoardMargin+kBlockSize*j-kRadius,kBoardMargin+kBlockSize*i-kRadius,kRadius*2,kRadius*2);

    // if(clickPosRow>0&&clickPosRow<kBoardSize&&clickPosCol>0&&clickPosCol<kBoardSize&&(game->gameMap[clickPosRow][clickPosCol]==1||game->gameMap[clickPosRow][clickPosCol]==-1))
    // {
    //     if(game->isWin(clickPosRow,clickPosCol)&&game->gameStatus==playing)
    //     {
    //         qDebug()<<"win";
    //         game->gameStatus=win;


    //         QString str;
    //         if(game->gameMap[clickPosRow][clickPosCol]==1)
    //             str="white player";
    //         else if(game->gameMap[clickPosRow][clickPosCol]==-1)
    //             str="black player";
    //         QMessageBox::StandardButton btnValue = QMessageBox::information(this,"congratulations",str+"win");

    //         if(btnValue==QMessageBox::Ok)
    //         {
    //             game->startGame(game_type);
    //             game->gameStatus=playing;
    //         }
    //     }
    // }
    // if(game->isDeadGame())
    // {

    //     QMessageBox::StandardButton btnValue=QMessageBox::information(this,"oops","dead game");
    //     if(btnValue==QMessageBox::Ok)
    //     {
    //         game->startGame(game_type);
    //         game->gameStatus=playing;
    //     }
    // }

void MainWindow::drawPlate(QPainter &painter)
{
    for(int i=0;i<kBoardSize;i++)
    {
        painter.drawLine(kBoardMargin+kBlockSize*(i+2),kBoardMargin+kBlockSize*2,kBoardMargin+kBlockSize*(i+2),kBoardMargin+kBlockSize*7);
        painter.drawLine(kBoardMargin+kBlockSize*2,kBoardMargin+kBlockSize*(i+2),kBoardMargin+kBlockSize*7,kBoardMargin+kBlockSize*(i+2));

    }
    painter.drawPie(kBoardMargin,kBoardMargin,kBlockSize*4,kBlockSize*4,0,4320);
    painter.drawPie(kBoardMargin+kBlockSize,kBoardMargin+kBlockSize,kBlockSize*2,kBlockSize*2,0,4320);

    painter.drawPie(kBoardMargin,kBoardMargin+kBlockSize*5,kBlockSize*4,kBlockSize*4,90*16,4320);
    painter.drawPie(kBoardMargin+kBlockSize,kBoardMargin+kBlockSize*6,kBlockSize*2,kBlockSize*2,90*16,4320);

    painter.drawPie(kBoardMargin+kBlockSize*5,kBoardMargin,kBlockSize*4,kBlockSize*4,(-90)*16,4320);
    painter.drawPie(kBoardMargin+kBlockSize*6,kBoardMargin+kBlockSize,kBlockSize*2,kBlockSize*2,(-90)*16,4320);

    painter.drawPie(kBoardMargin+kBlockSize*5,kBoardMargin+kBlockSize*5,kBlockSize*4,kBlockSize*4,(-180)*16,4320);
    painter.drawPie(kBoardMargin+kBlockSize*6,kBoardMargin+kBlockSize*6,kBlockSize*2,kBlockSize*2,(-180)*16,4320);

}

void MainWindow::drawInitPosition(QPainter &painter)

{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    for(int i=0;i<=5;i++)
        for(int j=0;j<=1;j++)
        {
            brush.setColor(Qt::black);
            painter.setBrush(brush);
            painter.drawEllipse(kBoardMargin+kBlockSize*2+kBlockSize*i-kRadius,kBoardMargin+kBlockSize*2+kBlockSize*j-kRadius,kRadius*2,kRadius*2);
        }
    for(int i=0;i<=5;i++)
        for(int j=0;j<=1;j++)
        {
            brush.setColor(Qt::white);
            painter.setBrush(brush);
            painter.drawEllipse(kBoardMargin+kBlockSize*2+kBlockSize*i-kRadius,kBoardMargin+kBlockSize*2+kBlockSize*(j+4)-kRadius,kRadius*2,kRadius*2);
        }
}

void MainWindow::drawPiece(QPainter &painter)
{
    // if(GameModel::isDeadGame()) return;
    // QColor color;

    QBrush brush;

   brush.setStyle(Qt::SolidPattern);
    for(int i=0;i<kBoardSize;i++)
        for(int j=0;j<kBoardSize;j++)
        {

            if(game->gameMap[i][j]==-1)
            {
                brush.setColor(Qt::black);
                if(select[i][j]==1)
                {
                    brush.setColor(Qt::gray);//鼠标选中的棋子显示黑色
                }
                painter.setBrush(brush);
                painter.drawEllipse(kBoardMargin+kBlockSize*2+kBlockSize*j-kRadius,kBoardMargin+kBlockSize*2+kBlockSize*i-kRadius,kRadius*2,kRadius*2);
                //painter.drawEllipse(kBoardMargin+kBoardSize*2+kBoardSize*j,kBoardMargin+kBoardSize*2+kBoardSize*i,kBlockSize/2,kBlockSize/2);
            }
            else if(game->gameMap[i][j]==1)
            {
                brush.setColor(Qt::white);
                if(select[i][j]==1)
                {
                    brush.setColor(Qt::gray);
                }
                painter.setBrush(brush);
               // painter.drawEllipse(kBoardMargin+kBoardSize*2+kBoardSize*j,kBoardMargin+kBoardSize*2+kBoardSize*i,kBlockSize/2,kBlockSize/2);
                painter.drawEllipse(kBoardMargin+kBlockSize*2+kBlockSize*j-kRadius,kBoardMargin+kBlockSize*2+kBlockSize*i-kRadius,kRadius*2,kRadius*2);
            }

        }
    //select[clickPosRow][clickPosCol]=0;

}
namespace space1
{
int illegalmove = 0;
const int little_round[49] = {1, 6, 7, 8, 9, 10, 11, 4, 10, 16, 22, 28, 34, 29, 28, 27, 26, 25, 24, 31, 25, 19, 13, 7, 1, 6, 7, 8, 9, 10, 11, 4, 10, 16, 22, 28, 34, 29, 28, 27, 26, 25, 24, 31, 25, 19, 13, 7, 1};
const bool little_round_sign[49] = {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0};
const bool little_round_sign_reverse[49] = {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0,0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0};
const int big_round[49] = {2, 12, 13, 14, 15, 16, 17, 3, 9, 15, 21, 27, 33, 23, 22, 21, 20, 19, 18, 32, 26, 20, 14, 8, 2, 12, 13, 14, 15, 16, 17, 3, 9, 15, 21, 27, 33, 23, 22, 21, 20, 19, 18, 32, 26, 20, 14, 8, 2};
const bool big_round_sign[49] = {0,  1, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0};
const bool big_round_sign_reverse[49] = {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0,0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0};
int uid, vid;
int indicator_i, indicator_j, sum;
int mark;
int used[50];

int just_board[6][6];
bool search() {
    for (indicator_i = 0; indicator_i < 49; indicator_i++) {
        if (uid == little_round[indicator_i]) {
            sum = 0;
            for (indicator_j = indicator_i + 1; indicator_j < 49; indicator_j++) {
                sum += little_round_sign[indicator_j];
                if (little_round[indicator_j] == vid) {if (sum > 0)return 1;break;}
                else if (little_round[indicator_j] == uid) {continue;}
                else if (used[little_round[indicator_j]]) {break;}
            }
        }
    }
    for (indicator_i = 48; indicator_i >=0; indicator_i--) {
        if (uid == little_round[indicator_i]) {
            sum = 0;
            for (indicator_j = indicator_i-1; indicator_j >=0; indicator_j--) {
                sum += little_round_sign_reverse[indicator_j];
                if (little_round[indicator_j] == vid) {
                    if (sum > 0)
                        return 1;
                    break;
                } else if (little_round[indicator_j] == uid) {
                    continue;
                } else if (used[little_round[indicator_j]]) {
                    break;
                }
            }
        }
    }
    for (indicator_i = 0; indicator_i < 49; indicator_i++) {
        if (uid == big_round[indicator_i]) {
            sum = 0;
            for (indicator_j = indicator_i + 1; indicator_j < 49; indicator_j++) {
                sum += big_round_sign[indicator_j];
                if (big_round[indicator_j] == vid) {
                    if (sum > 0)
                        return 1;
                    break;
                } else if (big_round[indicator_j] == uid) {
                    continue;
                } else if (used[big_round[indicator_j]]) {
                    break;
                }
            }
        }
    }
    for (indicator_i = 48;indicator_i>=0;indicator_i--) {
        if (uid == big_round[indicator_i]) {
            sum = 0;
            for (indicator_j = indicator_i-1; indicator_j >=0; indicator_j--) {
                sum += big_round_sign_reverse[indicator_j];
                if (big_round[indicator_j] == vid) {
                    if (sum > 0)
                        return 1;
                    break;
                } else if (big_round[indicator_j] == uid) {
                    continue;
                } else if (used[big_round[indicator_j]]) {
                    break;
                }
            }
        }
    }
    return 0;
}
}


bool MainWindow::judge_move(int ux,int uy,int vx,int vy,int now_player){
    if (now_player!=game->playerFlag) return 0;
    if (vx >= 6 || vy >= 6 || ux >= 6 || uy >= 6) {return 0;}

    space1::uid = (ux) * 6 + uy;space1::vid = (vx) * 6 + vy;
    for (int i=0;i<6;i++)
        for (int j=0;j<6;j++) {
            if (game->gameMap[i][j]==0)
                space1::used[i*6+j] = 0;
            else
                space1::used[i*6+j] = 1;
        }
    int vcolor=game->gameMap[vx][vy];
    if (abs(((int)ux - (int)vx) > 1 || abs((int)uy - (int)vy) > 1) && vcolor==0) {return 0;}
    if(now_player==1&&vcolor==1)return 0;
    if(now_player==0&&vcolor==-1)return 0;
    if(vcolor!=0)
    {
        if((space1::search()))return 1;
        else return 0;
    }

    return 1;
}
void MainWindow::judge_end()
{
    int white_sum, black_sum;
    black_sum = 0;
    white_sum = 0;
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            if (game->gameMap[i][j]== -1) black_sum++;
            if (game->gameMap[i][j]== 1)white_sum++;
    }
    if( (black_sum<=0) && game->playerFlag==1){whitewin();}
    if( (white_sum<=0) && game->playerFlag==0){blackwin();}
    if(game->capturesign==0)
    {
        if(game->gameround>40-1+game->lastcaptureround)
        {
            if(white_sum==black_sum)nonewin();
            if(white_sum>black_sum)whitewin();
            if(white_sum<black_sum)blackwin();
        }
    }
    /*if ( (reason != SurakartaIllegalMoveReason::LEGAL_CAPTURE_MOVE) && (reason != SurakartaIllegalMoveReason::LEGAL_NON_CAPTURE_MOVE)) {
        if(current_player==SurakartaPlayer::BLACK)return std::make_pair(SurakartaEndReason::ILLIGAL_MOVE, SurakartaPlayer::WHITE);
        else return std::make_pair(SurakartaEndReason::ILLIGAL_MOVE, SurakartaPlayer::BLACK);
    }*/
    /*if((reason != SurakartaIllegalMoveReason::LEGAL_CAPTURE_MOVE))
    {
        if ((game_info_->num_round_)>game_info_->max_no_capture_round_-1+game_info_->last_captured_round_) {
            if(white_sum==black_sum)return std::make_pair(SurakartaEndReason::STALEMATE, SurakartaPlayer::NONE);
            else if(white_sum>black_sum)return std::make_pair(SurakartaEndReason::STALEMATE, SurakartaPlayer::WHITE);
            else return std::make_pair(SurakartaEndReason::STALEMATE, SurakartaPlayer::BLACK);
        }
    }
    */
}


void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
/*
    int x=event->x();//获取鼠标位置
    int y=event->y();


    if(x>=kBoardMargin+kBlockSize/2+kBlockSize*2&&x<kBoardMargin+kBlockSize*7&&y>=kBoardMargin+kBlockSize/2+kBlockSize*2&&y<kBoardMargin+kBlockSize*7)
    {
        int col=x-kBlockSize*2-kBoardMargin/kBlockSize;//列 x
        int row=y-kBlockSize*2-kBoardMargin/kBlockSize;//行  y 从0-5
//鼠标最近左上角的xy坐标
        int leftTopPosX=kBoardMargin+kBlockSize*2+kBlockSize*col;
        int leftTopPosY=kBoardMargin+kBlockSize*2+kBlockSize*row;
//设初值
        clickPosRow=-1;
        clickPosCol=-1;
        int len=0;
        selectPos=false;
//计算鼠标和点的距离 判断鼠标要点哪个点
        len=sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
        if(len<kPosDelta)
        {
            clickPosRow = row;
            clickPosCol = col;
            if(game->gameMap[clickPosRow][clickPosCol]==0)
            {
                selectPos=true;
            }
        }
        len=sqrt((x - leftTopPosX - kBlockSize) * (x - leftTopPosX - kBlockSize) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < kPosDelta)
        {
            clickPosRow = row ;
            clickPosCol = col + 1;
            if(game->gameMap[clickPosRow][clickPosCol]==0)
            {
                selectPos=true;
            }
        }
        len=sqrt((x-leftTopPosX)*(x-leftTopPosX)+(y-leftTopPosY-kBlockSize)*(y-leftTopPosY-kBlockSize));
        if(len<kPosDelta)
        {
            clickPosRow=row+1;
            clickPosCol=col;
            if(game->gameMap[clickPosRow][clickPosCol]==0)
            {
                selectPos=true;
            }
        }
        len=sqrt((x-leftTopPosX-kBlockSize)*(x-leftTopPosX-kBlockSize)+(y-leftTopPosY-kBlockSize)*(y-leftTopPosY-kBlockSize));
        if(len<kPosDelta)
        {
            clickPosRow=row+1;
            clickPosCol=col+1;
            if(game->gameMap[clickPosRow][clickPosCol]==0)
            {
                selectPos=true;
            }
        }

    }

    update();//更新界面 重新调用paintevent
*/
}



int clickId=6;
bool piece_clicked=0;
bool click_color=1;
bool beinside(int x,int y)
{
    if(x>=kBoardMargin-kBlockSize/2+kBlockSize*2&&
        x<kBoardMargin+kBlockSize*7&&
        y>=kBoardMargin-kBlockSize/2+kBlockSize*2&&
        y<kBoardMargin+kBlockSize*7)
        return 1;
    else return 0;
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)//鼠标松开时的实现
{
    //select[0][0]=1;
    //update();
    //
    QLabel *aixLabel=new QLabel("AIX",this);

    int x=event->x();//获取鼠标位置
    int y=event->y();
    int selectId=-1;//
    if(!beinside(x,y))return;

        int col=(x-kBlockSize*2-kBoardMargin)/kBlockSize;//列 x
        int row=(y-kBlockSize*2-kBoardMargin)/kBlockSize;//行  y 从0-5
        //鼠标最近左上角的xy坐标
        int leftTopPosX=kBoardMargin+kBlockSize*2+kBlockSize*col;
        int leftTopPosY=kBoardMargin+kBlockSize*2+kBlockSize*row;
        //设初值
        clickPosRow=-1;
        clickPosCol=-1;
        //int clickId=-1;
        int len=0;
        selectPos=false;
        bool have_position=0;

        //计算鼠标和点的距离 判断鼠标要点哪个点
        len=sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
        if(len<kPosDelta)
        {
            clickPosRow = row;clickPosCol = col;
            if(game->gameMap[clickPosRow][clickPosCol]!=0)selectPos=true;
            have_position=1;
        }
        len=sqrt((x - leftTopPosX - kBlockSize) * (x - leftTopPosX - kBlockSize) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < kPosDelta)
        {
            clickPosRow = row ;clickPosCol = col + 1;
            if(game->gameMap[clickPosRow][clickPosCol]!=0)selectPos=true;
            have_position=1;

        }
        len=sqrt((x-leftTopPosX)*(x-leftTopPosX)+(y-leftTopPosY-kBlockSize)*(y-leftTopPosY-kBlockSize));
        if(len<kPosDelta)
        {
            clickPosRow=row+1;clickPosCol=col;
            if(game->gameMap[clickPosRow][clickPosCol]!=0)selectPos=true;
            have_position=1;

        }
        len=sqrt((x-leftTopPosX-kBlockSize)*(x-leftTopPosX-kBlockSize)+(y-leftTopPosY-kBlockSize)*(y-leftTopPosY-kBlockSize));
        if(len<kPosDelta)
        {
            clickPosRow=row+1;clickPosCol=col+1;
            if(game->gameMap[clickPosRow][clickPosCol]!=0)selectPos=true;
            have_position=1;
        }
        if(!have_position)return;




    //if(selectPos==false)return;
    //鼠标没有选中任何棋子


    //    clickId=clickPosRow*6+clickPosCol;//鼠标选中棋子的id

     //选中棋子

        //select[clickPosRow][clickPosCol]=0;
        if((!piece_clicked)&&(game->gameMap[clickPosRow][clickPosCol]!=0))//鼠标选中了棋子
        {
            //selectId=clickId;//选中棋子Id赋值


            piece_clicked=1;
            if(game->gameMap[clickPosRow][clickPosCol]==1)click_color=1;
            else click_color=0;
            selectPosRow=clickPosRow;
            selectPosCol=clickPosCol;
            select[selectPosRow][selectPosCol]=1;
            update();
            //statusBar->showMessage("Rounds:",game->gameround);
           // statusBar->showMessage("Player:",game->playerFlag);
           // select[clickPosRow][clickPosCol]=1;
           // update();

            // if(game->isDeadGame())
            // {
            //     statusBar->setStyleSheet(QString("QStatusBar::item{border: 0px}")); // 设置不显示label的边框
            //     statusBar->setSizeGripEnabled(false); //设置是否显示右边的大小控制点
            //     statusBar->addWidget(locationLabel);
            //     statusBar->addWidget(aixLabel, 1);
            //     statusBar->showMessage("stalemate, game over!", 3000); // 显示临时信息，时间3秒钟.
            // //    statusBar->showMessage("Rounds:",game_info_->num_round_, 3000);
            // //    statusBar->showMessage("Winner:",game_info_->winner_, 3000);
            // }
            // else if (game->isWin(selectPosRow, selectPosCol))
            // {
            //     statusBar->setStyleSheet(QString("QStatusBar::item{border: 0px}")); // 设置不显示label的边框
            //     statusBar->setSizeGripEnabled(false); //设置是否显示右边的大小控制点
            //     statusBar->addWidget(locationLabel);
            //     statusBar->addWidget(aixLabel, 1);
            //     statusBar->showMessage("checkmate, game over!", 3000); // 显示临时信息，时间3秒钟.
            // //    statusBar->showMessage("Rounds:",game_info_->num_round_, 3000);
            // //    statusBar->showMessage("Winner:",game_info_->winner_, 3000);
            // }
        }

    else//移动已被选中的棋子 （clickId为棋子to的位置
    {
        if(!piece_clicked)
            {
                select[selectPosRow][selectPosCol]=0;
                update();
            }
        piece_clicked=0;
        /*SurakartaPosition SurclickPos(clickPosRow,clickPosCol);
        SurakartaPosition SurselectPos(selectPosRow,selectPosCol);
        SurakartaPlayer Splayer=SurakartaPlayer::NONE;

        if(game->playerFlag){ Splayer=SurakartaPlayer::BLACK;}
        else { Splayer=SurakartaPlayer::WHITE;}
        SurakartaMove move(SurselectPos,SurclickPos,Splayer);

        SurakartaIllegalMoveReason move_reason = rule_manager_.JudgeMove(move);*/
        if(!judge_move(selectPosRow,selectPosCol,clickPosRow,clickPosCol,click_color))
        {
            select[selectPosRow][ selectPosCol]=0;
            update();
            return ;
        }
        if(game->gameMap[clickPosRow][clickPosCol]==0)game->capturesign=0;
        else game->capturesign=1;
            game->gameMap[clickPosRow][clickPosCol]=game->gameMap[selectPosRow][selectPosCol];
            game->gameMap[selectPosRow][selectPosCol]=0;
            select[selectPosRow][selectPosCol]=0;
            if(game->capturesign)game->lastcaptureround=game->gameround;
            update();
            judge_end();
            game->updateGame();
            //statusBar->showMessage(Qstring("gameround: %1").arg(game->gameround));

/*
        if(move_reason==SurakartaIllegalMoveReason::LEGAL_CAPTURE_MOVE||
            move_reason==SurakartaIllegalMoveReason::LEGAL_NON_CAPTURE_MOVE||move_reason==SurakartaIllegalMoveReason::LEGAL)
        {
            selectId=clickId;
            //select为from_position click为to_position
            game->gameMap[clickPosRow][clickPosCol]=game->gameMap[selectPosRow][selectPosCol];
            game->gameMap[selectPosRow][selectPosCol]=0;
        }
        else
        {
            statusBar->setStyleSheet(QString("QStatusBar::item{border: 0px}")); // 设置不显示label的边框
            statusBar->setSizeGripEnabled(false); //设置是否显示右边的大小控制点
            statusBar->addWidget(locationLabel);
            statusBar->addWidget(aixLabel, 1);
            statusBar->showMessage("illegal move, game over!", 3000); // 显示临时信息，时间3秒钟.
            //statusBar->showMessage("Rounds:",game->game_info_->num_round_, 3000);
            //statusBar->showMessage("Winner:",game_info_->winner_, 3000);

        }
*/
       // selectId=-1;
        //clickId=6;

        // if(clickId!=-1)//棋子移动到的地方有棋子
        // {
        //     p[clickId].dead=true;//棋子被吃
        // }

    }

    // 人下棋，并且不能抢机器的棋
    /*
    if (!(game_type == bot && !game->playerFlag))
    {
        chessOneByPerson();
        // 如果是人机模式，需要调用AI下棋
        if (game->gameType == bot && !game->playerFlag)
        {
            // 用定时器做一个延迟
            QTimer::singleShot(kAIDelay, this, SLOT(chessOneByAi()));
        }
    }
*/

}

void MainWindow::chessOneByPerson()
{
    if(clickPosRow!=-1&&clickPosCol!=-1&&game->gameMap[clickPosRow][clickPosCol]==0)
    {
        game->actionByPerson(clickPosRow,clickPosCol);//落子 在里实现

        update();//重绘
    }
}

void MainWindow::chessOneByAi()
{
    game->actionByAi(clickPosRow,clickPosCol);

    update();
}
