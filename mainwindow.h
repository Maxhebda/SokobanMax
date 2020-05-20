#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <board.h>
#include <onecell.h>
#include <QtGui>
#include <QtCore>

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
protected:
    void paintEvent(QPaintEvent *);
};
#endif // MAINWINDOW_H
