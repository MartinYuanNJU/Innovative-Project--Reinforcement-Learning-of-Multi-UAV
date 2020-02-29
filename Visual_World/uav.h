#ifndef __UAV_H__
#define __UAV_H__

#include "macro.h"
#include "type.h"

class World;

class Uav {
private:
    Pos_info *comm_info;
    Pos pos;
    bool side;
    int step_cnt;
    World *world;
    int comm_cnt;
    int comm_prob;
    bool last_info;
    //int index;

public:
    Uav() {}
    Uav(World* world, Pos pos, bool side);

    void set_world_comm(World *world, Pos_info *comm_info) { this->world = world; this->comm_info = comm_info; }

    bool collision_flag;
    bool attacked_flag;
    bool penalty;

    bool is_nearby(Pos& x);
    bool ob();
    bool is_die();
    void set_comm_prob(int p);
    bool need_comm();

    void reset(Pos pos, bool side);
    State get_state();
    void apply_action(Action action);
    Pos_info scan_nearby();
    int power_count();
    void commit_comm_info();
    void clear_comm_info();
    Pos get_pos() { return pos; }
    bool get_side() { return side; }
};

#endif
