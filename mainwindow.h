#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <board.h>
#include <onecell.h>
#include <QtGui>
#include <QtCore>
#include <QImage>
#include <QShortcut>
#include <levels.h>

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
    void addMenuLevel();

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
    QShortcut * shSPACE;

    unsigned short int numberOfLevel;
    static const unsigned short int LEVEL_BASIC=7;                     //number of levels
    QAction * levelBasicAction[LEVEL_BASIC];

protected:
    void paintEvent(QPaintEvent *);

private slots:
    //---- menu
    void clickStart();
    void clickLevelBasic();
    //---- shortcut
    void clickUP();
    void clickDOWN();
    void clickRIGHT();
    void clickLEFT();
    void clickSPACE();
};
#endif // MAINWINDOW_H
