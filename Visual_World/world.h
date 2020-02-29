#ifndef __WORLD_H__
#define __WORLD_H__

#include "macro.h"
#include "type.h"
#include "object.h"
#include <cstdlib>
#include <ctime>
#include "uav.h"
#include "mainwindow.h"
//#include <QApplication>

class World {
private:
    Uav positive_uav[UAV_COUNT];
    Uav negative_uav[UAV_COUNT];
    Object object[OBJECT_COUNT];

    Pos_info positive_comm_info;
    Pos_info negative_comm_info;

    Pos_info *pos_info;
    set<Pos> *obstacle_pos;

    friend class Env;
    friend class Uav;
    friend class MainWindow;

public:
    World();
    void reset();
    void merge_comm_info();
    void generate_row_col(int &selectrow,int &selectcol);
    void print();
};

#endif
