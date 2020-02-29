#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPainterPath>
#include <QMainWindow>
#include <QPolygonF>
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QImage>
#include <QTimer>
#include <cmath>
#include <QPen>
#include "type.h"

class World;

class Env;

enum objectType{
    Uav_Red, Uav_Blue, Uav_Red_Down, Uav_Blue_Down, Object_Unexplored, Object_Explored, Obstacle
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void test();

    void printWorld(World *world);

private:
    Ui::MainWindow *ui;

    QImage *visualworld;

    const int square_length=600;
    const int cellnum=50;
    const int interval=square_length/cellnum;
    const int fixed_square_length=square_length+interval*2;

    QTimer *timer;

    void paintEvent(QPaintEvent*);

    void reset();

    void drawCell();

    void drawObject(int x,int y,objectType type);

    Env *env;

private slots:
    void handleTimeout();
};

#endif // MAINWINDOW_H
