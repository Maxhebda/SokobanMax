#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // --------------------------- basic bacgroud --------------------
    image = new QImage(15*48,13*48,QImage::Format_RGB32);
    image->fill(QColor(180,180,170));
    paintOnImage = new QPainter;
    paintOnImage->begin(image);

    // ------------------------ shortcut keyboard --------------------
    shUP    = new QShortcut(QKeySequence(Qt::Key_Up),this,SLOT(clickUP()));
    shDOWN  = new QShortcut(QKeySequence(Qt::Key_Down),this,SLOT(clickDOWN()));
    shRIGHT    = new QShortcut(QKeySequence(Qt::Key_Right),this,SLOT(clickRIGHT()));
    shLEFT  = new QShortcut(QKeySequence(Qt::Key_Left),this,SLOT(clickLEFT()));

    connect(ui->actionStart,SIGNAL(triggered()),this,SLOT(clickStart()));
    myBoard.load();
    showBoard();
}

MainWindow::~MainWindow()
{
    delete ui;
    paintOnImage->end();
    delete image;
    delete paintOnImage;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(10,10 + ui->menubar->height(),*image);
    painter.end();
}

void MainWindow::showBoard()
{
    paintOnImage->fillRect(QRect(0,0,15*48,13*48),QColor(180,180,170));
    QRectF source(0, 0, 47, 47);
    for (unsigned short int y=0; y<13; y++)
    {
        for (unsigned short int x=0; x<15; x++)
        {
            switch (myBoard.get(y,x)) {
                case OneCell::CELL_EMPTY:
                {
                    break;
                }
                case OneCell::CELL_WALL:
                {
                    paintOnImage->drawImage(QRectF(x*48,y*48,48,48),QImage(":/img/wall.png"),source);
                    break;
                }
                case OneCell::CELL_DOOR:
                {
                    paintOnImage->drawImage(QRectF(x*48,y*48,48,48),QImage(":/img/door.png"),source);
                    break;
                }
                case OneCell::CELL_STEVE:
                {
                    paintOnImage->drawImage(QRectF(x*48,y*48,48,48),QImage(":/img/steve.png"),source);
                    break;
                }
                case OneCell::CELL_HOLE:
                {
                    paintOnImage->drawImage(QRectF(x*48,y*48,48,48),QImage(":/img/hole.png"),source);
                    break;
                }
                case OneCell::CELL_DIAMOND:
                {
                    paintOnImage->drawImage(QRectF(x*48,y*48,48,48),QImage(":/img/diamond.png"),source);
                    break;
                }
                case OneCell::CELL_DIAMONDinHOLE:
                {
                    paintOnImage->drawImage(QRectF(x*48,y*48,48,48),QImage(":/img/diamondHole.png"),source);
                    break;
                }
                case OneCell::CELL_STEVEinHOLE:
                {
                    paintOnImage->drawImage(QRectF(x*48,y*48,48,48),QImage(":/img/steveHole.png"),source);
                    break;
                }
                case OneCell::CELL_ARROW_UP:
                {
                    paintOnImage->drawImage(QRectF(x*48,y*48,48,48),QImage(":/img/arrowUp.png"),source);
                    break;
                }
                case OneCell::CELL_ARROW_DOWN:
                {
                    paintOnImage->drawImage(QRectF(x*48,y*48,48,48),QImage(":/img/arrowDown.png"),source);
                    break;
                }
                case OneCell::CELL_ARROW_LEFT:
                {
                    paintOnImage->drawImage(QRectF(x*48,y*48,48,48),QImage(":/img/arrowLeft.png"),source);
                    break;
                }
                case OneCell::CELL_ARROW_RIGHT:
                {
                    paintOnImage->drawImage(QRectF(x*48,y*48,48,48),QImage(":/img/arrorRight.png"),source);
                    break;
                }
            }
        }
    }
    repaint();
}

void MainWindow::clickStart()
{
    myBoard.load();
    showBoard();
    repaint();
}

void MainWindow::clickDOWN()
{
    unsigned short int steveX = myBoard.pos_Steve_x;
    unsigned short int steveY = myBoard.pos_Steve_y;
        //steve and empty
        if (myBoard.get(steveY+1,steveX)==OneCell::CELL_EMPTY)
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(steveY+1,steveX,OneCell::CELL_STEVE);
        }
        //steve and hole
        else if (myBoard.get(steveY+1,steveX)==OneCell::CELL_HOLE)
        {
            myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
            myBoard.set(steveY+1,steveX,OneCell::CELL_STEVEinHOLE);
        }
        //steve and door and teleport=empty/hole
        else if (myBoard.get(steveY+1,steveX)==OneCell::CELL_DOOR && (myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_EMPTY || myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_HOLE))
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x,(myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_EMPTY)?OneCell::CELL_STEVE:OneCell::CELL_STEVEinHOLE);
        }
        //steve and diamodn and empty
        else if ((myBoard.get(steveY+1,steveX)==OneCell::CELL_DIAMOND || myBoard.get(steveY+1,steveX)==OneCell::CELL_DIAMONDinHOLE) && myBoard.get(steveY+2,steveX)==OneCell::CELL_EMPTY)
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(steveY+2,steveX,OneCell::CELL_DIAMOND);
             myBoard.set(steveY+1,steveX,(myBoard.get(steveY+1,steveX)==OneCell::CELL_DIAMOND)?OneCell::CELL_STEVE:OneCell::CELL_STEVEinHOLE);
        }
        //steve and diamodn/diamondHole and hole
        else if ((myBoard.get(steveY+1,steveX)==OneCell::CELL_DIAMOND || myBoard.get(steveY+1,steveX)==OneCell::CELL_DIAMONDinHOLE) && myBoard.get(steveY+2,steveX)==OneCell::CELL_HOLE)
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(steveY+2,steveX,OneCell::CELL_DIAMONDinHOLE);
             myBoard.set(steveY+1,steveX,(myBoard.get(steveY+1,steveX)==OneCell::CELL_DIAMOND)?OneCell::CELL_STEVE:OneCell::CELL_STEVEinHOLE);
        }
        //*steve and diamond/diamondHole and door and teleport=empty/hole
        else if ((myBoard.get(steveY+1,steveX)==OneCell::CELL_DIAMOND || myBoard.get(steveY+1,steveX)==OneCell::CELL_DIAMONDinHOLE) && myBoard.get(steveY+2,steveX)==OneCell::CELL_DOOR && (myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_EMPTY || myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_HOLE))
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x,(myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_EMPTY)?OneCell::CELL_DIAMOND:OneCell::CELL_DIAMONDinHOLE);
             myBoard.set(steveY+1,steveX,(myBoard.get(steveY+1,steveX)==OneCell::CELL_DIAMOND)?OneCell::CELL_STEVE:OneCell::CELL_STEVEinHOLE);
        }
        //steve and door and teleport=diamond and empty
        else if (myBoard.get(steveY+1,steveX)==OneCell::CELL_DOOR && myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_DIAMOND && myBoard.get(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next)==OneCell::CELL_EMPTY)
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next,OneCell::CELL_DIAMOND);
             myBoard.set(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x,OneCell::CELL_STEVE);
        }
    showBoard();
}

void MainWindow::clickUP()
{
    unsigned short int steveX = myBoard.pos_Steve_x;
    unsigned short int steveY = myBoard.pos_Steve_y;
        //steve and empty
        if (myBoard.get(steveY-1,steveX)==OneCell::CELL_EMPTY)
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(steveY-1,steveX,OneCell::CELL_STEVE);
        }
        //steve and hole
        else if (myBoard.get(steveY-1,steveX)==OneCell::CELL_HOLE)
        {
            myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
            myBoard.set(steveY-1,steveX,OneCell::CELL_STEVEinHOLE);
        }
        //steve and door and teleport=empty/hole
        else if (myBoard.get(steveY-1,steveX)==OneCell::CELL_DOOR && (myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_EMPTY || myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_HOLE))
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x,(myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_EMPTY)?OneCell::CELL_STEVE:OneCell::CELL_STEVEinHOLE);
        }
        //steve and diamodn and empty
        else if ((myBoard.get(steveY-1,steveX)==OneCell::CELL_DIAMOND || myBoard.get(steveY-1,steveX)==OneCell::CELL_DIAMONDinHOLE) && myBoard.get(steveY-2,steveX)==OneCell::CELL_EMPTY)
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(steveY-2,steveX,OneCell::CELL_DIAMOND);
             myBoard.set(steveY-1,steveX,(myBoard.get(steveY-1,steveX)==OneCell::CELL_DIAMOND)?OneCell::CELL_STEVE:OneCell::CELL_STEVEinHOLE);
        }
        //steve and diamodn/diamondHole and hole
        else if ((myBoard.get(steveY-1,steveX)==OneCell::CELL_DIAMOND || myBoard.get(steveY-1,steveX)==OneCell::CELL_DIAMONDinHOLE) && myBoard.get(steveY-2,steveX)==OneCell::CELL_HOLE)
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(steveY-2,steveX,OneCell::CELL_DIAMONDinHOLE);
             myBoard.set(steveY-1,steveX,(myBoard.get(steveY-1,steveX)==OneCell::CELL_DIAMOND)?OneCell::CELL_STEVE:OneCell::CELL_STEVEinHOLE);
        }
        //steve and diamond/diamondHole and door and teleport=empty/hole
        else if ((myBoard.get(steveY-1,steveX)==OneCell::CELL_DIAMOND || myBoard.get(steveY-1,steveX)==OneCell::CELL_DIAMONDinHOLE) && myBoard.get(steveY-2,steveX)==OneCell::CELL_DOOR && (myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_EMPTY || myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_HOLE))
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x,(myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_EMPTY)?OneCell::CELL_DIAMOND:OneCell::CELL_DIAMONDinHOLE);
             myBoard.set(steveY-1,steveX,(myBoard.get(steveY-1,steveX)==OneCell::CELL_DIAMOND)?OneCell::CELL_STEVE:OneCell::CELL_STEVEinHOLE);
        }
        //steve and door and teleport=diamond and empty
        else if (myBoard.get(steveY-1,steveX)==OneCell::CELL_DOOR && myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_DIAMOND && myBoard.get(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next)==OneCell::CELL_EMPTY)
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next,OneCell::CELL_DIAMOND);
             myBoard.set(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x,OneCell::CELL_STEVE);
        }
    showBoard();
}

void MainWindow::clickLEFT()
{
    unsigned short int steveX = myBoard.pos_Steve_x;
    unsigned short int steveY = myBoard.pos_Steve_y;
        //steve and empty
        if (myBoard.get(steveY,steveX-1)==OneCell::CELL_EMPTY)
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(steveY,steveX-1,OneCell::CELL_STEVE);
        }
        //steve and hole
        else if (myBoard.get(steveY,steveX-1)==OneCell::CELL_HOLE)
        {
            myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
            myBoard.set(steveY,steveX-1,OneCell::CELL_STEVEinHOLE);
        }
        //steve and door and teleport=empty/hole
        else if (myBoard.get(steveY,steveX-1)==OneCell::CELL_DOOR && (myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_EMPTY || myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_HOLE))
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x,(myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_EMPTY)?OneCell::CELL_STEVE:OneCell::CELL_STEVEinHOLE);
        }
        //steve and diamodn and empty
        else if ((myBoard.get(steveY,steveX-1)==OneCell::CELL_DIAMOND || myBoard.get(steveY,steveX-1)==OneCell::CELL_DIAMONDinHOLE) && myBoard.get(steveY,steveX-2)==OneCell::CELL_EMPTY)
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(steveY,steveX-2,OneCell::CELL_DIAMOND);
             myBoard.set(steveY,steveX-1,(myBoard.get(steveY,steveX-1)==OneCell::CELL_DIAMOND)?OneCell::CELL_STEVE:OneCell::CELL_STEVEinHOLE);
        }
        //steve and diamodn/diamondHole and hole
        else if ((myBoard.get(steveY,steveX-1)==OneCell::CELL_DIAMOND || myBoard.get(steveY,steveX-1)==OneCell::CELL_DIAMONDinHOLE) && myBoard.get(steveY,steveX-2)==OneCell::CELL_HOLE)
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(steveY,steveX-2,OneCell::CELL_DIAMONDinHOLE);
             myBoard.set(steveY,steveX-1,(myBoard.get(steveY,steveX-1)==OneCell::CELL_DIAMOND)?OneCell::CELL_STEVE:OneCell::CELL_STEVEinHOLE);
        }
        //steve and diamond/diamondHole and door and teleport=empty/hole
        else if ((myBoard.get(steveY,steveX-1)==OneCell::CELL_DIAMOND || myBoard.get(steveY,steveX-1)==OneCell::CELL_DIAMONDinHOLE) && myBoard.get(steveY,steveX-2)==OneCell::CELL_DOOR && (myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_EMPTY || myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_HOLE))
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x,(myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_EMPTY)?OneCell::CELL_DIAMOND:OneCell::CELL_DIAMONDinHOLE);
             myBoard.set(steveY,steveX-1,(myBoard.get(steveY,steveX-1)==OneCell::CELL_DIAMOND)?OneCell::CELL_STEVE:OneCell::CELL_STEVEinHOLE);
        }
        //steve and door and teleport=diamond and empty
        else if (myBoard.get(steveY,steveX-1)==OneCell::CELL_DOOR && myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_DIAMOND && myBoard.get(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next)==OneCell::CELL_EMPTY)
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next,OneCell::CELL_DIAMOND);
             myBoard.set(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x,OneCell::CELL_STEVE);
        }
    showBoard();
}

void MainWindow::clickRIGHT()
{
    unsigned short int steveX = myBoard.pos_Steve_x;
    unsigned short int steveY = myBoard.pos_Steve_y;
        //steve and empty
        if (myBoard.get(steveY,steveX+1)==OneCell::CELL_EMPTY)
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(steveY,steveX+1,OneCell::CELL_STEVE);
        }
        //steve and hole
        else if (myBoard.get(steveY,steveX+1)==OneCell::CELL_HOLE)
        {
            myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
            myBoard.set(steveY,steveX+1,OneCell::CELL_STEVEinHOLE);
        }
        //steve and door and teleport=empty/hole
        else if (myBoard.get(steveY,steveX+1)==OneCell::CELL_DOOR && (myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_EMPTY || myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_HOLE))
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x,(myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_EMPTY)?OneCell::CELL_STEVE:OneCell::CELL_STEVEinHOLE);
        }
        //steve and diamodn and empty
        else if ((myBoard.get(steveY,steveX+1)==OneCell::CELL_DIAMOND || myBoard.get(steveY,steveX+1)==OneCell::CELL_DIAMONDinHOLE) && myBoard.get(steveY,steveX+2)==OneCell::CELL_EMPTY)
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(steveY,steveX+2,OneCell::CELL_DIAMOND);
             myBoard.set(steveY,steveX+1,(myBoard.get(steveY,steveX+1)==OneCell::CELL_DIAMOND)?OneCell::CELL_STEVE:OneCell::CELL_STEVEinHOLE);
        }
        //steve and diamodn/diamondHole and hole
        else if ((myBoard.get(steveY,steveX+1)==OneCell::CELL_DIAMOND || myBoard.get(steveY,steveX+1)==OneCell::CELL_DIAMONDinHOLE) && myBoard.get(steveY,steveX+2)==OneCell::CELL_HOLE)
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(steveY,steveX+2,OneCell::CELL_DIAMONDinHOLE);
             myBoard.set(steveY,steveX+1,(myBoard.get(steveY,steveX+1)==OneCell::CELL_DIAMOND)?OneCell::CELL_STEVE:OneCell::CELL_STEVEinHOLE);
        }
        //steve and diamond/diamondHole and door and teleport=empty/hole
        else if ((myBoard.get(steveY,steveX+1)==OneCell::CELL_DIAMOND || myBoard.get(steveY,steveX+1)==OneCell::CELL_DIAMONDinHOLE) && myBoard.get(steveY,steveX+2)==OneCell::CELL_DOOR && (myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_EMPTY || myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_HOLE))
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x,(myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_EMPTY)?OneCell::CELL_DIAMOND:OneCell::CELL_DIAMONDinHOLE);
             myBoard.set(steveY,steveX+1,(myBoard.get(steveY,steveX+1)==OneCell::CELL_DIAMOND)?OneCell::CELL_STEVE:OneCell::CELL_STEVEinHOLE);
        }
        //steve and door and teleport=diamond and empty
        else if (myBoard.get(steveY,steveX+1)==OneCell::CELL_DOOR && myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_DIAMOND && myBoard.get(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next)==OneCell::CELL_EMPTY)
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next,OneCell::CELL_DIAMOND);
             myBoard.set(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x,OneCell::CELL_STEVE);
        }
    showBoard();
}
