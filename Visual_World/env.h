#ifndef __ENV_H__
#define __ENV_H__

#include "macro.h"
#include "type.h"
#include "world.h"
#include "uav.h"
#include "object.h"

class Env {
private:
    World *world;
    int step_cnt;

    void process_attack(Uav &a, Uav &b);
    bool same_direction(Uav &u1, Action a1, Uav &u2, Action a2);
    Pos rollback_action(Uav &u, Action a);

    friend class MainWindow;

public:
    Env();
    State *reset();
    SRDI *step(Action action[]);
    void print();
};

#endif
