#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include <QPainter>
#include <board.h>
#include <onecell.h>

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

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void clickFillWall();
    void clickFillEmpty();
    void clickFillEmptyFrame();
    void clickFillEmptyCenter();
    void clickFillSmallEmptyFrame();
};

#endif // MAINWINDOW2_H
