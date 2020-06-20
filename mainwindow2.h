#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include <QPainter>
#include <board.h>
#include <onecell.h>
#include <QMouseEvent>
#include <QMessageBox>
#include <QVector>
#include <QAction>
#include <saveloadboard.h>
# include <QFileDialog>

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

    //----------- class storing all boards --------------
    SaveLoadBoard saveLoadBoard;

    //------------ counter elements at board ------------
    void counterElementsAtBoard(unsigned short int & diamonds, unsigned short int & holes, bool & steve, bool & diamondsWithoutHole);
    unsigned short int counterDiamond;
    unsigned short int counterHole;
    bool               counterSteve;
    bool               counterDiamondWithoutHole;

    void myMouseClick(QMouseEvent *);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private slots:
    // menu
    void clickFillWall();
    void clickFillEmpty();
    void clickFillEmptyFrame();
    void clickFillEmptyCenter();
    void clickFillSmallEmptyFrame();
    void clickDeleteActiveBoard();
    void clickSaveFile();
    void clickOpenFile();
    // form
    void on_pushButton_clicked();           //clicked "dodaj do zestawu"
    void on_pushButton_2_clicked();         //clicked +nowa
    void on_comboBox_activated(int index);  //combobox
};

#endif // MAINWINDOW2_H
