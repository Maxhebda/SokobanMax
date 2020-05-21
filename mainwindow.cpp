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
    image->fill(QColor(230,230,255));
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

                    break;
                }
            }
        }
    }
}

void MainWindow::clickStart()
{
    paintOnImage->drawLine(10,10,30,30);
    repaint();
}
