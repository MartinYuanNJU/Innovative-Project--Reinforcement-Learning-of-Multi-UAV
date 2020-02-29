#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "world.h"
#include "env.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(fixed_square_length,fixed_square_length+30);
    visualworld=new QImage(fixed_square_length,fixed_square_length,QImage::Format_RGB32);
    visualworld->fill(Qt::white);

    timer=new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(handleTimeout()));
    timer->start(1000);

    env=new Env();
    env->reset();
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.drawImage(0,0,*visualworld);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawCell()
{
    QPainter *painter=new QPainter(visualworld);
    painter->setPen(Qt::black);
    for(int i=1;i<=cellnum+1;i++)
    {
        int t=i*interval;
        painter->drawLine(t,interval,t,square_length+interval);
        painter->drawLine(interval,t,square_length+interval,t);
    }
    update();
    delete painter;
}

void MainWindow::reset()
{
    QImage newworld(fixed_square_length,fixed_square_length,QImage::Format_RGB32);
    *visualworld=newworld;
    visualworld->fill(Qt::white);
    drawCell();
}

void MainWindow::drawObject(int x,int y,objectType type)
{
    QPainter *painter=new QPainter(visualworld);
    painter->setRenderHint(QPainter::Antialiasing);
    int a,b,c,d;
    a=interval*(x+1);
    b=interval*(x+2);
    c=interval*(y+1);
    d=interval*(y+2);
    int x0=(int)round((a+b)/2);
    int y0=(int)round((c+d)/2);
    QPainterPath path;
    if(type==Obstacle)
    {
        path.moveTo(a,y0);
        path.lineTo(x0,c);
        path.lineTo(b,y0);
        path.lineTo(x0,d);
        path.closeSubpath();
        painter->setPen(Qt::black);
        painter->setBrush(Qt::black);

    }
    else if(type==Uav_Red)
    {
        path.moveTo(a,c);
        path.lineTo(b,c);
        path.lineTo(x0,d);
        path.closeSubpath();
        painter->setPen(Qt::red);
        painter->setBrush(Qt::red);
    }
    else if(type==Uav_Blue)
    {
        path.moveTo(a,d);
        path.lineTo(b,d);
        path.lineTo(x0,c);
        path.closeSubpath();
        painter->setPen(Qt::blue);
        painter->setBrush(Qt::blue);
    }
    else if(type==Object_Unexplored)
    {
        path.addEllipse(b+3-interval,d+3-interval,interval-4,interval-4);
        painter->setPen(QPen(QColor(255,0,255)));
        painter->setBrush(QBrush(QColor(255,0,255)));
    }
    else if(type==Object_Explored)
    {
        path.addEllipse(b+3-interval,d+3-interval,interval-4,interval-4);
        painter->setPen(QPen(QColor(128,128,128)));
        painter->setBrush(QBrush(QColor(128,128,128)));
    }
    else if(type==Uav_Red_Down)
    {
        path.moveTo(a,c);
        path.lineTo(b,c);
        path.lineTo(x0,d);
        path.closeSubpath();
        painter->setPen(Qt::green);
        painter->setBrush(Qt::green);
    }
    else if(type==Uav_Blue_Down)
    {
        path.moveTo(a,d);
        path.lineTo(b,d);
        path.lineTo(x0,c);
        path.closeSubpath();
        painter->setPen(Qt::green);
        painter->setBrush(Qt::green);
    }
    painter->drawPath(path);
    delete painter;
}

void MainWindow::test()
{
    reset();
    drawObject(0,0,Obstacle);
    drawObject(3,3,Uav_Red_Down);
    drawObject(4,4,Uav_Blue_Down);
}

void MainWindow::printWorld(World *world)
{
    reset();
    for(int i = 0; i < UAV_COUNT; i++)
    {
//        qDebug() << world->positive_uav[i].get_state().self_pos.row << world->positive_uav[i].get_state().self_pos.col;
        if(world->positive_uav[i].is_die())
            drawObject(world->positive_uav[i].get_state().self_pos.row,world->positive_uav[i].get_state().self_pos.col,Uav_Red_Down);
        else
            drawObject(world->positive_uav[i].get_state().self_pos.row,world->positive_uav[i].get_state().self_pos.col,Uav_Red);
        if(world->negative_uav[i].is_die())
            drawObject(world->negative_uav[i].get_state().self_pos.row,world->negative_uav[i].get_state().self_pos.col,Uav_Blue_Down);
        else
            drawObject(world->negative_uav[i].get_state().self_pos.row,world->negative_uav[i].get_state().self_pos.col,Uav_Blue);
    }
    for(int i = 0; i < OBJECT_COUNT; i++)
    {
        if(world->object[i].is_detected())
            drawObject(world->object[i].get_pos().row,world->object[i].get_pos().col,Object_Explored);
        else
            drawObject(world->object[i].get_pos().row,world->object[i].get_pos().col,Object_Unexplored);
    }
    set<Pos>::iterator it;
    it = world->obstacle_pos->begin();
    while (it != world->obstacle_pos->end())
    {
        drawObject(it->row,it->col,Obstacle);
        it++;
    }
    update();
}

void MainWindow::handleTimeout()
{
    Action action[UAV_COUNT * 2] = { UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP, UP};
    env->step(action);
    printWorld(env->world);
}
