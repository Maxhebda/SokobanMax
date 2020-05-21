#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <board.h>
#include <onecell.h>
#include <QtGui>
#include <QtCore>
#include <QImage>
#include <QShortcut>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showBoard();

private:
    Ui::MainWindow *ui;
    Board myBoard;
    QImage * image;
    QPainter * paintOnImage;

    // shortcut up, down, right, left :
    QShortcut * shUP;
    QShortcut * shDOWN;
    QShortcut * shRIGHT;
    QShortcut * shLEFT;

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void clickStart();
    void clickUP();
    void clickDOWN();
    void clickRIGHT();
    void clickLEFT();

};
#endif // MAINWINDOW_H
