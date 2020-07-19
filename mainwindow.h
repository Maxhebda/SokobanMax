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
#include <mainwindow2.h>
#include <saveloadboard.h>

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
    void addMenuLevel();                //create menu from basic levels
    void addMenuLevelFromFile();        //create menu from file

private:
    Ui::MainWindow *ui;
    Board myBoard;
    QImage * image;
    QPainter * paintOnImage;
    MainWindow2 * mainWindow2;

    // shortcut up, down, right, left :
    QShortcut * shUP;
    QShortcut * shDOWN;
    QShortcut * shRIGHT;
    QShortcut * shLEFT;
    QShortcut * shSPACE;

    uint8_t WhatBoardsToLoad;   // 0 = basic levels for menu, 1 = levels for file

    // --- levels from file ---
    unsigned short int numberOfLevelFromFile;
    QVector <QAction *> levelFromFileAction;
    SaveLoadBoard levelsFromFile; //all boards from file

    // --- levels basics menu ---
    unsigned short int numberOfLevel;
    static const unsigned short int LEVEL_BASIC=8;                     //number of levels
    QAction * levelBasicAction[LEVEL_BASIC];

protected:
    void paintEvent(QPaintEvent *);

private slots:
    //---- menu
    void clickStart();
    void clickLevelBasic();
    void clickBoardsEditor();
    void clickLoadFromFile();   //click "załaduj z pliku"
    void clickLevelFromFile();  //click level1..  in "z pliku"
    //---- shortcut
    void clickUP();
    void clickDOWN();
    void clickRIGHT();
    void clickLEFT();
    void clickSPACE();
};
#endif // MAINWINDOW_H
