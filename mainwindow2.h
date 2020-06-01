#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include <QPainter>
#include <board.h>
#include <onecell.h>
#include <QMouseEvent>
#include <QMessageBox>

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
    void getXboardClick(short int & x, short int & y, unsigned short int xInForm, unsigned short int yInForm);// x=0-14, y=0-12 -1=npClick
    short int selectedMenu;

    //------------ counter elements at board ------------
    void counterElementsAtBoard(unsigned short int & diamonds, unsigned short int & holes, bool & steve);
    unsigned short int counterDiamond;
    unsigned short int counterHole;
    bool               counterSteve;

    void myMouseClick(QMouseEvent *);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private slots:
    void clickFillWall();
    void clickFillEmpty();
    void clickFillEmptyFrame();
    void clickFillEmptyCenter();
    void clickFillSmallEmptyFrame();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW2_H
