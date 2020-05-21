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
    image->fill(QColor(160,160,160));
    paintOnImage = new QPainter;
    paintOnImage->begin(image);
    // --------------------------- basic bacgroud --------------------

    connect(ui->actionStart,SIGNAL(triggered()),this,SLOT(clickStart()));
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
                    paintOnImage->drawImage(QRectF(10+x*48,10 + ui->menubar->height()+y*48,48,48),QImage(":/img/wall.png"),source);
                    break;
                }
                case OneCell::CELL_DOOR:
                {
                    paintOnImage->drawImage(QRectF(10+x*48,10 + ui->menubar->height()+y*48,48,48),QImage(":/img/door.png"),source);
                    break;
                }
                case OneCell::CELL_STEVE:
                {
                    paintOnImage->drawImage(QRectF(10+x*48,10 + ui->menubar->height()+y*48,48,48),QImage(":/img/steve.png"),source);
                    break;
                }
                case OneCell::CELL_HOLE:
                {
                    paintOnImage->drawImage(QRectF(10+x*48,10 + ui->menubar->height()+y*48,48,48),QImage(":/img/hole.png"),source);
                    break;
                }
                case OneCell::CELL_DIAMOND:
                {
                    paintOnImage->drawImage(QRectF(10+x*48,10 + ui->menubar->height()+y*48,48,48),QImage(":/img/diamond.png"),source);
                    break;
                }
                case OneCell::CELL_DIAMONDinHOLE:
                {
                    paintOnImage->drawImage(QRectF(10+x*48,10 + ui->menubar->height()+y*48,48,48),QImage(":/img/diamondHole.png"),source);
                    break;
                }
                case OneCell::CELL_ARROW_UP:
                {
                    paintOnImage->drawImage(QRectF(10+x*48,10 + ui->menubar->height()+y*48,48,48),QImage(":/img/arrowUP.png"),source);
                    break;
                }
                case OneCell::CELL_ARROW_DOWN:
                {
                    paintOnImage->drawImage(QRectF(10+x*48,10 + ui->menubar->height()+y*48,48,48),QImage(":/img/arrowDown.png"),source);
                    break;
                }
                case OneCell::CELL_ARROW_LEFT:
                {
                    paintOnImage->drawImage(QRectF(10+x*48,10 + ui->menubar->height()+y*48,48,48),QImage(":/img/arrowLeft.png"),source);
                    break;
                }
                case OneCell::CELL_ARROW_RIGHT:
                {
                    paintOnImage->drawImage(QRectF(10+x*48,10 + ui->menubar->height()+y*48,48,48),QImage(":/img/arrorRight.png"),source);
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
