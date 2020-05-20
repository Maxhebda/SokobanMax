#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QRectF target(10, 10 + ui->menubar->height(), ui->centralwidget->geometry().width()-30, ui->centralwidget->geometry().height()-30);
    QRectF source(0, 0, 23, 23);
    QImage image(":/img/wall.png");

    QPainter painter(this);
    painter.drawImage(target, image, source);

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
