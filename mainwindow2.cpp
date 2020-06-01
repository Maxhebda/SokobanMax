#include "mainwindow2.h"
#include "ui_mainwindow2.h"

MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{
    ui->setupUi(this);
    // --------------------------- basic bacgroud --------------------
    image = new QImage(15*48+16,13*48+14+60,QImage::Format_RGB32);   // 15 (+16) x 13 (+14 +60)
    image->fill(QColor(180,180,170));
    paintOnImage = new QPainter;
    paintOnImage->begin(image);

    // ------------------------ connect menu -------------------------
    connect(ui->actionWype_nij_cian,SIGNAL(triggered()),this,SLOT(clickFillWall()));
    connect(ui->actionWype_nij_pustym_blokiem,SIGNAL(triggered()),this,SLOT(clickFillEmpty()));
    connect(ui->actionPusta_ramka,SIGNAL(triggered()),this,SLOT(clickFillEmptyFrame()));
    connect(ui->actionPusty_rodek,SIGNAL(triggered()),this,SLOT(clickFillEmptyCenter()));
    connect(ui->actionMa_a_pusta_ramka,SIGNAL(triggered()),this,SLOT(clickFillSmallEmptyFrame()));

    myEditorBoard.clearToWall();
    showEditorBoard();
}

MainWindow2::~MainWindow2()
{
    delete ui;
}

void MainWindow2::paintEvent(QPaintEvent *e)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(10,10 + ui->menubar->height(),*image);
    painter.end();
}

void MainWindow2::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
//        if (event->x()<20)
//            ui->menuPlik->setTitle("tera");
    }
}

void MainWindow2::clickFillWall()
{
    myEditorBoard.clearToWall();
    showEditorBoard();
}

void MainWindow2::clickFillEmpty()
{
    myEditorBoard.clear();
    showEditorBoard();
}

void MainWindow2::clickFillEmptyFrame()
{
    for (unsigned short int y=0; y<13; y++)
    {
        for (unsigned short int x=0; x<15; x++)
        {
            if (y>0 && y<12 && x>0 && x<14)
            {
               myEditorBoard.set(y,x,OneCell::CELL_EMPTY);
            }
            else
            {
                myEditorBoard.set(y,x,OneCell::CELL_WALL);
            }

        }
    }
    showEditorBoard();
}

void MainWindow2::clickFillEmptyCenter()
{
    for (unsigned short int y=0; y<13; y++)
    {
        for (unsigned short int x=0; x<15; x++)
        {
            if (y>2 && y<10 && x>3 && x<11)
            {
               myEditorBoard.set(y,x,OneCell::CELL_EMPTY);
            }
            else
            {
                myEditorBoard.set(y,x,OneCell::CELL_WALL);
            }

        }
    }
    showEditorBoard();
}

void MainWindow2::clickFillSmallEmptyFrame()
{
    for (unsigned short int y=0; y<13; y++)
    {
        for (unsigned short int x=0; x<15; x++)
        {
            if ((y==3 && x>3 && x<11)||(y==9 && x>3 && x<11)||(x==4 && y>3 && y<9)||(x==10 && y>3 && y<9))
            {
               myEditorBoard.set(y,x,OneCell::CELL_WALL);
            }
            else
            {
                myEditorBoard.set(y,x,OneCell::CELL_EMPTY);
            }

        }
    }
    showEditorBoard();
}

void MainWindow2::showEditorBoard()
{
    const unsigned short int position_board=60;
    paintOnImage->fillRect(QRect(0,0,15*48+16,position_board),QColor(255,180,170));
    paintOnImage->fillRect(QRect(0,position_board,15*48+16,13*48+14+position_board),QColor(180,180,170));
    QRectF source(0, 0, 47, 47);

    //-------------------------- drawing a grid --------------------------
    paintOnImage->setPen(QColor(0,0,0));
    for (unsigned short int y=0; y<14; y++)
    {
        paintOnImage->drawLine(0,y*49+position_board,15*48+16,y*49+position_board);
    }
    for (unsigned short int x=0; x<16; x++)
    {
        paintOnImage->drawLine(x*49,position_board,x*49,13*48+14+position_board);
    }

    //----------------------- drawing a menu grid ------------------------
    paintOnImage->setPen(QColor(255,215,215));
    for (unsigned short int a=0; a<2; a++)
    {
        paintOnImage->drawLine(32,a*51+3,32+10*48+32,a*51+3);
        paintOnImage->drawLine(32,a*51+4,32+10*48+32,a*51+4);
        paintOnImage->drawLine(32,a*51+5,32+10*48+32,a*51+5);
    }
    for (unsigned short int a=0; a<11; a++)
    {
        paintOnImage->drawLine(32+51*a,5,32+51*a,54);
        paintOnImage->drawLine(33+51*a,5,33+51*a,54);
        paintOnImage->drawLine(34+51*a,5,34+51*a,54);
    }

    //----------------------- drawing a menu object ----------------------
    paintOnImage->drawImage(QRectF(35     ,6,48,48),QImage(":/img/wall.png"),source);
    paintOnImage->drawImage(QRectF(35+51*2,6,48,48),QImage(":/img/door.png"),source);
    paintOnImage->drawImage(QRectF(35+51*3,6,48,48),QImage(":/img/steve.png"),source);
    paintOnImage->drawImage(QRectF(35+51*4,6,48,48),QImage(":/img/hole.png"),source);
    paintOnImage->drawImage(QRectF(35+51*5,6,48,48),QImage(":/img/diamond.png"),source);
    paintOnImage->drawImage(QRectF(35+51*6,6,48,48),QImage(":/img/arrowUp.png"),source);
    paintOnImage->drawImage(QRectF(35+51*7,6,48,48),QImage(":/img/arrowDown.png"),source);
    paintOnImage->drawImage(QRectF(35+51*8,6,48,48),QImage(":/img/arrowLeft.png"),source);
    paintOnImage->drawImage(QRectF(35+51*9,6,48,48),QImage(":/img/arrorRight.png"),source);

    for (unsigned short int y=0; y<13; y++)
    {
        for (unsigned short int x=0; x<15; x++)
        {
            switch (myEditorBoard.get(y,x)) {
                case OneCell::CELL_EMPTY:
                {
                    break;
                }
                case OneCell::CELL_WALL:
                {
                    paintOnImage->drawImage(QRectF(x*49+1,y*49+1+position_board,48,48),QImage(":/img/wall.png"),source);
                    break;
                }
                case OneCell::CELL_DOOR:
                {
                    paintOnImage->drawImage(QRectF(x*49+1,y*49+1+position_board,48,48),QImage(":/img/door.png"),source);
                    break;
                }
                case OneCell::CELL_STEVE:
                {
                    paintOnImage->drawImage(QRectF(x*49+1,y*49+1+position_board,48,48),QImage(":/img/steve.png"),source);
                    break;
                }
                case OneCell::CELL_HOLE:
                {
                    paintOnImage->drawImage(QRectF(x*49+1,y*49+1+position_board,48,48),QImage(":/img/hole.png"),source);
                    break;
                }
                case OneCell::CELL_DIAMOND:
                {
                    paintOnImage->drawImage(QRectF(x*49+1,y*49+1+position_board,48,48),QImage(":/img/diamond.png"),source);
                    break;
                }
                case OneCell::CELL_DIAMONDinHOLE:
                {
                    paintOnImage->drawImage(QRectF(x*49+1,y*49+1+position_board,48,48),QImage(":/img/diamondHole.png"),source);
                    break;
                }
                case OneCell::CELL_STEVEinHOLE:
                {
                    paintOnImage->drawImage(QRectF(x*49+1,y*49+1+position_board,48,48),QImage(":/img/steveHole.png"),source);
                    break;
                }
                case OneCell::CELL_ARROW_UP:
                {
                    paintOnImage->drawImage(QRectF(x*49+1,y*49+1+position_board,48,48),QImage(":/img/arrowUp.png"),source);
                    break;
                }
                case OneCell::CELL_ARROW_DOWN:
                {
                    paintOnImage->drawImage(QRectF(x*49+1,y*49+1+position_board,48,48),QImage(":/img/arrowDown.png"),source);
                    break;
                }
                case OneCell::CELL_ARROW_LEFT:
                {
                    paintOnImage->drawImage(QRectF(x*49+1,y*49+1+position_board,48,48),QImage(":/img/arrowLeft.png"),source);
                    break;
                }
                case OneCell::CELL_ARROW_RIGHT:
                {
                    paintOnImage->drawImage(QRectF(x*49+1,y*49+1+position_board,48,48),QImage(":/img/arrorRight.png"),source);
                    break;
                }
            }
        }
    }
    repaint();
}
