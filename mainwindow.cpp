#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QFont>

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
    shSPACE  = new QShortcut(QKeySequence(Qt::Key_Space),this,SLOT(clickSPACE()));

    // ------------------------ connect menu -------------------------
    connect(ui->actionStart,SIGNAL(triggered()),this,SLOT(clickStart()));
    connect(ui->actionEdytor_Plansz,SIGNAL(triggered()),this,SLOT(clickBoardsEditor()));

    addMenuLevel();
    showBoard();
}

MainWindow::~MainWindow()
{
    delete ui;
    paintOnImage->end();
    delete image;
    delete paintOnImage;
    for (unsigned short int i=0;i<LEVEL_BASIC;i++)
    {
        delete levelBasicAction[i];
    }
    delete mainWindow2;
}

void MainWindow::addMenuLevel()
{
    char tmp[8];
    for (unsigned short int i=0;i<LEVEL_BASIC;i++)
    {
        sprintf(tmp,"Level %d",i);
        levelBasicAction[i] = new QAction(tmp,this);
        levelBasicAction[i]->setCheckable(true);
        sprintf(tmp,"%d",i);
        levelBasicAction[i]->setObjectName(tmp);
        ui->menuPodstawowe->addAction(levelBasicAction[i]);
        connect(levelBasicAction[i],SIGNAL(triggered()),this,SLOT(clickLevelBasic()));
    }
    levelBasicAction[0]->setChecked(true);  //selected first level
    numberOfLevel=0;
    myBoard.load(Levels::basicLevel(numberOfLevel));
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
    if (myBoard.isWin())
    {
        QFont font;
        font.setPixelSize(30);
        font.setBold(true);
        paintOnImage->setFont(font);
        paintOnImage->drawText(280,310,"Gratulacje!");
    }
    repaint();
}

void MainWindow::clickLevelBasic()
{
    numberOfLevel = QVariant(((QAction*)sender())->objectName()).toInt();
    myBoard.load(Levels::basicLevel(numberOfLevel));

    // checked only active levels
    for (unsigned short int i=0;i<LEVEL_BASIC;i++)
    {
        levelBasicAction[i]->setChecked(false);
    }
    levelBasicAction[numberOfLevel]->setChecked(true);

    showBoard();
}

void MainWindow::clickStart()
{
    myBoard.load(Levels::basicLevel(numberOfLevel));
    showBoard();
}

void MainWindow::clickBoardsEditor()
{
    mainWindow2 = new MainWindow2(this);
    mainWindow2->show();
}

void MainWindow::clickDOWN()
{
    if (myBoard.isWin()) return;
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
        //steve and diamond/diamondHole and door and teleport=empty/hole
        else if ((myBoard.get(steveY+1,steveX)==OneCell::CELL_DIAMOND || myBoard.get(steveY+1,steveX)==OneCell::CELL_DIAMONDinHOLE) && myBoard.get(steveY+2,steveX)==OneCell::CELL_DOOR && (myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_EMPTY || myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_HOLE))
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x,(myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_EMPTY)?OneCell::CELL_DIAMOND:OneCell::CELL_DIAMONDinHOLE);
             myBoard.set(steveY+1,steveX,(myBoard.get(steveY+1,steveX)==OneCell::CELL_DIAMOND)?OneCell::CELL_STEVE:OneCell::CELL_STEVEinHOLE);
        }
        //steve and door and teleport=diamond/diamondHole and empty/hole
        else if (myBoard.get(steveY+1,steveX)==OneCell::CELL_DOOR && (myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_DIAMOND || myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_DIAMONDinHOLE) && (myBoard.get(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next)==OneCell::CELL_EMPTY || myBoard.get(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next)==OneCell::CELL_HOLE))
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next,(myBoard.get(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next)==OneCell::CELL_EMPTY)?OneCell::CELL_DIAMOND:OneCell::CELL_DIAMONDinHOLE);
             myBoard.set(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x,(myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_DIAMOND)?OneCell::CELL_STEVE:OneCell::CELL_STEVEinHOLE);
        }
    showBoard();
}

void MainWindow::clickUP()
{
    if (myBoard.isWin()) return;
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
        //steve and door and teleport=diamond/diamondHole and empty/hole
        else if (myBoard.get(steveY-1,steveX)==OneCell::CELL_DOOR && (myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_DIAMOND || myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_DIAMONDinHOLE) && (myBoard.get(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next)==OneCell::CELL_EMPTY || myBoard.get(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next)==OneCell::CELL_HOLE))
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next,(myBoard.get(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next)==OneCell::CELL_EMPTY)?OneCell::CELL_DIAMOND:OneCell::CELL_DIAMONDinHOLE);
             myBoard.set(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x,(myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_DIAMOND)?OneCell::CELL_STEVE:OneCell::CELL_STEVEinHOLE);
        }
    showBoard();
}

void MainWindow::clickLEFT()
{
    if (myBoard.isWin()) return;
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
        //steve and door and teleport=diamond/diamondHole and empty/hole
        else if (myBoard.get(steveY,steveX-1)==OneCell::CELL_DOOR && (myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_DIAMOND || myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_DIAMONDinHOLE) && (myBoard.get(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next)==OneCell::CELL_EMPTY || myBoard.get(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next)==OneCell::CELL_HOLE))
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next,(myBoard.get(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next)==OneCell::CELL_EMPTY)?OneCell::CELL_DIAMOND:OneCell::CELL_DIAMONDinHOLE);
             myBoard.set(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x,(myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_DIAMOND)?OneCell::CELL_STEVE:OneCell::CELL_STEVEinHOLE);
        }
    showBoard();
}

void MainWindow::clickRIGHT()
{
    if (myBoard.isWin()) return;

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
        //steve and door and teleport=diamond/diamondHole and empty/hole
        else if (myBoard.get(steveY,steveX+1)==OneCell::CELL_DOOR && (myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_DIAMOND || myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_DIAMONDinHOLE) && (myBoard.get(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next)==OneCell::CELL_EMPTY || myBoard.get(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next)==OneCell::CELL_HOLE))
        {
             myBoard.set(steveY,steveX,(myBoard.get(steveY,steveX)==OneCell::CELL_STEVE)?OneCell::CELL_EMPTY:OneCell::CELL_HOLE);
             myBoard.set(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next,(myBoard.get(myBoard.pos_Teleport_y_next,myBoard.pos_Teleport_x_next)==OneCell::CELL_EMPTY)?OneCell::CELL_DIAMOND:OneCell::CELL_DIAMONDinHOLE);
             myBoard.set(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x,(myBoard.get(myBoard.pos_Teleport_y,myBoard.pos_Teleport_x)==OneCell::CELL_DIAMOND)?OneCell::CELL_STEVE:OneCell::CELL_STEVEinHOLE);
        }
    showBoard();
}

void MainWindow::clickSPACE()
{
    if (!myBoard.isWin()) return;
    if (numberOfLevel<LEVEL_BASIC-1) numberOfLevel++;

    // checked only active levels
    for (unsigned short int i=0;i<LEVEL_BASIC;i++)
    {
        levelBasicAction[i]->setChecked(false);
    }
    levelBasicAction[numberOfLevel]->setChecked(true);

    myBoard.load(Levels::basicLevel(numberOfLevel));
    showBoard();
}
