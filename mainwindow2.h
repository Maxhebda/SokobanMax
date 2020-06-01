#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include <QPainter>
#include <board.h>
#include <onecell.h>
#include <QMouseEvent>

namespace Ui {
class MainWindow2;
}

class MainWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow2(QWidget *parent = nullptr);
    ~MainWindow2();
    void showEditorBoard();

private:
    Ui::MainWindow2 *ui;
    QImage * image;
    QPainter * paintOnImage;
    Board myEditorBoard;
    short int getAmenuClick(unsigned short int x, unsigned short int y);   //-1=noClick, 0-9=a menu position
    short int getXboardClick(unsigned short int x, unsigned short int y);  //-1=noClick, 0-14=x position
    short int getYboardClick(unsigned short int x, unsigned short int y);  //-1=noClick, 0-12=x position
    short int selectedMenu;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private slots:
    void clickFillWall();
    void clickFillEmpty();
    void clickFillEmptyFrame();
    void clickFillEmptyCenter();
    void clickFillSmallEmptyFrame();
};

#endif // MAINWINDOW2_H
